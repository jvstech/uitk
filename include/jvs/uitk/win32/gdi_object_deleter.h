
#if !defined (JVS_UITK_WIN32_GDI_OBJECT_DELETER_H_)
#define JVS_UITK_WIN32_GDI_OBJECT_DELETER_H_

#include <windows.h>
#include <utility> // for std::pair

#include "jvs/uitk/win32/types.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

struct GdiObjectDisposer
{
  template <typename GdiObjectT>
  void operator()(GdiObjectT gdiObject)
  {
    GdiObjectDisposer::Dispose(gdiObject);
  }

  template <typename GdiObjectT>
  static void Dispose(GdiObjectT gdiObject)
  {
    ::DeleteObject(gdiObject);
  }
};


// used to auto-delete GDI objects stored in smart pointers
template <typename GdiObjectT>
struct GdiObjectDeleter
{
  using PointerType = GdiObjectT*;

  void operator()(PointerType gdiObject)
  {
    GdiObjectDeleter::Delete(gdiObject);
  }

  static void Delete(PointerType gdiObject)
  {
    if (gdiObject != nullptr)
    {
      GdiObjectDisposer::Dispose(*gdiObject);
      delete gdiObject;
    }
  }

};

template <>
struct GdiObjectDeleter<DeviceContextHandle>
{
  using PointerType = DeviceContextHandle*;
  WindowHandle hwnd;

  GdiObjectDeleter(WindowHandle wnd)
    : hwnd(wnd)
  {
  }

  void operator()(PointerType hdc)
  {
    if (hdc != nullptr)
    {
      ::ReleaseDC(hwnd, *hdc);
    }

    delete hdc;
  }
};

template <>
struct GdiObjectDeleter<std::pair<DeviceContextHandle, WindowHandle>>
{
  using ContextPair = std::pair<DeviceContextHandle, WindowHandle>;
  using PointerType = ContextPair*;

  void operator()(PointerType ctx)
  {
    if (ctx->first != nullptr)
    {
      ::ReleaseDC(
        ctx->second, // DeviceContextHandle
        ctx->first // WindowHandle
        );
    }

    delete ctx;
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs
#endif