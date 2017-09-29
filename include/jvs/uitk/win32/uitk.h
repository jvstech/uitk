
#if !defined (JVS_UITK_WIN32_H_)
#define JVS_UITK_WIN32_H_

#include <Windows.h>

#if defined _MSC_VER
#	pragma comment(lib, "comctl32.lib") 
#	include <commctrl.h>
#	pragma comment(linker, "/manifestdependency:\"type='win32' \
							name='Microsoft.Windows.Common-Controls' \
							version='6.0.0.0' \
							processorArchitecture='*' \
							publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

// application helpers
#include "simple_message_loop.h"

// components
#include "button.h"
#include "frame.h"
#include "label.h"
#include "list.h"
#include "textbox.h"

// event consumers
#include "component_event_consumer.h"
#include "frame_event_consumer.h"
#include "focus_event_consumer.h"
#include "key_event_consumer.h"
#include "mouse_motion_event_consumer.h"
#include "mouse_wheel_event_consumer.h"

// directives
#include "component_directives.h"

#endif