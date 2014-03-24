
#if !defined (JVS_UITK_WIN32_FRAME_EVENT_ARGUMENTS_H_)
#define JVS_UITK_WIN32_FRAME_EVENT_ARGUMENTS_H_

#include <jvs/uitk/event_arguments.h>
#include "frame.h"
#include "frame_state.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

struct FrameEventArguments : BasicEventArguments
{
	FrameState::Enum NewState;
	FrameState::Enum OldState;
	
	FrameEventArguments(FrameState::Enum oldState, FrameState::Enum newState)
		: OldState(oldState),
		NewState(NewState)
	{
	}
}; // struct FrameEventArguments

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif

