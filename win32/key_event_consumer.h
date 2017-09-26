
#if !defined (JVS_UITK_WIN32_KEY_EVENT_CONSUMER_H_)
#define JVS_UITK_WIN32_KEY_EVENT_CONSUMER_H_

#include <functional>
#include <windows.h>
#include "jvs/uitk/event.h"
#include "jvs/uitk/event_consumer.h"
#include "component_msghandler.h"
#include "keyboard.h"
#include "key_event_arguments.h"
#include "message_arguments.h"
#include "component.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

  class KeyEventConsumer : 
    public virtual EventConsumer<Component, MessageArguments>,
    protected MessageHandler
  {
  public:
    typedef Event<Component&, KeyEventArguments&> KeyEventHandler;
    typedef EventConsumer<Component, MessageArguments> ConsumerType;
    typedef KeyEventConsumer Type;

  private:
    Component* component_;
    KeyEventHandler keyDownEvent_;
    KeyEventHandler keyUpEvent_;
    KeyEventHandler keyPressEvent_;
    
  public:
    KeyEventHandler& KeyDown;
    KeyEventHandler& KeyUp;
    KeyEventHandler& KeyPress;

    KeyEventConsumer()
      : component_(nullptr),
      keyDownEvent_(),
      keyUpEvent_(),
      keyPressEvent_(),
      KeyDown(keyDownEvent_),
      KeyUp(keyUpEvent_),
      KeyPress(keyPressEvent_)
    {
    }

    virtual ~KeyEventConsumer()
    {
    }

    bool operator==(const ConsumerType& b) override
    {
      auto p = dynamic_cast<const Type*>(&b);
      return (
        (p != nullptr)
        && (this->keyDownEvent_ == p->keyDownEvent_)
        && (this->keyUpEvent_ == p->keyUpEvent_)
        && (this->keyPressEvent_ == p->keyPressEvent_)
        );
    }

  protected:

    LRESULT WmSysChar(LRESULT defaultResult, MSG& msg, bool& handled)
    {
      return this->WmChar(defaultResult, msg, handled);
    }
    
    LRESULT WmChar(LRESULT defaultResult, MSG& msg, bool& handled)
    {
      KeyEventArguments e = Keyboard::GetKeyPressEventArgs(msg);
      this->KeyPress(*this->component_, e);
      if (e.Handled)
      {
        handled = true;
        return 0;
      }

      return defaultResult;
    }

    LRESULT WmKeyDown(LRESULT defaultResult, MSG& msg, bool& handled)
    {
      KeyEventArguments e = Keyboard::GetKeyEventArguments(msg);
      this->KeyDown(*this->component_, e);
      if (e.Handled)
      {
        handled = true;
        return 0;
      }

      return defaultResult;
    }

    LRESULT WmKeyUp(LRESULT defaultResult, MSG& msg, bool& handled)
    {
      KeyEventArguments e = Keyboard::GetKeyEventArguments(msg);

      this->KeyUp(*this->component_, e);
      if (e.Handled)
      {
        handled = true;
        return 0;
      }

      return defaultResult;
    }

  private:

    void RaiseEvent(Component& component, MessageArguments& args)
    {
      this->component_ = &component;
      args.Result = this->RouteMessage(args.Result, args.Message, 
        args.Handled);
    }
};

template <typename EventHandlerT>
static std::shared_ptr<KeyEventConsumer> 
OnKeyPress(const EventHandlerT& handler)
{
  auto ret = std::make_shared<KeyEventConsumer>();
  ret->KeyPress.Add(handler);
  return std::move(ret);
}


}
}
}

#endif