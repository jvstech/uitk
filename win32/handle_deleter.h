#if !defined (JVS_UITK_WIN32_HANDLE_DELETER_H_)
#define JVS_UITK_WIN32_HANDLE_DELETER_H_

#if defined (_MSC_VER)
#pragma once
#endif

#include <Windows.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

struct HandleDisposer
{
  template <typename HandleT>
  void operator()(HandleT handle)
  {
    HandleDisposer::Dispose(handle);
  }

  template <typename HandleT>
  static void Dispose(HandleT handle)
  {
    ::CloseHandle(handle);
  }
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif