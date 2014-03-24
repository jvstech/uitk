
#if !defined (JVS_UITK_WIN32_FRAME_STATES_H_)
#define JVS_UITK_WIN32_FRAME_STATES_H_

#include <cstdint>

namespace jvs
{
namespace uitk
{
namespace win32
{

enum class FrameStates : uint32_t
{
	BoundsWidthIsClientSize = 0x1,
	BoundsHeightIsClientSize = 0x2,
	SizeLockedByOs = 0x4
};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif /* #if !defined (JVS_UITK_WIN32_FRAMESTATES_H_) */