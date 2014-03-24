
#if !defined (JVS_UITK_WIN32_MOUSE_EVENT_CONSUMER_H_)
#define JVS_UITK_WIN32_MOUSE_EVENT_CONSUMER_H_

#include <map>
#include <utility>
#include <Windows.h>
#include <jvs/uitk/event.h>
#include <jvs/uitk/event_consumer.h>
#include "component.h"
#include "component_msghandler.h"
#include "message_arguments.h"
#include "mouse_event_arguments.h"
#include "mouse_button.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

class MouseEventConsumer :
  public virtual EventConsumer<Component, MessageArguments>,
  protected MessageHandler
{
public:
  typedef Event<Component&, MouseEventArguments&> MouseEventHandler;
  typedef EventConsumer<Component, MessageArguments> ConsumerType;
  typedef MouseEventConsumer Type;

private:
  std::map<std::pair<Component*, MouseButton>, bool> mouseUpPending;
  std::map<Component*, bool> mouseEnterPending;
  std::map<Component*, bool> trackingMouse;
  std::map<Component*, TRACKMOUSEEVENT> trackMouseEvent;

  Component* component_;
  MouseEventHandler clicked_;
  MouseEventHandler entered_;
  MouseEventHandler exited_;
  MouseEventHandler hovered_;
  MouseEventHandler pressed_;
  MouseEventHandler released_;


public:

  MouseEventHandler& Clicked;
  MouseEventHandler& Entered;
  MouseEventHandler& Exited;
  MouseEventHandler& Hovered;
  MouseEventHandler& Pressed;
  MouseEventHandler& Released;

  MouseEventConsumer(void)
    : component_(nullptr),
      mouseUpPending(),
      mouseEnterPending(),
      trackingMouse(),
      trackMouseEvent(),
      clicked_(),
      entered_(),
      exited_(),
      hovered_(),
      pressed_(),
      released_(),
      Clicked(clicked_),
      Entered(entered_),
      Exited(exited_),
      Hovered(hovered_),
      Pressed(pressed_),
      Released(released_)
  {
  }

  virtual ~MouseEventConsumer(void)
  {
  }

  virtual bool operator==(const ConsumerType& b) override
  {
    auto p = dynamic_cast<const Type*>(&b);
    return (
             (p != nullptr)
             && (this->clicked_ == p->clicked_)
             && (this->entered_ == p->entered_)
             && (this->exited_ == p->exited_)
             && (this->hovered_ == p->hovered_)
             && (this->pressed_ == p->pressed_)
             && (this->released_ == p->released_)
           );
  }

protected:

  Component* get_Component(void) const
  {
    return this->component_;
  }

  void set_Component(Component* component)
  {
    this->component_ = component;
  }

  virtual LRESULT OnButtonDown(MouseButton button, LRESULT defaultResult,
                               MSG& msg, bool& handled)
  {
    mouseUpPending[std::make_pair(this->component_, button)] = true;
    MouseEventArguments e(msg, button, 0);
    this->Pressed(*this->component_, e);
    return (e.Handled ? 0 : 1);
  }

  virtual LRESULT WmLButtonDown(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    return this->OnButtonDown(MouseButton::Left, defaultResult, msg, handled);
  }

  virtual LRESULT WmMButtonDown(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    return this->OnButtonDown(MouseButton::Middle, defaultResult, msg, handled);
  }

  virtual LRESULT WmRButtonDown(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    return this->OnButtonDown(MouseButton::Right, defaultResult, msg, handled);
  }

  virtual LRESULT WmXButtonDown(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    MouseButton button = (GET_XBUTTON_WPARAM(msg.wParam) == XBUTTON1 ?
                          MouseButton::XButton1 : MouseButton::XButton2);
    return this->OnButtonDown(button, defaultResult, msg, handled);
  }

  virtual LRESULT OnButtonUp(MouseButton button, LRESULT defaultResult,
                             MSG& msg, bool& handled)
  {
    bool mouseClick = this->getMouseUpPending(std::make_pair(this->component_,
                      button));
    int clicks = mouseClick ? 1 : 0;
    MouseEventArguments e(msg, button, clicks);
    this->Released(*this->component_, e);
    if (mouseClick)
    {
      MouseEventArguments e2(msg, button, clicks);
      this->Clicked(*this->component_, e2);
    }

    return (e.Handled ? 0 : 1);
  }

  virtual LRESULT WmLButtonUp(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    return this->OnButtonUp(MouseButton::Left, defaultResult, msg, handled);
  }

  virtual LRESULT WmMButtonUp(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    return this->OnButtonUp(MouseButton::Middle, defaultResult, msg, handled);
  }

  virtual LRESULT WmRButtonUp(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    return this->OnButtonUp(MouseButton::Right, defaultResult, msg, handled);
  }

  virtual LRESULT WmXButtonUp(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    MouseButton button = (GET_XBUTTON_WPARAM(msg.wParam) == XBUTTON1 ?
                          MouseButton::XButton1 : MouseButton::XButton2);
    return this->OnButtonUp(button, defaultResult, msg, handled);
  }

  virtual LRESULT WmMouseMove(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    handled = false;
    Component* component = this->component_;
    if (!this->getTrackingMouse(component))
    {
      this->hookMouse(component);
      if (this->getMouseEnterPending(component))
      {
        this->mouseEnterPending[component] = false;
        MouseEventArguments e(msg, MouseButton::None, 0);
        this->Entered(*component, e);
      }
    }

    return 1; // 0 if handled
  }

  virtual LRESULT WmMouseHover(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    MouseEventArguments e(msg, MouseButton::None, 0);
    this->Hovered(*this->component_, e);
    return (e.Handled ? 0 : 1);
  }

  virtual LRESULT WmMouseLeave(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    Component* component = this->component_;
    this->mouseEnterPending[component] = true;
    this->clearMouseUpPending(component);
    this->unhookMouse(component);
    MouseEventArguments e(msg, MouseButton::None, 0);
    this->Exited(*component, e);
    return (e.Handled ? 0 : 1);
  }

  static MouseButton GetButtonFromParam(WPARAM wparam)
  {
    if ((GET_KEYSTATE_WPARAM(wparam) & MK_LBUTTON) != 0)
    {
      return MouseButton::Left;
    }
    else if ((GET_KEYSTATE_WPARAM(wparam) & MK_MBUTTON) != 0)
    {
      return MouseButton::Middle;
    }
    else if ((GET_KEYSTATE_WPARAM(wparam) & MK_RBUTTON) != 0)
    {
      return MouseButton::Right;
    }
    else if ((GET_KEYSTATE_WPARAM(wparam) & MK_XBUTTON1) != 0)
    {
      return MouseButton::XButton1;
    }
    else if ((GET_KEYSTATE_WPARAM(wparam) & MK_XBUTTON2) != 0)
    {
      return MouseButton::XButton2;
    }

    return MouseButton::None;
  }

private:

  void clearMouseUpPending(Component* component)
  {
    this->mouseUpPending[std::make_pair(component, MouseButton::Left)]
      = false;
    this->mouseUpPending[std::make_pair(component, MouseButton::Middle)]
      = false;
    this->mouseUpPending[std::make_pair(component, MouseButton::Right)]
      = false;
    this->mouseUpPending[std::make_pair(component, MouseButton::XButton1)]
      = false;
    this->mouseUpPending[std::make_pair(component, MouseButton::XButton2)]
      = false;
  }

  void hookMouse(Component* component)
  {
    if (component->IsCreated()
        && (!(this->getTrackingMouse(component))))
    {
      this->trackingMouse[component] = true;
      this->trackMouseEvent[component] = TRACKMOUSEEVENT();
      this->trackMouseEvent[component].cbSize = sizeof(TRACKMOUSEEVENT);
      this->trackMouseEvent[component].dwHoverTime = 100;
      this->trackMouseEvent[component].dwFlags = TME_LEAVE | TME_HOVER;
      this->trackMouseEvent[component].hwndTrack = *component;
      // this raises WM_MOUSEHOVER and WM_MOUSEEXIT
      ::TrackMouseEvent(&this->trackMouseEvent[component]);
    }
  }

  void unhookMouse(Component* component)
  {
    this->trackingMouse[component] = false;
  }

  template <typename IdentifierT, typename MapT>
  bool getState(IdentifierT component, MapT& stateMap, 
    bool defaultState = false)
  {
    auto it = stateMap.find(component);
    if (it != stateMap.end())
    {
      return it->second;
    }

    stateMap[component] = defaultState;
    return defaultState;
  }

  bool getMouseUpPending(const std::pair<Component*, MouseButton>& button)
  {
    return this->getState(button, this->mouseUpPending);
  }

  bool getMouseEnterPending(Component* component)
  {
    return this->getState(component, this->mouseEnterPending);
  }

  bool getTrackingMouse(Component* component)
  {
    return this->getState(component, this->trackingMouse);
  }

  virtual void OnAttached(Component& component)
  {
    this->mouseEnterPending[&component] = true;
    this->trackingMouse[&component] = false;
  }

  void RaiseEvent(Component& component, MessageArguments& args)
  {
    this->component_ = &component;
    args.Result = this->RouteMessage(args.Result, args.Message,
                                     args.Handled);
  }
};

template <typename EventHandlerT>
static std::unique_ptr<MouseEventConsumer>
OnClick(const EventHandlerT& handler)
{
  auto ret = std::unique_ptr<MouseEventConsumer>(new MouseEventConsumer());
  ret->Clicked.Add(handler);
  return std::move(ret);
}

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif