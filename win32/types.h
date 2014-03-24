#if !defined (JVS_UITK_WIN32_TYPES_H_)
#define JVS_UITK_WIN32_TYPES_H_

#if defined (_MSC_VER)
#pragma once
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <jvs/base/counted_value.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

// Win32 API value types mapped to UITK-friendly names

// Graphics typedefs
typedef HDC DeviceContextHandleType;

// Brush typedefs
typedef HBRUSH BrushHandleType;
typedef LOGBRUSH LogicalBrushType;

// Font typedefs
typedef HFONT FontHandleType;
typedef LOGFONT LogicalFontType;

// Generic API typedefs
typedef HWND WindowHandleType;
typedef LRESULT Int32ResultType;
typedef WPARAM Int16ParameterType;
typedef LPARAM Int32ParameterType;
typedef MSG MessageType;
typedef UINT UIntType;
typedef DWORD DWordType;

// Reference counted aliases
struct GdiObjectDisposer;
template <typename GdiObjectT>
using GdiHandle = CountedValue<GdiObjectT, GdiObjectDisposer>;


} // namespace win32
} // namespace uitk
} // namespace jvs

#endif