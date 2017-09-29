
#if !defined (JVS_UITK_COMPONENT_STATES_H_)
#define JVS_UITK_COMPONENT_STATES_H_

#include <cstdint>

namespace jvs
{
namespace uitk
{

/// <summary> Internal enum for helping with component state manipulation. 
///           </summary>
/// <remarks> Jsmith, 12/24/2013. </remarks>
enum class ComponentStates : uint32_t
{
  MouseEnterPending = 0x1,
  TrackingMouse = 0x2,
  MouseUpPending = 0x4,
  Visible = 0x8,
  Enabled = 0x10
};

}
}

#endif