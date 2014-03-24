
#if !defined (JVS_UITK_WIN32_FOCUS_EVENT_CONSUMER_H_)
#define JVS_UITK_WIN32_FOCUS_EVENT_CONSUMER_H_

#include <algorithm>
#include <Windows.h>
#include <jvs/uitk/event.h>
#include <jvs/uitk/event_consumer.h>
#include "component.h"
#include "message_arguments.h"
#include "focus_event_arguments.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

class FocusEventConsumer :
  public virtual EventConsumer<Component, MessageArguments>,
  protected MessageHandler
{
public:
  typedef Event<Component&, FocusEventArguments&> FocusEventHandler;
  typedef EventConsumer<Component, MessageArguments> ConsumerType;
  typedef FocusEventConsumer Type;

private:
  Component* component_;
  FocusEventHandler gained_;
  FocusEventHandler lost_;

public:

  FocusEventHandler& Gained;
  FocusEventHandler& Lost;
  
  FocusEventConsumer(void)
    : gained_(),
    lost_(),
    Gained(gained_),
    Lost(lost_)
  {
  }

  virtual ~FocusEventConsumer(void)
  {
  }

  bool operator==(const ConsumerType& b) override
  {
    auto p = dynamic_cast<const Type*>(&b);
    return (
      (p != nullptr)
      && (this->gained_ == p->gained_)
      && (this->lost_ == p->lost_)
      );
  }

protected:

  virtual LRESULT OnFocusChanged(LRESULT defaultResult, MSG& msg, bool& handled,
    bool gained)
  {
    Component* component = this->component_;
    HWND oppositeHandle = reinterpret_cast<HWND>(msg.wParam);
    Component* oppositeComponent = nullptr;
    auto componentSet = Component::GetCreatedComponents();
    auto match = std::find_if(componentSet.begin(), componentSet.end(), 
      [&](const Component::OwnedComponent& c)-> bool
      {
        return c->handle() == oppositeHandle;
      });

    if (match != componentSet.end())
    {
      oppositeComponent = match->get();
    }

    FocusEventArguments e(oppositeComponent);
    if (gained)
    {
      this->Gained(*component, e);
    }
    else
    {
      this->Lost(*component, e);
    }
    
    return 1; // 0 for handled
  }

  virtual LRESULT WmSetFocus(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    return this->OnFocusChanged(defaultResult, msg, handled, true);
  }

  virtual LRESULT WmKillFocus(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    return this->OnFocusChanged(defaultResult, msg, handled, false);
  }

private:
  void RaiseEvent(Component& component, MessageArguments& args)
  {
    this->component_ = &component;
    args.Result = this->RouteMessage(args.Result, args.Message, args.Handled);
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif