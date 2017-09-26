
#if !defined (JVS_UITK_WIN32_POINT_H_)
#define JVS_UITK_WIN32_POINT_H_

#include <utility>
#include <windows.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

class Point
{
public:
  using ValueType = POINT;
  using CoordinateType = decltype(std::declval<POINT>().x);

private:
  ValueType point_{0, 0};

public:
  CoordinateType& x;
  CoordinateType& y;
  static const Point Zero;

  Point()
    : point_(),
      x(point_.x),
      y(point_.y)
  {
  }

  Point(const Point& src)
    : point_(src.point_),
      x(point_.x),
      y(point_.y)
  {
  }

  Point(ValueType src)
    : point_(src),
      x(point_.x),
      y(point_.y)
  {
  }

  Point(int x, int y)
    : point_(),
      x(point_.x),
      y(point_.y)
  {
    this->point_.x = x;
    this->point_.y = y;
  }

  ~Point()
  {
  }

  Point& operator=(const Point& src)
  {
    this->point_.x = src.point_.x;
    this->point_.y = src.point_.y;
    return *this;
  }

  operator ValueType() const
  {
    return this->point_;
  }

  ValueType* operator&()
  {
    return &this->point_;
  }

  bool operator==(const Point& b)
  {
    return (std::memcmp(&this->point_, &b.point_, sizeof(POINT)) == 0);
  }

  Point& Move(int offsetX, int offsetY)
  {
    this->point_.x += offsetX;
    this->point_.y += offsetY;
    return *this;
  }

  Point& Move(const Point& offset)
  {
    return this->Move(offset.x, offset.y);
  }

  Point& set_Location(int x, int y)
  {
    this->point_.x = x;
    this->point_.y = y;
    return *this;
  }

};

// static initializers
const Point Point::Zero = Point(0, 0);

}
}
}

#endif