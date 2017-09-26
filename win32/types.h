#if !defined (JVS_UITK_WIN32_TYPES_H_)
#define JVS_UITK_WIN32_TYPES_H_

#include <cstddef>
#include <cstdint>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#if defined (_WIN64)
#include "types64.h"
#else
#include "types32.h"
#endif

namespace jvs
{
namespace uitk
{
namespace win32
{

// Win32 API value types mapped to UITK-friendly names

// The ubiquitous handle type
using Handle = void*;

// Window-related types
using Atom = std::uint16_t;

// Graphics types
using DeviceContextHandle = HDC;

// Brush types
using BrushHandle = HBRUSH;
using LogicalBrush = LOGBRUSH;

// Font types
using FontHandle = HFONT;
using LogicalFont = LOGFONTW;

// Cursor handle
using CursorHandle = HCURSOR;

// Icon handle
using IconHandle = HICON;

// Generic API types
using WindowHandle = HWND;
using WParam = std::uintptr_t;
using MessageType = MSG;
using UInt = unsigned int;
using DWord = std::uint32_t;


} // namespace win32
} // namespace uitk
} // namespace jvs

#endif