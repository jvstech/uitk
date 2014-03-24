
#if !defined (JVS_UITK_WIN32_BRUSH_H_)
#define JVS_UITK_WIN32_BRUSH_H_

#include <jvs/base.h>
#include <jvs/uitk/win32/types.h>
#include <jvs/uitk/win32/color.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

class Brush : public ValueWrapper<BrushHandleType>
{
private:
  GdiHandle<BrushHandleType> brush_;
  Color color_;

public:

  static const Brush Empty;

  Brush(void)
    : brush_(nullptr),
    color_(Color::Empty)
  {
  }

  Brush(const Brush& src)
    : brush_(src.brush_),
    color_(src.color_)
  {
  }

  Brush(Brush&& src)
    : brush_(std::move(src.brush_)),
    color_(src.color_)
  {
  }

  Brush(BrushHandleType brush)
    : brush_(brush),
    color_(0)
  {
    this->loadLogicalBrush();
  }

  virtual ~Brush(void)
  {
  }

  BrushHandleType get_Value(void) const override
  {
    return this->brush_;
  }

  Brush& Assign(const Color& src)
  {
    this->color_ = src;
    this->brush_ = ::CreateSolidBrush(this->color_);
    return *this;
  }

private:
  void loadLogicalBrush(void)
  {
    LogicalBrushType lb;
    ::GetObject(this->brush_, sizeof(lb), &lb);
    // Duplicate the brush
    this->brush_ = ::CreateBrushIndirect(&lb);
    this->Assign(lb.lbColor);
  }
};

const Brush Brush::Empty = Brush();

}
}
}

#endif