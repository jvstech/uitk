
#if !defined (JVS_UITK_WIN32_INPUT_EVENT_ARGUMENTS_H_)
#define JVS_UITK_WIN32_INPUT_EVENT_ARGUMENTS_H_

#include <algorithm>
#include <iterator>
#include <vector>

#include <jvs/base/types.h>
#include "keyboard.h"
#include <jvs/uitk/event_arguments.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

struct InputEventArguments : BasicEventArguments
{
  bool Handled;
  long When;
  bool IsShiftDown;
  bool IsControlDown;
  bool IsAltDown;
  std::string ModifierText;

  InputEventArguments(long when, bool isShiftDown, bool isControlDown, 
    bool isAltDown)
    : Handled(false),
    When(when),
    IsShiftDown(isShiftDown),
    IsControlDown(isControlDown),
    IsAltDown(isAltDown),
    ModifierText()
  {
    std::stringstream modifierText;
    std::vector<std::string> modifiers;
    if (isShiftDown)
    {
      modifiers.push_back("Shift");
    }

    if (isControlDown)
    {
      modifiers.push_back("Ctrl");
    }

    if (isAltDown)
    {
      modifiers.push_back("Alt");
    }

    std::copy(modifiers.begin(), modifiers.end(), 
      std::ostream_iterator<std::string, char>(modifierText, "+"));
    this->ModifierText = modifierText.str();
  }

};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif