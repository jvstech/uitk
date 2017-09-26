
#if !defined (JVS_UITK_WIN32_COMPONENT_EVENT_CONSUMER_H_)
#define JVS_UITK_WIN32_COMPONENT_EVENT_CONSUMER_H_

#include <functional>
#include <utility>
#include <windows.h>
#include "jvs/uitk/event_consumer.h"
#include "component_msghandler.h"
#include "jvs/uitk/event_arguments.h"
#include "message_arguments.h"
#include "component.h"
#include "jvs/uitk/event.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

class ComponentEventConsumer : 
  public virtual EventConsumer<Component, MessageArguments>,
  protected MessageHandler
{
public:
  typedef Event<Component&, BasicEventArguments&> ComponentEventHandler;
  typedef EventConsumer<Component, MessageArguments> ConsumerType;
  typedef ComponentEventConsumer Type;

private:
  Component* component_;
  ComponentEventHandler moveEvent_;
  ComponentEventHandler hiddenEvent_;
  ComponentEventHandler shownEvent_;
  ComponentEventHandler resizedEvent_;

  // non-copyable
  ComponentEventConsumer(const ComponentEventConsumer&) = delete;
  //  : moveEvent_(),
  //  hiddenEvent_(),
  //  shownEvent_(),
  //  resizedEvent_(),
  //  Moved(moveEvent_),
  //  Hidden(hiddenEvent_),
  //  Shown(shownEvent_),
  //  Resized(resizedEvent_)
  //{
  //}
  
public:
  
  ComponentEventHandler& Moved;
  ComponentEventHandler& Hidden;
  ComponentEventHandler& Shown;
  ComponentEventHandler& Resized;

  ComponentEventConsumer()
    : moveEvent_(),
    hiddenEvent_(),
    shownEvent_(),
    resizedEvent_(),
    Moved(moveEvent_),
    Hidden(hiddenEvent_),
    Shown(shownEvent_),
    Resized(resizedEvent_)
  {
  }

  ComponentEventConsumer(ComponentEventConsumer&& src)
    : moveEvent_(std::move(src.moveEvent_)),
    hiddenEvent_(std::move(src.hiddenEvent_)),
    shownEvent_(std::move(src.shownEvent_)),
    resizedEvent_(std::move(src.resizedEvent_)),
    Moved(moveEvent_),
    Hidden(hiddenEvent_),
    Shown(shownEvent_),
    Resized(resizedEvent_)
  {
  }

  virtual ~ComponentEventConsumer()
  {
  }

  bool operator==(const ConsumerType& b) override
  {
    auto p = dynamic_cast<const Type*>(&b);
    return (
      (p != nullptr)
      && (this->moveEvent_ == p->moveEvent_)
      && (this->hiddenEvent_ == p->hiddenEvent_)
      && (this->resizedEvent_ == p->resizedEvent_)
      && (this->shownEvent_ == p->shownEvent_)
      );
  }

protected:
  virtual LRESULT WmMove(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    this->Moved(*this->component_, BasicEventArguments());
    return defaultResult;
  }

  virtual LRESULT WmShowWindow(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    if (static_cast<BOOL>(msg.wParam) == TRUE)
    {
      this->Shown(*this->component_, BasicEventArguments());
    }
    else
    {
      this->Hidden(*this->component_, BasicEventArguments());
    }

    return defaultResult;
  }

  virtual LRESULT WmSize(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    this->Resized(*this->component_, BasicEventArguments());
    return defaultResult;
  }

private:

  void RaiseEvent(Component& component, MessageArguments& args) override
  {
    this->component_ = &component;
    args.Result = this->RouteMessage(args.Result, args.Message, 
      args.Handled);
  }
}; // class ComponentEventConsumer

//
// event handler extensions
//

template <typename EventHandlerT>
static std::shared_ptr<ComponentEventConsumer> 
  OnMoved(const EventHandlerT& handler)
{
  auto ret = std::make_shared<ComponentEventConsumer>();
  ret->Moved.Add(handler);
  return std::move(ret);
}

template <typename EventHandlerT>
static std::shared_ptr<ComponentEventConsumer> 
  OnHidden(const EventHandlerT& handler)
{
  auto ret = std::make_shared<ComponentEventConsumer>();
  ret->Hidden.Add(handler);
  return std::move(ret);
}

template <typename EventHandlerT>
static std::shared_ptr<ComponentEventConsumer> 
  OnShown(const EventHandlerT& handler)
{
  auto ret = std::make_shared<ComponentEventConsumer>();
  ret->Shown.Add(handler);
  return std::move(ret);
}

template <typename EventHandlerT>
static std::shared_ptr<ComponentEventConsumer> 
  OnResized(const EventHandlerT& handler)
{
  auto ret = std::make_shared<ComponentEventConsumer>();
  ret->Resized.Add(handler);
  return std::move(ret);
}

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif
