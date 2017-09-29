
#if !defined (JVS_UITK_WIN32_FRAME_STATE_H_)
#define JVS_UITK_WIN32_FRAME_STATE_H_

#include <Windows.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

namespace FrameState
{
	enum Enum
	{
		Maximized = 2,
		Minimized = 1,
		Normal = 0
	};

	// converts a FrameState::Enum in to a system command value that can be used
	// to tell a frame to change its state
	static WPARAM GetSysCommand(FrameState::Enum state)
	{
		switch (state)
		{
		case Maximized:
			return SC_MAXIMIZE;
		case Minimized:
			return SC_MINIMIZE;
		default:
			return SC_RESTORE;
		}
	}

	// converts a FrameState::Enum in to a ShowWindow parameter
	static int GetShowWindowCommand(FrameState::Enum state)
	{
		switch (state)
		{
		case Maximized:
			return SW_SHOWMAXIMIZED;
		case Minimized:
			return SW_SHOWMINIMIZED;
		default:
			return SW_SHOWNORMAL;
		}
	}

	// converts a SW_* variable in to its equivalent FrameState::Enum
	static FrameState::Enum FromShowWindowCommand(int sw)
	{
		switch (sw)
		{
		case SW_NORMAL: 
		case SW_RESTORE:
		case SW_SHOW: 
		case SW_SHOWNA: 
		case SW_SHOWNOACTIVATE:
			return FrameState::Normal;

		case SW_SHOWMAXIMIZED:
			return FrameState::Maximized;

		case SW_MINIMIZE:
		case SW_SHOWMINIMIZED:
		case SW_SHOWMINNOACTIVE:
			return FrameState::Minimized;

		default:
			return FrameState::Normal;

		}
	}
} // namespace FrameState

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif