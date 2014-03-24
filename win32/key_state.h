
#if !defined (JVS_UITK_WIN32_KEY_STATE_H_)
#define JVS_UITK_WIN32_KEY_STATE_H_

#include <windows.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

union KeyState
{
  LPARAM LParam;
  struct
  {
    unsigned RepeatCount : 16;
    unsigned ScanCode : 8;
    unsigned Extended : 1;
    unsigned Reserved : 4;
    unsigned Context : 1;
    unsigned WasDownBeforeEvent : 1;
    unsigned Transitioning : 1;
  };
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif