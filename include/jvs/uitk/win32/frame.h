
#if !defined (JVS_UITK_WIN32_FRAME_H_)
#define JVS_UITK_WIN32_FRAME_H_

#include <map>
#include <cstdint>
#include <bitset>
#include "component.h"
#include "frame_state.h"
#include "frame_states.h"

namespace jvs
{
namespace uitk
{ 
namespace win32
{

class Frame : public virtual Component
{
private:
  // flags
  enum InternalFlags
  {
    BoundsWidthIsClientSize,
    BoundsHeightIsClientSize,
    SizeLockedByOs
  };

  // members
  FrameState::Enum state_;
  FrameState::Enum prevState_;
  Point restoredSize_;
  Point restoredLoc_;
  std::bitset<8> flags_;
    
  // constants
  static const DWORD Style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | 
    WS_CLIPSIBLINGS;
  static const DWORD ExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

public:
  // custom window message
  static UINT WM_FIRSTSHOWN;

  Frame()
    : Component(),
    state_(FrameState::Normal),
    prevState_(FrameState::Normal),
    restoredSize_(),
    restoredLoc_(),
    flags_()
  {
    //this->set_width(300);
    //this->set_height(200);
    this->set_background_color(::GetSysColor(COLOR_3DFACE));
    this->Initialize();
  }

  virtual ~Frame()
  {
  }

  FrameState::Enum frame_state() const
  {
    return this->state_;
  }

  Frame& frame_state(FrameState::Enum& dst)
  {
    dst = this->state_;
    return *this;
  }

  Frame& set_frame_state(const FrameState::Enum& state)
  {
    if (state != this->state_)
    {
      if (this->IsCreated() && ::IsWindowVisible(*this))
      {
        ::ShowWindow(*this, FrameState::GetShowWindowCommand(state));
      }

      this->state_ = state;
    } // if (state != this->state_)

    return *this;
  }

  FrameState::Enum frame_state_previous() const
  {
    return this->prevState_;
  }

  Frame& frame_state_previous(FrameState::Enum& dst)
  {
    dst = this->prevState_;
    return *this;
  }

protected:

  ComponentCreationParameters GetCreationParameters() const override
  {
    auto createParams = Component::GetCreationParameters();
    createParams.WindowStyles = Frame::Style;
    createParams.WindowExStyles = Frame::ExStyle;
    return createParams;
  }

  Point GetDefaultSize() const override
  {
    return Point(300, 300);
  }

  Frame& GetProvider() override
  {
    return *this;
  }

  virtual void OnCreated()
  {
    if (Frame::WM_FIRSTSHOWN == ~0)
    {
      Frame::WM_FIRSTSHOWN = 
        ::RegisterWindowMessage(TEXT("JutFrameFirstShown"));
    }
  }

  virtual void OnFirstShown()
  {
    ::SendMessage(*this, WM_FIRSTSHOWN, 0, 0);
  }

private:

  virtual LRESULT WmCreate(LRESULT defaultResult, MSG& msg, bool& handled)
  {
    auto ret = Component::WmCreate(defaultResult, msg, handled);
    STARTUPINFO si;
    si.cb = sizeof(si);
    ::GetStartupInfo(&si);
    if (this->IsTopLevel() &&	(si.dwFlags & STARTF_USESHOWWINDOW) != 0)
    {
      switch (si.wShowWindow)
      {
      case SW_MAXIMIZE:
        this->set_frame_state(FrameState::Maximized);
        break;
      case SW_MINIMIZE:
        this->set_frame_state(FrameState::Minimized);
        break;
      } // switch (si.wShowWindow)
    }

    return ret;
  }

  virtual LRESULT WmWindowPosChanged(LRESULT defaultResult, MSG& msg, 
    bool& handled)
  {
    this->updateFrameState();
    return Component::WmWindowPosChanged(defaultResult, msg, handled);
  }

  virtual LRESULT WmSysCommand(LRESULT defaultResult,MSG& msg, bool& bHandled)
  {
    bHandled = false;
    return 0;
  }

  void updateFrameState() 
  {
    if (this->IsCreated())
    { 
      this->prevState_ = this->frame_state(); 
      WINDOWPLACEMENT wp;
      wp.length = sizeof(wp); 
      ::GetWindowPlacement(*this, &wp);
      switch (wp.showCmd)
      {
      case SW_NORMAL: 
      case SW_RESTORE:
      case SW_SHOW: 
      case SW_SHOWNA: 
      case SW_SHOWNOACTIVATE:
        if (this->state_ != FrameState::Normal)
        { 
          this->state_ = FrameState::Normal;
        }

        break;

      case SW_SHOWMAXIMIZED: 
        // TODO: Only update if this frame isn't a maximized MDI child
        this->state_ = FrameState::Maximized; 
        break;

      case SW_SHOWMINIMIZED: 
      case SW_MINIMIZE:
      case SW_SHOWMINNOACTIVE:
        // TODO: Only update if this frame isn't a maximized MDI child
        this->state_ = FrameState::Minimized;
        break;

      case SW_HIDE: 
      default:
        break; 

      } // switch (wp.showCmd)

      // // If we used to be normal and we just became minimized or maximized,
      // // stash off our current bounds so we can properly restore. 
      // //
      // if (this->prevState_ == FrameState::Normal && 
      //	this->frame_state() != FrameState::Normal)
      // { 
      //	if (this->frame_state() == FrameState::Minimized)
      //	{
      //		SuspendLayoutForMinimize(); 
      //	}

      //	this->restoredSize_ = this->client_size();
      //	this->setIntFrameState(FrameStates::BoundsWidthIsClientSize, true); 
      //	this->setIntFrameState(FrameStates::BoundsHeightIsClientSize, true);
      //	restoredWindowBoundsSpecified = BoundsSpecified.Size; 
      //	this->restoredLoc_ = this->get_Location(); 
      //	restoredWindowBoundsSpecified |= BoundsSpecified.Location;

      //	// stash off restoreBounds As well...
      //	restoreBounds.Size = Size;
      //	restoreBounds.Location = Location;
      // } 

      // // If we just became normal or maximized resume 
      // if (this->prevState_ == FrameState::Minimized && 
      //	this->frame_state() != FrameState::Minimized)
      // { 
      //	ResumeLayoutFromMinimize();
      // } 

      // switch (this->frame_state())
      // {
      // case FrameState::Normal:
      //	this->setIntFrameState(FrameStates::SizeLockedByOs, false);
      //	break;

      // case FrameState::Maximized: 
      // case FrameState::Minimized: 
      //	this->setIntFrameState(FrameStates::SizeLockedByOs, true);
      //	break; 
      // }

      // if (this->prevState_ != this->frame_state())
      // {
      //	AdjustSystemMenu(); 
      // }
    } // if (this->IsCreated())
  } // updateFrameState
}; /* class Frame */

UINT Frame::WM_FIRSTSHOWN = ~0;

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif