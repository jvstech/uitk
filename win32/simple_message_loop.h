
#if !defined (JVS_UITK_WIN32_SIMPLE_MESSAGE_LOOP_H_)
#define JVS_UITK_WIN32_SIMPLE_MESSAGE_LOOP_H_

#include <windows.h>

namespace jvs
{
namespace uitk
{
namespace win32
{
	
class SimpleMessageLoop
{
public:

	SimpleMessageLoop(void)
	{
	}

	virtual ~SimpleMessageLoop(void)
	{
	}

	static int Run(void)
	{
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			/*if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{*/
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			/*}*/
		}

		return msg.wParam;
	}
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif