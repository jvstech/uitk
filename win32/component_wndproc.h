#if !defined(JVS_UITK_WIN32_COMPONENT_WNDPROC_H_)
#define JVS_UITK_WIN32_COMPONENT_WNDPROC_H_

#include "jvs/uitk/win32/types.h"
#include "component.h"

#if defined (_MSC_VER)
#define Win32CallbackFunc(x) __stdcall x
#else
#define Win32CallbackFunc(x) x __attribute__((stdcall))
#endif

namespace jvs
{
namespace uitk
{

class Component;

namespace win32
{

// Currently unused; needs to be implemented

//LResult Win32CallbackFunc(ComponentWndProc(WindowHandle hWnd, UInt uMsg, 
//  WParam wParam, LParam lParam))
//{
//  Component* component = reinterpret_cast<Component*>(::GetWindowLongPtrW(hWnd, 0));
//  return component->WindowProc(hWnd, uMsg, wParam, lParam);
//}

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif // !JVS_UITK_WIN32_COMPONENT_WNDPROC_H_
