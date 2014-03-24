
#if !defined JVS_UITK_WIN32_FONT_H_
#define JVS_UITK_WIN32_FONT_H_

#include <memory>
#include <string>
#include <cstdint>
#include <functional>
#include <Windows.h>

#include <jvs/base/types.h>
#include <jvs/uitk/win32/types.h>
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
  FontHandleType handle_;
  String face_;
  float size_;
  bool bold_;
  bool italic_;
  bool underline_;
  bool strikethru_;

  static const std::unique_ptr<FontHandleType> SystemFontHandle;

public:
  
  static const Font Default;

  Font(void)
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

  Font(const String& face, float pointSize, bool bold = false, 
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

  Font(FontHandleType font) 
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

  virtual ~Font(void)
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
    
  operator const FontHandleType(void) const
  {
    return this->handle_;
  }

  const String& get_Face(void) const
  {
    return this->face_;
  }

  const FontHandleType handle(void) const
  {
    return this->handle_;
  }

  float get_Size(void) const
  {
    return this->size_;
  }

  bool get_Bold(void) const
  {
    return this->bold_;
  }

  bool get_Italic(void) const
  {
    return this->italic_;
  }

  bool get_Underline(void) const
  {
    return this->underline_;
  }

  bool get_StrikeThru(void) const
  {
    return this->strikethru_;
  }

  uint32_t GetHeight(void) const
  {
    // TODO: modify this to use GDI+ (see GdipGetFontHeight)
    TEXTMETRIC tm;
    auto hdc = ::GetDC(nullptr);
    ::GetTextMetrics(hdc, &tm);
    ::ReleaseDC(nullptr, hdc);
    return tm.tmHeight;
  }

  static FontHandleType GetCurrentSystemFontHandle(void)
  {
    static FontHandleType currentSystemFontHandle = NULL;
    if (currentSystemFontHandle == NULL)
    {
      LOGFONT lf;
      ::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, 
        SPIF_SENDWININICHANGE);
      currentSystemFontHandle = ::CreateFontIndirect(&lf);
    }
  }

private:
  void dispose(void)
  {
    if (this->handle_ != nullptr)
    {
      GdiObjectDisposer::Dispose(this->handle_);
    }
  }

  void createFont(void)
  {
    auto hdc = ::GetDC(nullptr);
    int lfHeight = static_cast<int>((-((this->size_ * ::GetDeviceCaps(hdc, 
      LOGPIXELSY)) / 72)));
    ::ReleaseDC(nullptr, hdc);

    this->handle_ = ::CreateFont(
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
      this->face_.c_str());
  }

  void loadFont(void)
  {
    if (this->handle_ == nullptr)
    {
      this->handle_ = Font::Default;
    }

    auto hdc = ::GetDC(nullptr);
    auto pixelSize = ::GetDeviceCaps(hdc, LOGPIXELSY);
    ::ReleaseDC(nullptr, hdc);
    LOGFONT lf;
    if (::GetObject(this->handle_, sizeof(LOGFONT), &lf) == 0)
    {
      Win32Error error(::GetLastError());
      throw error;
    }
  
    // Duplicate the font here so it can be disposed by its original owner
    // without causing any aliasing issues
    this->handle_ = ::CreateFontIndirect(&lf);
    this->face_ = String(lf.lfFaceName);
    this->size_ = std::abs((float)(lf.lfHeight * 72 / pixelSize));
    this->bold_ = (lf.lfWeight >= FW_BOLD);
    this->italic_ = lf.lfItalic != FALSE;
    this->underline_ = lf.lfUnderline != FALSE;
    this->strikethru_ = lf.lfStrikeOut != FALSE;
  }

  static FontHandleType* allocateSystemFont(void)
  {
    LOGFONT lf;
    ::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lf), &lf, NULL);
    FontHandleType* ret = new FontHandleType;
    *ret = ::CreateFontIndirect(&lf);
    return ret;
  }

};

const std::unique_ptr<FontHandleType> Font::SystemFontHandle = 
  std::unique_ptr<FontHandleType>(Font::allocateSystemFont());

const Font Font::Default = Font(*Font::SystemFontHandle);

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif