
#if !defined (JVS_UITK_DOCK_POSITION_H_)
#define JVS_UITK_DOCK_POSITION_H_

namespace jvs
{
namespace uitk
{

enum class DockPosition : int
{
	None = 0,
	Top = 1,
	Bottom = 2,
	Left = 3,
	Right = 4,
	All = 5
}; /* enum class DockPosition */

} // namespace uitk
} // namespace jvs

#endif