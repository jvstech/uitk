
#ifndef _CREATIONPARAMETERS_H_INCLUDED
#define _CREATIONPARAMETERS_H_INCLUDED

#include <Windows.h>
#include <atlwin.h>
#include <string>
#include <sstream>
#include <cassert>

#include "jvs/uitk/win32/types.h"

#include <jvs/base/types.h>

namespace jvs
{
namespace uitk
{

  /// <summary> Used to aide component registration and creation by the system. 
  ///           </summary>
  /// <remarks> Jsmith, 12/24/2013. </remarks>
  class ComponentCreationParameters
  {
  win32::Atom atom_{0};
  win32::BrushHandle background_brush_{reinterpret_cast<win32::BrushHandle>(
    (COLOR_WINDOW + 1))};
  std::string base_class_name_{};
  std::wstring base_class_name_buffer_{};
  std::string class_name_{};
  std::wstring class_name_buffer_{};
  win32::UInt class_styles_{CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS};
  const wchar_t* cursor_id_{IDC_ARROW};

  public:
  bool UseSystemClass{false};
  bool UseSystemCursor{true};
  win32::DWord WindowStyles{CControlWinTraits::GetWndStyle(0)};
  win32::DWord WindowExStyles{CControlWinTraits::GetWndExStyle(0)};
  WNDPROC WindowProc{nullptr};

  ComponentCreationParameters()
    {
      this->generateClassName();
    }

    ComponentCreationParameters(const ATL::CWndClassInfo& atlClsInfo)
    : atom_{atlClsInfo.m_atom},
    background_brush_{atlClsInfo.m_wc.hbrBackground},
    class_name_{jvs::Narrow(atlClsInfo.m_wc.lpszClassName)},
    class_name_buffer_{atlClsInfo.m_wc.lpszClassName},
    class_styles_{atlClsInfo.m_wc.style},
    cursor_id_{atlClsInfo.m_lpszCursorID},
    base_class_name_{atlClsInfo.m_lpszOrigName == nullptr ? std::string()
      : jvs::Narrow(atlClsInfo.m_lpszOrigName)},
    base_class_name_buffer_{atlClsInfo.m_lpszOrigName == nullptr ?
      std::wstring() : atlClsInfo.m_lpszOrigName},
    UseSystemCursor{atlClsInfo.m_bSystemCursor == TRUE ? true : false},
    WindowProc{atlClsInfo.m_wc.lpfnWndProc}
  {
  }

  ComponentCreationParameters(const ComponentCreationParameters& rhs) = default;

  uitk::win32::Atom atom() const
  {
    return this->atom_;
  }

  win32::BrushHandle background_brush() const
  {
    return this->background_brush_;
  }

  win32::BrushHandle& background_brush()
  {
    return this->background_brush_;
  }

  ComponentCreationParameters& background_brush(win32::BrushHandle& outValue)
  {
    outValue = this->background_brush_;
    return *this;
  }

  ComponentCreationParameters& set_background_brush(
    const win32::BrushHandle& value)
  {
    this->background_brush_ = value;
    return *this;
  }

  ComponentCreationParameters& set_background_brush(win32::BrushHandle&& value)
    {
    this->background_brush_ = std::move(value);
    return *this;
    }


  const std::string& base_class_name() const
    {
    return this->base_class_name_;
    }

  ComponentCreationParameters& base_class_name(std::string& outValue)
    {
    outValue = this->base_class_name_;
    return *this;
  }

  ComponentCreationParameters& set_base_class_name(const std::string& value)
  {
    this->base_class_name_ = value;
    this->base_class_name_buffer_ = jvs::Widen(this->base_class_name_);
    return *this;
  }

  ComponentCreationParameters& set_base_class_name(std::string&& value)
  {
    this->base_class_name_ = std::move(value);
    this->base_class_name_buffer_ = jvs::Widen(this->base_class_name_);
    return *this;
  }

  const std::wstring& base_class_name_buffer() const
  {
    return this->base_class_name_buffer_;
  }

  ComponentCreationParameters& base_class_name_buffer(std::wstring& outValue)
  {
    outValue = this->base_class_name_buffer_;
    return *this;
  }

  const std::string& class_name() const
  {
    return this->class_name_;
  }

  ComponentCreationParameters& class_name(std::string& outValue)
  {
    outValue = this->class_name_;
    return *this;
  }

  ComponentCreationParameters& set_class_name(const std::string& value)
  {
    this->class_name_ = value;
    this->class_name_buffer_ = jvs::Widen(this->class_name_);
    return *this;
  }

  ComponentCreationParameters& set_class_name(std::string&& value)
  {
    this->class_name_ = std::move(value);
    this->class_name_buffer_ = jvs::Widen(this->class_name_);
    return *this;
  }

  const std::wstring& class_name_buffer() const
  {
    return this->class_name_buffer_;
  }

  ComponentCreationParameters& class_name_buffer(std::wstring& outValue)
  {
    outValue = this->class_name_buffer_;
    return *this;
  }

  win32::UInt class_styles() const
  {
    return this->class_styles_;
  }

  win32::UInt& class_styles()
  {
    return this->class_styles_;
  }

  ComponentCreationParameters& class_styles(win32::UInt& outValue)
  {
    outValue = this->class_styles_;
    return *this;
  }

  ComponentCreationParameters& set_class_styles(win32::UInt value)
  {
    this->class_styles_ = value;
    return *this;
    }

  bool GetClassInfo(std::string baseClassName = "", // value copied on purpose
      bool combineClassStyles = false, bool setBaseClassName = true)
    {
    std::wstring baseClassNameBuffer;
    if (!baseClassName.empty())
      {
      baseClassNameBuffer = jvs::Widen(baseClassName);
    }
    else
    {
      baseClassNameBuffer = this->base_class_name_buffer_;
      }

    assert(!baseClassNameBuffer.empty());

      WNDCLASSEX tempWc;
    ATOM baseClassAtom = static_cast<ATOM>(::GetClassInfoExW(nullptr,
      baseClassNameBuffer.c_str(), &tempWc));
      if (baseClassAtom == 0)
      {
      baseClassAtom = static_cast<ATOM>(::GetClassInfoExW(
        ::GetModuleHandleW(nullptr), baseClassNameBuffer.c_str(),
          &tempWc));
        if (baseClassAtom == 0)
        {
          return false;
        }
      }
      
    this->background_brush_ = tempWc.hbrBackground;
    this->class_styles_ =
      (combineClassStyles ? this->class_styles_ | tempWc.style
        : tempWc.style) & ~CS_GLOBALCLASS;
      this->WindowProc = tempWc.lpfnWndProc;

      return true;
    }

  ATOM Superclass(const std::string& baseClassName = "",
      bool autoGetClassInfo = true, bool combineClassStyles = false)
    {
      // This function is meant to be called BEFORE calling 
      // CWndClassInfo::Register.

      if (!baseClassName.empty())
      {
      this->set_base_class_name(baseClassName);
      }
      
    if (this->base_class_name_.empty())
      {
        return this->atom_;
      }

      WNDCLASSEX wc = static_cast<WNDCLASSEX>(*this);

      if (autoGetClassInfo)
      {
      this->GetClassInfo(this->base_class_name_, combineClassStyles, false);
        wc = static_cast<WNDCLASSEX>(*this);
      }

    if (this->class_name_.empty())
      {
        this->generateClassName();
      }

    wc.lpszClassName = this->class_name_buffer_.c_str();

      WNDCLASSEX tempWc;
      tempWc = wc;

      this->atom_ = 
      static_cast<ATOM>(::GetClassInfoExW(::GetModuleHandleW(nullptr),
        this->class_name_buffer_.c_str(), &tempWc));

      if (this->atom_ == 0)
      {
      this->atom_ = ::RegisterClassExW(&wc);
        
        // Now that the class has been registered, generate a NEW class
      // name for ATL to use to register and set base_class_name_ to the 
        // newly registered class name
      this->set_base_class_name(this->class_name_);
        this->generateClassName();
      }

      return this->atom_;

    }

#if defined (USE_ATL)
  operator ATL::CWndClassInfo() const
    {
      ATL::CWndClassInfo createParams = 
      {
      { sizeof(WNDCLASSEX), this->class_styles_, this->WindowProc,
        0, 0, nullptr, nullptr, nullptr, this->background_brush_,
          nullptr, 
        // FIXME: hanging reference
        this->class_name_.empty() ? NULL : this->class_name_buffer_.c_str(),
          nullptr 
        },
      this->base_class_name_.empty() ? NULL : 
        this->base_class_name_buffer_.c_str(), 
      nullptr, cursor_id_, TRUE, 0, _T("")
      };

      return createParams;
    }
#endif

  operator WNDCLASSEXW () const
    {
    WNDCLASSEXW ret =
      {
      sizeof(WNDCLASSEXW), this->class_styles_, this->WindowProc,
      0, 0, nullptr, nullptr, nullptr, this->background_brush_, nullptr,
      this->class_name_.empty() ? nullptr : this->class_name_buffer_.c_str(),
        nullptr
      };

      return ret;
    }

  static ComponentCreationParameters FromBaseClass(
    const std::string& className, bool setBaseClassName = true)
    {
      ComponentCreationParameters ret;
      ret.GetClassInfo(className, false, setBaseClassName);
      return ret;
    }

    private:



  void generateClassName()
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
    std::stringstream ss{};
        
        if (::CoCreateGuid(&guid) == S_OK)
        {
      ss << "UITKWindow_";
          ss << std::hex << guid.Data1;
          ss << std::hex << guid.Data2;
          ss << std::hex << guid.Data3;
      ss << std::hex << static_cast<int>(guid.Data4[0]);
      ss << std::hex << static_cast<int>(guid.Data4[1]);
      ss << std::hex << static_cast<int>(guid.Data4[2]);
      ss << std::hex << static_cast<int>(guid.Data4[3]);
      ss << std::hex << static_cast<int>(guid.Data4[4]);
      ss << std::hex << static_cast<int>(guid.Data4[5]);
      ss << std::hex << static_cast<int>(guid.Data4[6]);
      ss << std::hex << static_cast<int>(guid.Data4[7]);
      this->set_class_name(ss.str());
        }
        else
        {
      static const std::string kAlphaNum =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
          static const int GenClassNameLen = 8;
          uint32_t seed = 0;
          uint64_t seedValue = std::time(0) 
            + reinterpret_cast<uint64_t>(this);
          std::memcpy(&seed, &seedValue 
            + (sizeof(seedValue) - sizeof(seed)), sizeof(seed));
          std::srand(seed);
      std::string className{"UITKWindow_"};
          for (int i = 0; i < GenClassNameLen; ++i)
          {
        className += kAlphaNum[rand() % (kAlphaNum.length() - 1)];
          }

      this->set_class_name(className);
        }
        
      }

  };

} // namespace uitk
} // namespace jvs

#endif