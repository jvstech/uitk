
#if !defined (JVS_UITK_WIN32_GDI_OBJECT_DELETER_H_)
#define JVS_UITK_WIN32_GDI_OBJECT_DELETER_H_

#include <windows.h>
#include <utility> // for std::pair

#include <jvs/uitk/win32/types.h>

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
  typedef GdiObjectT* PointerType;

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
struct GdiObjectDeleter<DeviceContextHandleType>
{
  typedef DeviceContextHandleType* PointerType;
  WindowHandleType hwnd;

  GdiObjectDeleter(WindowHandleType wnd)
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
struct GdiObjectDeleter<std::pair<DeviceContextHandleType, WindowHandleType>>
{
  typedef std::pair<DeviceContextHandleType, WindowHandleType> ContextPair;
  typedef ContextPair* PointerType;

  void operator()(PointerType ctx)
  {
    if (ctx->first != nullptr)
    {
      ::ReleaseDC(
        ctx->second, // DeviceContextHandleType
        ctx->first // WindowHandleType
        );
    }

    delete ctx;
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs
#endif