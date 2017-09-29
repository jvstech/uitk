#if !defined (JVS_UITK_WIN32_SIZE_H_)
#define JVS_UITK_WIN32_SIZE_H_

#if defined (_MSC_VER)
#pragma once
#endif

#include "point.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

// No need to re-define something that already exists; just create a typedef
typedef Point Size;

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif