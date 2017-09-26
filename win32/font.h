
#if !defined JVS_UITK_WIN32_FONT_H_
#define JVS_UITK_WIN32_FONT_H_

#include <memory>
#include <string>
#include <cstdint>
#include <functional>
#include <Windows.h>

#include "jvs/uitk/base/string.h"
#include "jvs/uitk/win32/types.h"
#include "gdi_object_deleter.h"
#include "win32error.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

class Font
{
private:
  FontHandle handle_;
  std::string face_;
  float size_;
  bool bold_;
  bool italic_;
  bool underline_;
  bool strikethru_;

  static const std::unique_ptr<FontHandle> SystemFontHandle;

public:
  
  static const Font Default;

  Font()
    : handle_(nullptr),
    face_(),
    size_(0.0f),
    bold_(false),
    italic_(false),
    underline_(false),
    strikethru_(false)
  {
    this->loadFont();
  }

  Font(const Font& src)
    : handle_(src.handle_),
    face_(src.face_),
    size_(src.size_),
    bold_(src.bold_),
    italic_(src.italic_),
    underline_(src.underline_),
    strikethru_(src.strikethru_)
  {
    this->loadFont();
  }

  Font(Font&& src)
    : handle_(src.handle_),
    face_(std::move(src.face_)),
    size_(src.size_),
    bold_(src.bold_),
    italic_(src.italic_),
    underline_(src.underline_),
    strikethru_(src.strikethru_)
  {
    src.handle_ = nullptr;
  }

  Font(const std::string& face, float pointSize, bool bold = false,
    bool italic = false, bool underline = false, 
    bool strikethru = false)
    : handle_(nullptr),
    face_(face), 
    size_(pointSize), 
    bold_(bold), 
    italic_(italic), 
    underline_(underline), 
    strikethru_(strikethru)
  {
    this->createFont();
  }

  Font(FontHandle font) 
    : handle_(font),
    face_(), 
    size_(0.0f), 
    bold_(false), 
    italic_(false), 
    underline_(false), 
    strikethru_(false)
  {
    if (font == nullptr)
    {
      this->handle_ = Font::Default;
    }

    this->loadFont();
  }

  virtual ~Font()
  {
    this->dispose();
  }

  Font& Assign(const Font& src)
  {
    if (src.handle_ != this->handle_)
    {
      this->handle_ = src.handle_;
      this->loadFont();
    }

    return *this;
  }

  Font& Assign(Font&& src)
  {
    this->handle_ = src.handle_;
    this->face_ = std::move(src.face_);
    this->size_ = src.size_;
    this->bold_ = src.bold_;
    this->italic_ = src.italic_;
    this->underline_ = src.underline_;
    this->strikethru_ = src.strikethru_;
    src.handle_ = nullptr;
    return *this;
  }

  Font& operator= (const Font& src)
  {
    return this->Assign(src);
  }

  Font& operator= (Font&& src)
  {
    return this->Assign(std::move(src));
  }
    
  operator const FontHandle() const
  {
    return this->handle_;
  }

  const std::string& face() const
  {
    return this->face_;
  }

  const FontHandle handle() const
  {
    return this->handle_;
  }

  float size() const
  {
    return this->size_;
  }

  bool bold() const
  {
    return this->bold_;
  }

  bool italic() const
  {
    return this->italic_;
  }

  bool underline() const
  {
    return this->underline_;
  }

  bool strikethru() const
  {
    return this->strikethru_;
  }

  uint32_t GetHeight() const
  {
    // TODO: modify this to use GDI+ (see GdipGetFontHeight)
    TEXTMETRICW tm;
    auto hdc = ::GetDC(nullptr);
    ::GetTextMetricsW(hdc, &tm);
    ::ReleaseDC(nullptr, hdc);
    return tm.tmHeight;
  }

  static FontHandle GetCurrentSystemFontHandle()
  {
    static FontHandle currentSystemFontHandle = nullptr;
    if (currentSystemFontHandle == nullptr)
    {
      LOGFONTW lf;
      ::SystemParametersInfoW(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 
        SPIF_SENDWININICHANGE);
      currentSystemFontHandle = ::CreateFontIndirectW(&lf);
    }
  }

private:
  void dispose()
  {
    if (this->handle_ != nullptr)
    {
      GdiObjectDisposer::Dispose(this->handle_);
    }
  }

  void createFont()
  {
    auto hdc = ::GetDC(nullptr);
    int lfHeight = static_cast<int>((-((this->size_ * ::GetDeviceCaps(hdc, 
      LOGPIXELSY)) / 72)));
    ::ReleaseDC(nullptr, hdc);

    this->handle_ = ::CreateFontW(
      lfHeight,
      0, // width
      0, // escapement
      0, // orientation
      bold_ ? FW_BOLD : 0, 
      this->italic_ ? TRUE : FALSE, 
      this->underline_ ? TRUE : FALSE, 
      this->strikethru_ ? TRUE : FALSE, 
      DEFAULT_CHARSET, 
      OUT_OUTLINE_PRECIS, 
      CLIP_DEFAULT_PRECIS, 
      CLEARTYPE_QUALITY, 
      VARIABLE_PITCH, 
      jvs::Widen(this->face_).c_str());
  }

  void loadFont()
  {
    if (this->handle_ == nullptr)
    {
      this->handle_ = Font::Default;
    }

    auto hdc = ::GetDC(nullptr);
    auto pixelSize = ::GetDeviceCaps(hdc, LOGPIXELSY);
    ::ReleaseDC(nullptr, hdc);
    LOGFONTW lf;
    if (::GetObjectW(this->handle_, sizeof(LOGFONTW), &lf) == 0)
    {
      Win32Error error(::GetLastError());
      throw error;
    }
  
    // Duplicate the font here so it can be disposed by its original owner
    // without causing any aliasing issues
    this->handle_ = ::CreateFontIndirectW(&lf);
    this->face_ = jvs::Narrow(lf.lfFaceName);
    this->size_ = std::abs(static_cast<float>(lf.lfHeight * 72 / pixelSize));
    this->bold_ = (lf.lfWeight >= FW_BOLD);
    this->italic_ = lf.lfItalic != FALSE;
    this->underline_ = lf.lfUnderline != FALSE;
    this->strikethru_ = lf.lfStrikeOut != FALSE;
  }

  static FontHandle* allocateSystemFont()
  {
    LOGFONTW lf;
    ::SystemParametersInfoW(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, NULL);
    FontHandle* ret = new FontHandle;
    *ret = ::CreateFontIndirectW(&lf);
    return ret;
  }

};

const std::unique_ptr<FontHandle> Font::SystemFontHandle = 
  std::unique_ptr<FontHandle>(Font::allocateSystemFont());

const Font Font::Default = Font(*Font::SystemFontHandle);

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif