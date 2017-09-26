
#if !defined (JVS_UITK_WIN32_FRAME_CLOSING_ARGUMENTS_H_)
#define JVS_UITK_WIN32_FRAME_CLOSING_ARGUMENTS_H_

#include "jvs/uitk/event_arguments.h"
#include "frame_close_reason.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

struct FrameClosingArguments : BasicEventArguments
{
	FrameClosingArguments(FrameCloseReason::Enum closeReason, bool cancel = false)
		: CloseReason(closeReason), 
		Cancel(cancel)
	{
	}

	FrameCloseReason::Enum CloseReason;
	bool Cancel;
}; // struct FrameClosingArguments

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif