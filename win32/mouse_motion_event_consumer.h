
#if !defined (JVS_UITK_WIN32_MOUSEMOTION_EVENT_CONSUMER_H_)
#define JVS_UITK_WIN32_MOUSEMOTION_EVENT_CONSUMER_H_

#include <windows.h>
#include <jvs/uitk/event.h>
#include <jvs/uitk/event_consumer.h>
#include "component.h"
#include "message_arguments.h"
#include "mouse_event_consumer.h"
#include "mouse_event_arguments.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

class MouseMotionEventConsumer :
  public virtual MouseEventConsumer
{
public:
  typedef MouseEventConsumer::ConsumerType ConsumerType;
  typedef MouseMotionEventConsumer Type;

private:
  MouseEventConsumer::MouseEventHandler dragged_;
  MouseEventConsumer::MouseEventHandler moved_;

public:
  MouseEventConsumer::MouseEventHandler& Dragged;
  MouseEventConsumer::MouseEventHandler& Moved;

  MouseMotionEventConsumer(void)
    : MouseEventConsumer(),
      dragged_(),
      moved_(),
      Dragged(dragged_),
      Moved(moved_)
  {
  }

  virtual ~MouseMotionEventConsumer(void)
  {
  }

  bool operator==(const ConsumerType& b) override
  {
    auto p = dynamic_cast<const Type*>(&b);
    return (
             (p != nullptr)
             && (MouseEventConsumer::operator==(b))
             && (this->dragged_ == p->dragged_)
             && (this->moved_ == p->moved_)
           );
  } // equality comparison operator */

protected:
  virtual LRESULT WmMouseMove(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    Component* component = this->get_Component();

    // call the original WM_MOUSEMOVE handler to deal with enter/exit info
    LRESULT ret = MouseEventConsumer::WmMouseMove(defaultResult, msg, handled);

    MouseButton btn =
      static_cast<MouseButton>(GET_KEYSTATE_WPARAM(msg.wParam));
    if ((GET_KEYSTATE_WPARAM(msg.wParam) & MK_CONTROL) != 0
        || (GET_KEYSTATE_WPARAM(msg.wParam) & MK_SHIFT) != 0
        || GET_KEYSTATE_WPARAM(msg.wParam) == 0)
    {
      MouseEventArguments e(msg, MouseButton::None, 0);
      this->Moved(*component, e);
    }
    else
    {
      MouseEventArguments e(msg,
        MouseEventConsumer::GetButtonFromParam(msg.wParam), 0);
      this->Dragged(*component, e);
    }

    return ret; // 0 if handled
  }

private:
  void RaiseEvent(Component& component, MessageArguments& args)
  {
    this->set_Component(&component);
    args.Result = this->RouteMessage(args.Result, args.Message, args.Handled);
  }
};

}
}
}

#endif