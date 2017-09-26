
#if !defined (JVS_UITK_WIN32_KEY_EVENT_ARGUMENTS_H_)
#define JVS_UITK_WIN32_KEY_EVENT_ARGUMENTS_H_

#include <cstdint>
#include <windows.h>
#include <jvs/base/types.h>
//#include "keyboard.h"
#include "key_state.h"
#include "input_event_arguments.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

struct KeyEventArguments : InputEventArguments
{
  uint32_t KeyCode;
  char KeyChar;
  std::string KeyText;

  KeyEventArguments(uint32_t keyCode, char keyChar, const std::string& keyText,
    bool isShiftDown, bool isControlDown, bool isAltDown, long when)
    : InputEventArguments(when, isShiftDown, isControlDown,
    isAltDown),
    KeyCode(keyCode),
    KeyChar(keyChar),
    KeyText(keyText)
  {
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif