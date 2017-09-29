
#if !defined (JVS_UITK_WIN32_MOUSE_WHEEL_EVENT_ARGUMENTS_H_)
#define JVS_UITK_WIN32_MOUSE_WHEEL_EVENT_ARGUMENTS_H_

#include <windows.h>
#include "mouse_event_arguments.h"

namespace jvs
{
namespace uitk
{
namespace win32

{

struct MouseWheelEventArguments : MouseEventArguments
{
  int WheelRotation;

  MouseWheelEventArguments(const MSG& msg)
    : MouseEventArguments(msg, MouseButton::None, 
    GET_WHEEL_DELTA_WPARAM(msg.wParam) / WHEEL_DELTA), // number of "clicks"
    WheelRotation(GET_WHEEL_DELTA_WPARAM(msg.wParam)) // delta value
  {
  }

  MouseWheelEventArguments(int wheelRotation, int x, int y)
    : MouseEventArguments(MouseButton::None, wheelRotation / WHEEL_DELTA, x, y),
    WheelRotation(WheelRotation)
  {
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif