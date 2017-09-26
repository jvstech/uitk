#if !defined (JVS_UITK_WIN32_MOUSE_EVENT_ARGUMENTS_H_)
#define JVS_UITK_WIN32_MOUSE_EVENT_ARGUMENTS_H_

#include <chrono>
#include <Windows.h>
#include "input_event_arguments.h"
#include "mouse_button.h"
#include "point.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

struct MouseEventArguments : InputEventArguments
{
  MouseButton Button;
  int ClickCount;
  Point Location;
  int X;
  int Y;

  MouseEventArguments(const MSG& msg, MouseButton button, int clickCount)
    : InputEventArguments(msg.time, 
    (GET_KEYSTATE_WPARAM(msg.wParam) & MK_SHIFT) != 0,
    (GET_KEYSTATE_WPARAM(msg.wParam) & MK_CONTROL) != 0,
    Keyboard::Alt()),
    Button(button),
    ClickCount(clickCount),
    Location(GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam)),
    X(GET_X_LPARAM(msg.lParam)),
    Y(GET_Y_LPARAM(msg.lParam))
  {
  }

  MouseEventArguments(MouseButton button, int clickCount, int x, int y)
    : InputEventArguments(
      static_cast<long>(std::chrono::high_resolution_clock::now()
        .time_since_epoch().count()), Keyboard::Shift(), Keyboard::Ctrl(),
    Keyboard::Alt()),
    Button(button), 
    ClickCount(clickCount), 
    X(x), 
    Y(y), 
    Location(x, y)
  {
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif