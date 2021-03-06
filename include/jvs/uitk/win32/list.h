/*******************************************************************************
 List control

 TODO:
 * Get layouts working properly without having to set LBS_NOINTEGRALHEIGHT on
   the window style
 ******************************************************************************/


#if !defined (JVS_UITK_WIN32_LIST_H_)
#define JVS_UITK_WIN32_LIST_H_

#if defined (_MSC_VER)
#pragma once
#endif

#include <vector>
#include <map>
#include <commctrl.h>
#include "component.h"

namespace jvs
{
namespace uitk
{
namespace win32
{
  class List : public Component
  {
  private:
    bool allow_multiple_selections_;
    std::vector<std::string> items_;
    std::map<int, bool> selected_;

  public:

    List() 
      : items_(), 
      allow_multiple_selections_(false)
    {
      this->set_background_color(::GetSysColor(COLOR_WINDOW));
      this->set_background_mode(BackgroundMode::Opaque);
      this->Initialize();
    }

    virtual ~List()
    {
    }

    // Add function also serves as Insert
    virtual List& Add(const std::string& item, int index = -1)
    {
      if (this->items_.empty() || index < 0)
      {
        this->items_.push_back(item);
      }
      else
      {
        this->items_.insert(items_.begin() + index, item);
      }

      if (this->IsCreated())
      {
        ::SendMessage(*this, LB_INSERTSTRING, index, 
          reinterpret_cast<LPARAM>(item.c_str()));
      }

      return *this;
    }

    virtual bool allow_multiple_selections() const
    {
      if (this->IsCreated())
      {
        return ((::GetWindowLongPtrW(*this, GWL_STYLE) & LBS_EXTENDEDSEL) != 0);
      }

      return this->allow_multiple_selections_;
    }

    virtual List& set_allow_multiple_selections(bool value)
    {
      this->allow_multiple_selections_ = value;

      if (this->IsCreated())
      {
        if (this->allow_multiple_selections_)
        {
          ::SetWindowLongPtrW(*this, GWL_STYLE, 
            ::GetWindowLongPtrW(*this, GWL_STYLE) | LBS_EXTENDEDSEL);
        }
        else
        {
          ::SetWindowLongPtrW(*this, GWL_STYLE, 
            ::GetWindowLongPtrW(*this, GWL_STYLE) & ~LBS_EXTENDEDSEL);
        }
      }

      return *this;
    }

    virtual int size() const
    {
      return static_cast<int>(this->items_.size());
    }

    virtual List& Deselect(int index)
    {
      if (this->IsCreated())
      {
        if (this->allow_multiple_selections_)
        {
          ::SendMessageW(*this, LB_SETSEL, static_cast<WPARAM>(FALSE), 
            static_cast<LPARAM>(index));
        }
        else
        {
          ::SendMessageW(*this, LB_SETCURSEL, -1, 0);
        }
      }

      return *this;
    }

    List& DeselectAll()
    {
      return this->Deselect(-1);
    }

    virtual List& Remove(int index)
    {
#pragma warning(push)
#pragma warning(disable : 4018)
      if (index < 0 || index >= this->items_.size())
#pragma warning(pop)
      {
        return *this;
      }

      if (this->IsCreated())
      {
        ::SendMessageW(*this, LB_DELETESTRING, index, 0);
      }

      this->items_.erase(this->items_.begin() + index);

      return *this;
    }

    // "item" is passed as a copy to prevent aliasing issues
    virtual List& Remove(const std::string& item)
    {
      auto result = std::find(this->items_.begin(), this->items_.end(), item);
      if (result != this->items_.end())
      {
        if (this->IsCreated())
        {
          // Some people have said to me "you should 
          // use _items.distance(_items.begin(), result
          // because its standard"; My response is that
          // result - _items.begin() works and is O(n) 
          // whereas the distance method is O(n^2) and
          // I also have no plans on changing the 
          // storage container to a list.
          ::SendMessageW(*this, LB_DELETESTRING, result - items_.begin(), 0);
        }

        this->items_.erase(result);
      }

      return *this;
    }

    virtual List& RemoveAll()
    {
      this->items_.clear();
      if (this->IsCreated())
      {
        ::SendMessage(*this, LB_RESETCONTENT, 0, 0);
      }

      return *this;
    }

    virtual List& Select(int index)
    {
      if (this->IsCreated())
      {
        if (this->allow_multiple_selections_)
        {
          ::SendMessage(*this, LB_SETSEL, static_cast<WPARAM>(TRUE), 
            static_cast<LPARAM>(index));
        }
        else
        {
          ::SendMessage(*this, LB_SETCURSEL, static_cast<WPARAM>(index), 0);
        }
      }

      return *this;
    }

    virtual List& SelectAll()
    {
      return this->Select(-1);
    }


  protected:

    virtual ComponentCreationParameters GetCreationParameters() const 
      override
    {
      auto ret = Component::GetCreationParameters();
      ret.set_base_class_name(jvs::Narrow(WC_LISTBOXW));
      ret.WindowExStyles |= WS_EX_CLIENTEDGE;
      // This *must* be set to allow anchoring and layouts to work properly
      // (otherwise, the component height is fixed to any number divisible by 
      // the height of an item)
      // TODO: Make layouts work even without this style flag set
      ret.WindowStyles |= LBS_NOINTEGRALHEIGHT;
      if (this->allow_multiple_selections_)
      {
        ret.WindowStyles |= LBS_EXTENDEDSEL;
      }

      return ret;
    }

    virtual LResult WmChar(LParam defaultResult, MSG& msg, bool& handled) 
      override
    {
      if (msg.wParam == Keyboard::Ctrl(TEXT('a')))
      {
        this->SelectAll();
      }

      handled = false;
      return 0;
    }
  };

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif