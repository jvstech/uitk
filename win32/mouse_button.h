
#if !defined (JVS_UITK_WIN32_MOUSEBUTTON_H_)
#define JVS_UITK_WIN32_MOUSEBUTTON_H_

#include <windows.h>
#include <cstdint>

namespace jvs
{
namespace uitk
{
namespace win32
{
  enum class MouseButton : uint32_t
  {
    // Control = MK_CONTROL,
    Left = MK_LBUTTON,
    Middle = MK_MBUTTON,
    None = 0,
    Right = MK_RBUTTON,
    // Shift = MK_SHIFT,
    XButton1 = MK_XBUTTON1,
    XButton2 = MK_XBUTTON2
  };

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif