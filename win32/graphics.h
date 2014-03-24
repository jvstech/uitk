
#if !defined JVS_UITK_WIN32_CANVAS_H_
#define JVS_UITK_WIN32_CANVAS_H_

#include <cassert>
#include <memory>
#include <utility> // for std::pair
#include <Windows.h>
#include <GdiPlus.h>	// May use this later...

#include <jvs/base/types.h>
#include "font.h"
#include "brush.h"
#include "gdi_object_deleter.h"
#include "rectangle.h"
#include "win32error.h"

namespace jvs
{
namespace uitk
{
namespace win32
{
  class Graphics
  {
  private:
    typedef std::pair<DeviceContextHandleType, WindowHandleType> DcWndPair;

  public:
    
    explicit Graphics(WindowHandleType window)
      : dc_(), 
      window_(window)
    {
      this->getDcFrom(this->window_);
    }

    Graphics(const Graphics& rhs)
      : dc_(),
      window_(rhs.window_)
    {
      this->Reset(rhs);
    }

    virtual ~Graphics(void)
    {
    }

    Graphics& operator=(const Graphics& src)
    {
      this->Reset(src);
      return *this;
    }

    virtual void Reset(void)
    {
      this->dc_.reset();
    }

    virtual void Reset(const Graphics& canvas)
    {
      assert(::IsWindow(canvas.window_));
      this->window_ = canvas.window_;
      this->getDcFrom(this->window_);
    }
    
    void DrawText(String& text, const Font& font, const Brush& brush, 
      RECT& rect) const
    {
      assert(this->getDc() != nullptr);
      HFONT oldFont = reinterpret_cast<HFONT>(::SelectObject(this->getDc(), 
        reinterpret_cast<HGDIOBJ>(font.handle())));
      Brush oldBrush(reinterpret_cast<HBRUSH>(::SelectObject(this->getDc(),
        reinterpret_cast<HGDIOBJ>(brush.get_Value()))));
      ::DrawTextEx(*this, &text[0], text.length(), &rect, DT_LEFT | DT_TOP, 
        NULL /* this param is used for text margins */ );
      if (oldFont != font.handle())
      {
        ::SelectObject(this->getDc(), reinterpret_cast<HGDIOBJ>(oldFont));
      }

      if (oldBrush.get_Value() != brush.get_Value())
      {
        ::SelectObject(this->getDc(), 
          reinterpret_cast<HGDIOBJ>(oldBrush.get_Value()));
      }

    }

    void FillRectangle(const Brush& brush, const RECT& rect) const
    {
      ::FillRect(this->getDc(), &rect, brush);
    }

    Rectangle MeasureText(String& text, Font& font) const
    {
      RECT rect = { 0 };
      SIZE size;
      assert(this->getDc() != nullptr);
      DeviceContextHandleType dc = this->getDc();
      
      HFONT oldFont = reinterpret_cast<HFONT>(::SelectObject(dc, 
        reinterpret_cast<HGDIOBJ>(font.handle())));
      ::GetTextExtentPoint32(dc, text.c_str(), text.length(), &size);
      // This can also be done with DrawTextEx:
      //	::DrawTextEx(this->getDc(), &text[0], text.length(), &rect, 
      //		DT_SINGLELINE | DT_CALCRECT, NULL);
      if (oldFont != font.handle())
      {
        ::SelectObject(dc, reinterpret_cast<HGDIOBJ>(oldFont));
      }

      rect.right = size.cx;
      rect.bottom = size.cy;
      return rect;
    }

    Rectangle MeasureText(const String& text) const
    {
      SIZE size;
      ::GetTextExtentPoint32(this->getDc(), text.c_str(), text.length(), &size);
      return Rectangle(0, 0, size.cx, size.cy);
    }

    operator DeviceContextHandleType (void) const
    {
      return this->getDc();
    }

  protected:
    void Release(void)
    {
      this->dc_.reset();
    }

  private:

    typedef jvs::uitk::win32::GdiObjectDeleter<DcWndPair> DcWndPairDeleter;

    std::unique_ptr<DcWndPair, DcWndPairDeleter> dc_;
    WindowHandleType window_;

    Graphics(void)
      : dc_(),
      window_(nullptr)
    {
    }

    // cleaner way of retrieving the device context without having to use
    // the confusing "first/second" std::pair syntax
    DeviceContextHandleType getDc(void) const
    {
      if (this->dc_ == nullptr)
      {
        return nullptr; // empty DC
      }

      return this->dc_->first;
    }

    void getDcFrom(WindowHandleType wnd)
    {
      assert(::IsWindow(wnd));
      this->dc_.reset(new DcWndPair(::GetDC(wnd), wnd));
    }

  }; // class Graphics

}
}
}

#endif