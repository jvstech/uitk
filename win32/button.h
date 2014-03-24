
#if !defined (JVS_UITK_WIN32_BUTTON_H_)
#define JVS_UITK_WIN32_BUTTON_H_

// TODO: Add the ability for the button colors to be changed
// (Note to future self: this is handled exclusively in the WM_PAINT message)

#include "component.h"

namespace jvs
{
namespace uitk
{
namespace win32
{
class Button : public Component
{
public:

  Button(void)
  {
    this->Initialize();
  }

  virtual ~Button(void)
  {
  }

  // used to manually simulate a click event
  Button& ProcessClick(void)
  {
    bool handledIgnored = false;
    LRESULT resultIgnored = 0;
    MSG msg = { 0 };
    msg.hwnd = this->handle();
    msg.message = WM_LBUTTONDOWN;
    this->ProcessEvent(*this, MessageArguments(msg, handledIgnored,
                       resultIgnored));
    msg.message = WM_LBUTTONUP;
    this->ProcessEvent(*this, MessageArguments(msg, handledIgnored,
                       resultIgnored));
    return *this;
  }

protected:

  ComponentCreationParameters GetCreationParameters(void) const override
  {
    auto ret = Component::GetCreationParameters();
    ret.BaseClassName = "Button";
    return ret;
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif