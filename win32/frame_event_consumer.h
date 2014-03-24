
#if !defined (JVS_UITK_WIN32_FRAME_EVENT_CONSUMER_H_)
#define JVS_UITK_WIN32_FRAME_EVENT_CONSUMER_H_

#include <algorithm>
#include <Windows.h>
#include <jvs/uitk/event.h>
#include "frame.h"
#include "message_arguments.h"
#include "frame_event_arguments.h"
#include "frame_closing_arguments.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

class FrameEventConsumer
	: public virtual EventConsumer<Component, MessageArguments>,
	protected MessageHandler
{
public:
	typedef Event<Component&, BasicEventArguments&> FrameEventHandler;
	typedef Event<Component&, FrameClosingArguments&> FrameClosingEventHandler;
	typedef EventConsumer<Component, MessageArguments> ConsumerType;
	typedef FrameEventConsumer Type;

private:
	Component* frame_;
	FrameEventHandler activated_;
	FrameEventHandler closed_;
	FrameClosingEventHandler closing_;
	FrameEventHandler deactivated_;
	FrameEventHandler maximized_;
	FrameEventHandler minimized_;
	FrameEventHandler opened_;
	FrameEventHandler restored_;

public:
	FrameEventHandler& Activated;
	FrameEventHandler& Closed;
	FrameClosingEventHandler& Closing;
	FrameEventHandler& Deactivated;
	FrameEventHandler& Maximized;
	FrameEventHandler& Minimized;
	FrameEventHandler& Opened;
	FrameEventHandler& Restored;

	FrameEventConsumer(void)
		: activated_(),
		closed_(),
		closing_(),
		deactivated_(),
		maximized_(),
		minimized_(),
		opened_(),
		restored_(),
		Activated(activated_),
		Closed(closed_),
		Closing(closing_),
		Deactivated(deactivated_),
		Maximized(maximized_),
		Minimized(minimized_),
		Opened(opened_),
		Restored(restored_)
	{
	}

	FrameEventConsumer(FrameEventConsumer&& src)
		: activated_(std::move(src.activated_)),
		closed_(std::move(src.closed_)),
		closing_(std::move(src.closing_)),
		deactivated_(std::move(src.deactivated_)),
		maximized_(std::move(src.maximized_)),
		minimized_(std::move(src.minimized_)),
		opened_(std::move(src.opened_)),
		restored_(std::move(src.restored_)),
		Activated(activated_),
		Closed(closed_),
		Closing(closing_),
		Deactivated(deactivated_),
		Maximized(maximized_),
		Minimized(minimized_),
		Opened(opened_),
		Restored(restored_)
	{
	}

	virtual ~FrameEventConsumer(void)
	{
	}

	bool operator==(const ConsumerType& src)
	{
		auto p = dynamic_cast<const Type*>(&src);
		return (
			(p != nullptr)
			&& (this->activated_ == p->activated_)
			&& (this->closed_ == p->closed_)
			&& (this->closing_ == p->closing_)
			&& (this->deactivated_ == p->deactivated_)
			&& (this->maximized_ == p->maximized_)
			&& (this->minimized_ == p->minimized_)
			&& (this->opened_ == p->opened_)
			&& (this->restored_ == p->restored_)
			);
	}

protected:

	virtual LRESULT Message(LRESULT defaultResult, MSG& msg, bool& handled)
	{
		if (msg.message == Frame::WM_FIRSTSHOWN)
		{
			this->Opened(*this->frame_, BasicEventArguments());
		}

		return defaultResult;
	}

	virtual LRESULT WmActivate(LRESULT defaultResult, MSG& msg, bool& handled)
	{
		if (msg.wParam != WA_INACTIVE)
		{
			this->Activated(*this->frame_, BasicEventArguments());
		}
		else
		{
			this->Deactivated(*this->frame_, BasicEventArguments());
		}

		return defaultResult;
	}

	virtual LRESULT WmClose(LRESULT defaultResult, MSG& msg, bool& bHandled)
	{
		// TODO: update the close reason
		FrameClosingArguments e(FrameCloseReason::None);
		// TODO: Update cancel based on the "dialog result" of modal frames
		// TODO: Update cancel based on validation of controls on this frame
		// TODO: Propagate event to child frame if this is an MDI frame
		// TODO: Propagate event to frames owned by this one
		if (msg.message != WM_ENDSESSION)
		{
			this->Closing(*this->frame_, e);
			if (msg.message == WM_QUERYENDSESSION)
			{
				defaultResult = (e.Cancel ? 0 : 1);
			} // if (msg.message == WM_QUERYENDSESSION) */
			else
			{
				defaultResult = (e.Cancel ? 1 : 0);
			} // else [if (msg.message == WM_QUERYENDSESSION)] */

			// TODO: If modal, return here.
		}
		else
		{
			e.Cancel = (msg.wParam == 0);
			defaultResult = (e.Cancel ? 1 : 0);
		}
		
		if (msg.message != WM_QUERYENDSESSION)
		{
			if (!(e.Cancel))
			{
				// TODO: Propagate event to child frame if this is an MDI frame
				// TODO: Propagate event to frames owned by this one
				this->Closed(*this->frame_, e);
			} // if
		} // if

		bHandled = e.Cancel;
		return defaultResult /*e.Cancel ? 1 : 0*/;
	}

	virtual LRESULT WmEndSession(LRESULT defaultResult, MSG& msg, bool& handled)
	{
		return this->WmClose(defaultResult, msg, handled);
	}

	virtual LRESULT WmQueryEndSession(LRESULT defaultResult, MSG& msg, 
		bool& handled)
	{
		return this->WmClose(defaultResult, msg, handled);
	}

	virtual LRESULT WmWindowPosChanging(LRESULT defaultResult, MSG& msg, 
		bool& handled)
	{
		auto* frame = dynamic_cast<Frame*>(this->frame_);
		// If (for some reason) this isn't a frame, don't process the event.
		if (frame == nullptr)
		{
			return defaultResult;
		}

		WINDOWPLACEMENT placement;
		placement.length = sizeof(placement);
		::GetWindowPlacement(msg.hwnd, &placement);
		switch (placement.showCmd)
		{
		case SW_NORMAL: 
		case SW_RESTORE:
		case SW_SHOW: 
		case SW_SHOWNA: 
		case SW_SHOWNOACTIVATE:
			if (frame->frame_state() != FrameState::Normal)
			{ 
				FrameEventArguments e(frame->frame_state(), FrameState::Normal);
				this->Restored(*this->frame_, e);
			}

			break;
		
		case SW_SHOWMAXIMIZED: 
			// TODO: Only update if this frame isn't a maximized MDI child
			if (frame->frame_state() != FrameState::Maximized)
			{ 
				FrameEventArguments e(frame->frame_state(), FrameState::Maximized);
				this->Maximized(*this->frame_, e);
			}

			break;

		case SW_SHOWMINIMIZED: 
		case SW_MINIMIZE:
		case SW_SHOWMINNOACTIVE:
			// TODO: Only update if this frame isn't a maximized MDI child
			if (frame->frame_state() != FrameState::Minimized)
			{ 
				FrameEventArguments e(frame->frame_state(), FrameState::Minimized);
				this->Minimized(*this->frame_, e);
			}

			break;

		default:
			break; 

		}

		return defaultResult;
	}

private:
	void RaiseEvent(Component& frame, MessageArguments& args) override
	{
		this->frame_ = &frame;
		args.Result = this->RouteMessage(args.Result, args.Message, 
			args.Handled);
	}
}; //

template <typename EventHandlerT>
static std::unique_ptr<FrameEventConsumer> 
	OnClosing(const EventHandlerT& handler)
{
	auto ret = std::unique_ptr<FrameEventConsumer>(new FrameEventConsumer());
	ret->Closing.Add(handler);
	return std::move(ret);
}

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif /* #if !defined (JVS_UITK_WIN32_FRAME_EVENT_CONSUMER_H_) */
