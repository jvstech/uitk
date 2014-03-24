
#if !defined (JVS_UITK_WIN32_RECTANGLE_H_)
#define JVS_UITK_WIN32_RECTANGLE_H_

#include <algorithm>
#include <windows.h>
#include "point.h"

namespace jvs
{
namespace uitk
{
namespace win32

{

class Rectangle
{
private:
  RECT rect_;

public:
  LONG& left;
  LONG& x;
  LONG& top;
  LONG& y;
  LONG& right;
  LONG& bottom;

  Rectangle(void)
    : rect_(),
    left(rect_.left),
    x(rect_.left),
    top(rect_.top),
    y(rect_.top),
    right(rect_.right),
    bottom(rect_.bottom)
  {
  }

  Rectangle(const RECT& rect)
    : rect_(rect),
    left(rect_.left),
    x(rect_.left),
    top(rect_.top),
    y(rect_.top),
    right(rect_.right),
    bottom(rect_.bottom)
  {
  }

  Rectangle(const Rectangle& src)
    : rect_(src.rect_),
    left(rect_.left),
    x(rect_.left),
    top(rect_.top),
    y(rect_.top),
    right(rect_.right),
    bottom(rect_.bottom)
  {
  }

  Rectangle(int x, int y, int width, int height)
    : rect_(),
    left(rect_.left),
    x(rect_.left),
    top(rect_.top),
    y(rect_.top),
    right(rect_.right),
    bottom(rect_.bottom)
  {
    this->rect_.left = x;
    this->rect_.top = y;
    this->rect_.right = x + width;
    this->rect_.bottom = y + height;
  }

  virtual ~Rectangle(void)
  {
  }

  RECT* operator&(void)
  {
    return &this->rect_;
  }

  operator RECT(void) const
  {
    return this->rect_;
  }

  bool operator==(const Rectangle& b)
  {
    return (std::memcmp(&this->rect_, &b.rect_, sizeof(this->rect_)) == 0);
  } // operator== */

  bool operator!=(const Rectangle& b)
  {
    return (!(this->operator==(b)));
  } // operator!= */

  Rectangle& operator=(const Rectangle& src)
  {
    this->rect_.left = src.rect_.left;
    this->rect_.top = src.rect_.top;
    this->rect_.right = src.rect_.right;
    this->rect_.bottom = src.rect_.bottom;
    return *this;
  }

  int width(void) const
  {
    return this->rect_.right - this->rect_.left;
  }

  Rectangle& width(int& w)
  {
    w = this->width();
    return *this;
  }

  int height(void) const
  {
    return this->rect_.bottom - this->rect_.top;
  }

  Rectangle& height(int& h)
  {
    h = this->height();
    return *this;
  }

  bool Contains(int x, int y) const
  {
    return (
      ((x >= this->rect_.left) && (x <= this->rect_.right))
      && ((y >= this->rect_.top) && (y <= this->rect_.bottom))
      );
  }

  bool Contains(Point point) const
  {
    return this->Contains(point.x, point.y);
  }

  bool Contains(int x, int y, int w, int h) const
  {
    return (x >= this->rect_.left && y >= this->rect_.top
      && (x + w) <= this->rect_.right && (y + h) <= this->rect_.bottom);
  }

  bool Contains(const Rectangle& r) const
  {
    return this->Contains(r.x, r.y, r.width(), r.height());
  }

  Rectangle CreateIntersection(const Rectangle& r) const
  {
    Rectangle ret;
    ret.left = (std::min)(this->rect_.left, r.rect_.left);
    ret.top = (std::min)(this->rect_.top, r.rect_.top);
    ret.right = (std::max)(this->rect_.right, r.rect_.right);
    ret.bottom = (std::max)(this->rect_.bottom, r.rect_.bottom);
    return ret;
  }

  Rectangle CreateUnion(const Rectangle& r) const
  {
    Rectangle ret;
    ret.left = (std::max)(this->rect_.left, r.rect_.left);
    ret.top = (std::max)(this->rect_.top, r.rect_.top);
    ret.right = (std::min)(this->rect_.right, r.rect_.right);
    ret.bottom = (std::min)(this->rect_.bottom, r.rect_.bottom);
    return ret;
  }

  Point location(void) const
  {
    return Point(this->rect_.left, this->rect_.top);
  }

  Rectangle& location(Point& point)
  {
    point = this->location();
    return *this;
  }

  Point size(void) const
  {
    return Point(this->width(), this->height());
  }

  Rectangle& size(Point& s)
  {
    s = this->size();
    return *this;
  }

  Rectangle& Grow(int h, int v)
  {
    this->rect_.left -= h;
    this->rect_.top -= v;
    this->rect_.right += h;
    this->rect_.bottom += v;
    return *this;
  }

  Rectangle& set_location(int x, int y)
  {
    int w = this->rect_.right - this->rect_.left;
    int h = this->rect_.bottom - this->rect_.top;
    this->rect_.left = x;
    this->rect_.top = y;
    this->rect_.right = x + w;
    this->rect_.bottom = y + h;
    return *this;
  }

  Rectangle& set_location(const Point& p)
  {
    return this->set_location(p.x, p.y);
  }

  Rectangle& SetBounds(int x, int y, int w, int h)
  {
    this->rect_.left = x;
    this->rect_.top = y;
    this->rect_.right = x + w;
    this->rect_.bottom = y + h;
    return *this;
  }

  Rectangle& SetBounds(const Rectangle& r)
  {
    return this->SetBounds(r.x, r.y, r.right - r.x, r.bottom - r.y);
  }

  Rectangle& set_size(int w, int h)
  {
    this->rect_.right = this->rect_.left + w;
    this->rect_.bottom = this->rect_.top + h;
    return *this;
  }

  Rectangle& set_size(Point p)
  {
    return this->set_size(p.x, p.y);
  }

  static Rectangle CreateFromBounds(int left, int top, int right, int bottom)
  {
    return Rectangle(left, top, right - left, bottom - top);
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif