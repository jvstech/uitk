
#ifndef _CREATIONPARAMETERS_H_INCLUDED
#define _CREATIONPARAMETERS_H_INCLUDED

#include <Windows.h>
#include <atlwin.h>
#include <string>
#include <sstream>
#include <cassert>

#include <jvs/base/types.h>

namespace jvs
{
  using jvs::String;
  using jvs::uitk::StringStream;

  /// <summary> Used to aide component registration and creation by the system. 
  ///           </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  class ComponentCreationParameters
  {
  public:
    HBRUSH BackgroundBrush;
    String ClassName;
    UINT ClassStyles;
    LPCTSTR CursorId;
    String BaseClassName;
    bool UseSystemClass;
    bool UseSystemCursor;
    DWORD WindowStyles;
    DWORD WindowExStyles;
    WNDPROC WindowProc;

    ComponentCreationParameters(void)
      : atom_(NULL),
      BackgroundBrush((HBRUSH)(COLOR_WINDOW + 1)),
      ClassName(),
      ClassStyles(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS),
      CursorId(IDC_ARROW),
      BaseClassName(),
      UseSystemClass(false),
      UseSystemCursor(true),
      WindowStyles(CControlWinTraits::GetWndStyle(0)),
      WindowExStyles(CControlWinTraits::GetWndExStyle(0)),
      WindowProc(NULL)
    {
      this->generateClassName();
    }

    ComponentCreationParameters(const ATL::CWndClassInfo& atlClsInfo)
      : atom_(atlClsInfo.m_atom),
      BackgroundBrush(atlClsInfo.m_wc.hbrBackground),
      ClassName(atlClsInfo.m_wc.lpszClassName),
      ClassStyles(atlClsInfo.m_wc.style),
      CursorId(atlClsInfo.m_lpszCursorID),
      BaseClassName(atlClsInfo.m_lpszOrigName == NULL ? String() 
        : atlClsInfo.m_lpszOrigName),
      UseSystemClass(false),
      UseSystemCursor(atlClsInfo.m_bSystemCursor == TRUE ? true : false),
      WindowStyles(CControlWinTraits::GetWndStyle(0)),
      WindowExStyles(CControlWinTraits::GetWndExStyle(0)),
      WindowProc(atlClsInfo.m_wc.lpfnWndProc)
    {
    }

    ComponentCreationParameters(const ComponentCreationParameters& rhs)
      : atom_(rhs.atom_),
      BackgroundBrush(rhs.BackgroundBrush),
      ClassName(rhs.ClassName),
      ClassStyles(rhs.ClassStyles),
      CursorId(rhs.CursorId),
      BaseClassName(rhs.BaseClassName),
      UseSystemClass(rhs.UseSystemClass),
      UseSystemCursor(rhs.UseSystemCursor),
      WindowStyles(rhs.WindowStyles),
      WindowExStyles(rhs.WindowExStyles),
      WindowProc(rhs.WindowProc)
    {
    }

    ATOM atom(void) const
    {
      return this->atom_;
    }

    bool GetClassInfo(String baseClassName = "", // value copied on purpose
      bool combineClassStyles = false, bool setBaseClassName = true)
    {
      if (baseClassName.empty())
      {
        baseClassName = this->BaseClassName.c_str();
      }

      assert(!baseClassName.empty());

      WNDCLASSEX tempWc;
      ATOM baseClassAtom = static_cast<ATOM>(::GetClassInfoEx(nullptr, 
        baseClassName.c_str(), &tempWc));
      if (baseClassAtom == 0)
      {
        baseClassAtom = static_cast<ATOM>(::GetClassInfoEx(
          ::GetModuleHandle(nullptr), baseClassName.c_str(), 
          &tempWc));
        if (baseClassAtom == 0)
        {
          return false;
        }
      }
      
      this->BackgroundBrush = tempWc.hbrBackground;
      this->ClassStyles = 
        (combineClassStyles ? this->ClassStyles | tempWc.style 
        : tempWc.style) & ~CS_GLOBALCLASS;
      this->WindowProc = tempWc.lpfnWndProc;

      return true;
    }

    ATOM Superclass(const String& baseClassName = "", 
      bool autoGetClassInfo = true, bool combineClassStyles = false)
    {
      // This function is meant to be called BEFORE calling 
      // CWndClassInfo::Register.

      if (!baseClassName.empty())
      {
        this->BaseClassName = baseClassName;
      }
      
      if (this->BaseClassName.empty())
      {
        return this->atom_;
      }

      WNDCLASSEX wc = static_cast<WNDCLASSEX>(*this);

      if (autoGetClassInfo)
      {
        this->GetClassInfo(BaseClassName, combineClassStyles, false);
        wc = static_cast<WNDCLASSEX>(*this);
      }

      if (this->ClassName.empty())
      {
        this->generateClassName();
      }

      wc.lpszClassName = this->ClassName.c_str();

      WNDCLASSEX tempWc;
      tempWc = wc;

      this->atom_ = 
        static_cast<ATOM>(::GetClassInfoEx(::GetModuleHandle(nullptr), 
        this->ClassName.c_str(), &tempWc));

      if (this->atom_ == 0)
      {
        this->atom_ = ::RegisterClassEx(&wc);
        
        // Now that the class has been registered, generate a NEW class
        // name for ATL to use to register and set BaseClassName to the 
        // newly registered class name
        this->BaseClassName = ClassName;
        this->generateClassName();
      }

      return this->atom_;

    }

#if defined (USE_ATL)
    operator ATL::CWndClassInfo (void) const
    {
      ATL::CWndClassInfo createParams = 
      {
        { sizeof(WNDCLASSEX), this->ClassStyles, this->WindowProc,
          0, 0, nullptr, nullptr, nullptr, this->BackgroundBrush, 
          nullptr, 
          this->ClassName.empty() ? NULL : this->ClassName.c_str(), 
          nullptr 
        },
        this->BaseClassName.empty() ? NULL 
        : this->BaseClassName.c_str(), nullptr, CursorId, TRUE, 0, 
        _T("")
      };

      return createParams;
    }
#endif

    operator WNDCLASSEX (void) const
    {
      WNDCLASSEX ret = 
      {
        sizeof(WNDCLASSEX), this->ClassStyles, this->WindowProc,
        0, 0, nullptr, nullptr, nullptr, this->BackgroundBrush, nullptr, 
        this->ClassName.empty() ? nullptr : this->ClassName.c_str(), 
        nullptr
      };

      return ret;
    }

    static ComponentCreationParameters FromBaseClass(const String& className, 
      bool setBaseClassName = true)
    {
      ComponentCreationParameters ret;
      ret.GetClassInfo(className, false, setBaseClassName);
      return ret;
    }

    private:

      ATOM atom_;

      void generateClassName(void)
      {

        // I almost canceled the whole project because of this stupid 
        // function. ATL generates window class names using a format 
        // string. That format	string is "ATL:%p", and the %p parameter is
        // the WNDCLASSEX struct m_wc in the ATL::CWndClassInfo class. 
        // Typically, each window class registered through ATL is its own 
        // actual C++ class, too, and derives from CWindowImpl<T> where T 
        // is the deriving class itself. The end user is expected to use 
        // one of the DECLARE_WND_CLASS macros	(DECLARE_WND_CLASS, 
        // DECLARE_WND_SUPERCLASS, DECLARE_WND_CLASS_EX) which creates the
        // static function T::GetWndClassInfo(). This function itself 
        // returns a static reference to a CWndClassInfo instance so the
        // formatted class name will *always* be unique. In my framework, 
        // ALL of the UI classes inherit from Jut::Window and Jut::Window 
        // inherits CWindowImplBase<Window> when using ATL so I can give 
        // end users options within their own classes to generate their own
        // class names, styles, etc. instead of having to rely on macros 
        // (and because C++ doesn't allow virtual static members... 
        // yet...). As a result, EVERY SINGLE NEW WINDOW CLASS got its ATL
        // assigned class name as the first window to be created. It took 
        // me two freaking weeks to find this bug but the problem has now
        // been rectified with the following code.



        GUID guid;
        StringStream ss;
        
        if (::CoCreateGuid(&guid) == S_OK)
        {
          ss << "JutWindow_";
          ss << std::hex << guid.Data1;
          ss << std::hex << guid.Data2;
          ss << std::hex << guid.Data3;
          ss << std::hex << guid.Data4[0];
          ss << std::hex << guid.Data4[1];
          ss << std::hex << guid.Data4[2];
          ss << std::hex << guid.Data4[3];
          ss << std::hex << guid.Data4[4];
          ss << std::hex << guid.Data4[5];
          ss << std::hex << guid.Data4[6];
          ss << std::hex << guid.Data4[7];
          this->ClassName = ss.str();
        }
        else
        {
          static const String kAlphaNum = 
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
          static const int GenClassNameLen = 8;
          uint32_t seed = 0;
          uint64_t seedValue = std::time(0) 
            + reinterpret_cast<uint64_t>(this);
          std::memcpy(&seed, &seedValue 
            + (sizeof(seedValue) - sizeof(seed)), sizeof(seed));
          std::srand(seed);
          ClassName = "JutWindow_";
          for (int i = 0; i < GenClassNameLen; ++i)
          {
            this->ClassName += kAlphaNum[rand() % (kAlphaNum.length() - 1)];
          }
        }
        
      }

  };

}

#endif