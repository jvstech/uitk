
#if !defined (JVS_UITK_WIN32_COLOR_H_)
#define JVS_UITK_WIN32_COLOR_H_

#include <cstdint>
#include <Windows.h>
#include <jvs/base.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

class Color : public virtual ValueWrapper<COLORREF>
{
private:
  COLORREF color_;

public:

  static const Color Empty;

  Color(void)
    : color_(0)
  {
  }

  Color(DWORD color)
    : color_(color)
  {
  }

  Color(uint8_t r, uint8_t g, uint8_t b)
    : color_(RGB(r, g, b))
  {
  }

  Color(const Color& src)
    : color_(src.color_)
  {
  }

  virtual ~Color(void)
  {
  }

  Color& operator= (const Color& src)
  {
    this->color_ = src.color_;
    return *this;
  }

  COLORREF get_Value(void) const
  {
    return this->color_;
  }

  uint8_t R(void) const
  {
    return GetRValue(this->color_);
  }

  uint8_t G(void) const
  {
    return GetGValue(this->color_);
  }

  uint8_t B(void) const
  {
    return GetBValue(this->color_);
  }
};

const Color Color::Empty = Color();

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif