
#if !defined (JVS_UITK_WIN32_BRUSH_H_)
#define JVS_UITK_WIN32_BRUSH_H_

#include "jvs/uitk/base/value_wrapper.h"
#include "jvs/uitk/win32/types.h"
#include "jvs/uitk/win32/color.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

class Brush : public ValueWrapper<BrushHandle>
{
private:
  BrushHandle brush_;
  Color color_;

public:

  static const Brush Empty;

  Brush()
    : brush_(nullptr),
    color_(Color::Empty)
  {
  }

  Brush(const Brush& src)
    : brush_(src.brush_),
    color_(src.color_)
  {
    this->loadLogicalBrush();
  }

  Brush(Brush&&) = default;

  Brush(BrushHandle brush)
    : brush_(brush),
    color_(0)
  {
    this->loadLogicalBrush();
  }

  virtual ~Brush()
  {
    if (this->brush_ != nullptr)
    {
      this->dispose();
    }
  }

  Brush& operator=(Brush&&) = default;

  BrushHandle GetValue() const override
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
  void dispose()
  {
    GdiObjectDisposer::Dispose(this->brush_);
    this->brush_ = nullptr;
  }

  void loadLogicalBrush()
  {
    LogicalBrush lb{};
    ::GetObject(this->brush_, sizeof(lb), &lb);
    // Duplicate the brush
    this->brush_ = ::CreateBrushIndirect(&lb);
  }
};

const Brush Brush::Empty{};

}
}
}

#endif