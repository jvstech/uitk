#if !defined (JVS_UITK_WIN32_MOUSE_WHEEL_EVENT_CONSUMER_H_)
#define JVS_UITK_WIN32_MOUSE_WHEEL_EVENT_CONSUMER_H_

#include <windows.h>
#include "jvs/uitk/event.h"
#include "component.h"
#include "message_arguments.h"
#include "mouse_wheel_event_arguments.h"
#include "mouse_event_consumer.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

class MouseWheelEventConsumer :
  public virtual MouseEventConsumer
{
public:
  using MouseWheelEventHandler = Event<Component&, MouseWheelEventArguments&>;
  using ConsumerType = MouseEventConsumer::ConsumerType;
  using Type = MouseWheelEventConsumer;

private:
  MouseWheelEventHandler wheelMoved_;

public:
  MouseWheelEventHandler& WheelMoved;

  MouseWheelEventConsumer()
    : MouseEventConsumer(),
    wheelMoved_(),
    WheelMoved(wheelMoved_)
  {
  }

  virtual ~MouseWheelEventConsumer()
  {
  }

  bool operator==(const ConsumerType& b)
  {
    auto p = dynamic_cast<const Type*>(&b);
    return (
      (p != nullptr)
      && (MouseEventConsumer::operator==(b))
      && (this->wheelMoved_ == p->wheelMoved_)
      );
  }

protected:
  virtual LRESULT WmMouseWheel(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    MouseWheelEventArguments e(msg);
    this->WheelMoved(*this->get_Component(), e);
    return (e.Handled ? 0 : 1);
  }

private:
  void RaiseEvent(Component& component, MessageArguments& args)
  {
    this->set_Component(&component);
    args.Result = this->RouteMessage(args.Result, args.Message, args.Handled);
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif