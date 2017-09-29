#if !defined JVS_UITK_WIN32_CANVAS_H_
#define JVS_UITK_WIN32_CANVAS_H_

#include <cassert>
#include <memory>
#include <utility> // for std::pair
#include <Windows.h>
#include <GdiPlus.h>	// May use this later...

#include "jvs/uitk/base/string.h"
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
  using DcWndPair = std::pair<DeviceContextHandle, WindowHandle>;

public:

  Graphics() = delete;

  explicit Graphics(WindowHandle window)
    : window_(window)
  {
    this->getDcFrom(this->window_);
  }

  Graphics(const Graphics& rhs)
    : window_(rhs.window_)
  {
    this->Reset(rhs);
  }

  virtual ~Graphics()
  {
  }

  Graphics& operator=(const Graphics& src)
  {
    this->Reset(src);
    return *this;
  }

  virtual void Reset()
  {
    this->dc_.reset();
  }

  virtual void Reset(const Graphics& canvas)
  {
    this->window_ = canvas.window_;
    this->getDcFrom(this->window_);
  }

  void DrawText(const std::string& text, const Font& font, const Brush& brush,
    const Rectangle& rect) const
  {
    assert(this->getDc() != nullptr);
    RECT r = static_cast<RECT>(rect);
    std::wstring textBuffer{jvs::Widen(text)};
    HFONT oldFont = reinterpret_cast<HFONT>(::SelectObject(this->getDc(),
      reinterpret_cast<HGDIOBJ>(font.handle())));
    Brush oldBrush(reinterpret_cast<HBRUSH>(::SelectObject(this->getDc(),
      reinterpret_cast<HGDIOBJ>(brush.GetValue()))));
    ::DrawTextExW(*this, &textBuffer[0], static_cast<int>(textBuffer.length()),
      &r, DT_LEFT | DT_TOP, 0 /* this param is used for text margins */);
    if (oldFont != font.handle())
    {
      ::SelectObject(this->getDc(), reinterpret_cast<HGDIOBJ>(oldFont));
    }

    if (oldBrush.GetValue() != brush.GetValue())
    {
      ::SelectObject(this->getDc(),
        reinterpret_cast<HGDIOBJ>(oldBrush.GetValue()));
    }

  }

  void FillRectangle(const Brush& brush, const Rectangle& rect) const
  {
    RECT r = static_cast<RECT>(rect);
    ::FillRect(*this, &r, brush);
  }

  Rectangle MeasureText(const std::string& text, Font& font) const
  {
    RECT rect = {0};
    SIZE size;
    assert(this->getDc() != nullptr);
    DeviceContextHandle dc = this->getDc();

    HFONT oldFont = reinterpret_cast<HFONT>(::SelectObject(dc,
      reinterpret_cast<HGDIOBJ>(font.handle())));
    ::GetTextExtentPoint32W(dc, jvs::Widen(text).c_str(), 
      static_cast<int>(text.length()), &size);
    // This can also be done with DrawTextEx:
    //	::DrawTextEx(this->getDc(), &textBuffer[0], textBuffer.length(), 
    //    &rect, DT_SINGLELINE | DT_CALCRECT, NULL);
    if (oldFont != font.handle())
    {
      ::SelectObject(dc, reinterpret_cast<HGDIOBJ>(oldFont));
    }

    rect.right = size.cx;
    rect.bottom = size.cy;
    return rect;
  }

  Rectangle MeasureText(const std::string& text) const
  {
    SIZE size;
    ::GetTextExtentPoint32W(this->getDc(), jvs::Widen(text).c_str(),
      static_cast<int>(text.length()), &size);
    return Rectangle(0, 0, size.cx, size.cy);
  }

  operator DeviceContextHandle() const
  {
    return this->getDc();
  }

protected:
  void Release()
  {
    this->dc_.reset();
  }

private:

  using DcWndPairDeleter = jvs::uitk::win32::GdiObjectDeleter<DcWndPair>;

  std::unique_ptr<DcWndPair, DcWndPairDeleter> dc_{};
  WindowHandle window_{nullptr};

  // cleaner way of retrieving the device context without having to use
  // the confusing "first/second" std::pair syntax
  DeviceContextHandle getDc() const
  {
    if (this->dc_ == nullptr)
    {
      return nullptr; // empty DC
    }

    return this->dc_->first;
  }

  void getDcFrom(WindowHandle wnd)
  {
    assert(::IsWindow(wnd));
    this->dc_.reset(new DcWndPair(::GetDC(wnd), wnd));
  }

}; // class Graphics

}
}
}

#endif