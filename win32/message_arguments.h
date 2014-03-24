
#if !defined (JVS_UITK_WIN32_MESSAGE_ARGUMENTS_H_)
#define JVS_UITK_WIN32_MESSAGE_ARGUMENTS_H_

#include <jvs/uitk/win32/types.h>
#include <jvs/uitk/event_arguments.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

struct MessageArguments : BasicEventArguments
{
  bool& Handled;
  Int32ResultType& Result;
  MessageType Message;

  MessageArguments(MessageType msg, bool& handled, Int32ResultType& result)
    : Message(msg),
    Handled(handled),
    Result(result)
  {
  }

  MessageArguments(WindowHandleType handle, UIntType message, 
    Int16ParameterType wparam, Int32ParameterType lparam, long time, 
    bool& handled, Int32ResultType& result)
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

  virtual ~MessageArguments(void)
  {
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif