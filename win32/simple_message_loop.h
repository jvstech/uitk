
#if !defined (JVS_UITK_WIN32_SIMPLE_MESSAGE_LOOP_H_)
#define JVS_UITK_WIN32_SIMPLE_MESSAGE_LOOP_H_

#include <windows.h>

#include "jvs/uitk/win32/types.h"

namespace jvs
{
namespace uitk
{
namespace win32
{
	
class SimpleMessageLoop
{
public:

	SimpleMessageLoop()
	{
	}

	virtual ~SimpleMessageLoop()
	{
	}

	static WParam Run()
	{
		MSG msg;
		while (GetMessageW(&msg, NULL, 0, 0))
		{
			/*if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{*/
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
			/*}*/
		}

		return msg.wParam;
	}
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif