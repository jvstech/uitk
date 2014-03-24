
#if !defined (JVS_UITK_WIN32_DEFAULT_LAYOUT_H_)
#define JVS_UITK_WIN32_DEFAULT_LAYOUT_H_

#include <cstddef>
#include <jvs/uitk/anchor_styles.h>
#include "layout_engine.h"
#include "rectangle.h"

#include <jvs/debugging/debugkit.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

template <typename ComponentT>
class DefaultLayout : public LayoutEngine<ComponentT>
{
public:

  DefaultLayout(void)
    : LayoutEngine()
  {
  }

  virtual ~DefaultLayout(void)
  {
  }

  void LayoutAnchoredChildren(ComponentType& parent, Point originalSize, 
    Point newSize) override
  {
    TRACEIN_THIS;
    
    if (originalSize.x == newSize.x && originalSize.y == newSize.y)
    {
      // sizes are the same; nothing to do
      return;
    }

    if (originalSize == Point::Zero || newSize == Point::Zero)
    {
      return;
    }

    Rectangle clientArea;
    clientArea.set_size(newSize);
    auto& components = parent.components();
    static auto getDistance = [](ComponentType& component,
      Point size, bool bottom)->int
    {
      if (bottom)
      {
        return (size.y - component.bottom());
      }

      return (size.x - component.right());
    };

    for (std::size_t i = 0; i < components.size(); i++)
    {
      int left;
      int top;
      int width;
      int height;

      ComponentType& child = *components[i];

      if (!child.visible()
        // TODO: || child.ComponentLayoutType == Component.LayoutType.Dock
        )
      {
        continue;
      }

      AnchorStyles anchor = child.anchor();
      left = child.left();
      top = child.top();
      width = child.width();
      height = child.height();

      if ((anchor & AnchorStyles::Right) != AnchorStyles::None) 
      {
        if ((anchor & AnchorStyles::Left) != AnchorStyles::None)
        {
          width = clientArea.width() - 
            getDistance(child, originalSize, false) - left;
        }
        else
        {
          left = clientArea.width() - 
            getDistance(child, originalSize, false) - width;
        }
      }
      else if ((anchor & AnchorStyles::Left) == AnchorStyles::None)
      {
        left = left + (clientArea.width() - (left + width + 
          getDistance(child, originalSize, false))) / 2;
      }

      if ((anchor & AnchorStyles::Bottom) != AnchorStyles::None)
      {
        if ((anchor & AnchorStyles::Top) != AnchorStyles::None)
        {
          height = clientArea.height() - 
            getDistance(child, originalSize, true) - top;
        }
        else
        {
          top = clientArea.height() - 
            getDistance(child, originalSize, true) - height;
        }
      }
      else if ((anchor & AnchorStyles::Top) == AnchorStyles::None)
      {
        top = top + (clientArea.height() - (top + height + 
          getDistance(child, originalSize, true))) / 2;
      }

      //// Sanity
      //if (width < 0)
      //{
      //  width = 0;
      //}

      //if (height < 0)
      //{
      //  height = 0;
      //}

      child.set_bounds(left, top, width, height);
      
    } // for (int i = 0; i < components.size(); i++)
  }
}; // class DefaultLayout

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif