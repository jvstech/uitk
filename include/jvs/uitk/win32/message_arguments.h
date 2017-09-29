#if !defined (JVS_UITK_WIN32_MESSAGE_ARGUMENTS_H_)
#define JVS_UITK_WIN32_MESSAGE_ARGUMENTS_H_

#include "jvs/uitk/win32/types.h"
#include "jvs/uitk/event_arguments.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

struct MessageArguments : BasicEventArguments
{
  bool& Handled;
  LResult& Result;
  MessageType Message;

  MessageArguments(MessageType msg, bool& handled, LResult& result)
    : Message(msg),
    Handled(handled),
    Result(result)
  {
  }

  MessageArguments(WindowHandle handle, UInt message, 
    WParam wparam, LParam lparam, long time, 
    bool& handled, LResult& result)
    : Message(),
    Handled(handled),
    Result(result)
  {
    Message.hwnd = handle;
    Message.message = message;
    Message.wParam = wparam;
    Message.lParam = lparam;
    Message.time = time;
    ::GetCursorPos(&Message.pt);
  }

  virtual ~MessageArguments()
  {
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif