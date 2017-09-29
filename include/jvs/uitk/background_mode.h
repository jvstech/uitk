
#if !defined (JVS_UITK_BACKGROUND_MODE_H_)
#define JVS_UITK_BACKGROUND_MODE_H_

namespace jvs
{
namespace uitk
{
/// <summary> Values that represent the way component backgrounds are painted. 
///           </summary>
/// <remarks> Jsmith, 12/24/2013. </remarks>
enum class BackgroundMode
{
  /// <summary> An enum constant representing the transparent option. 
  ///           Components with transparent backgrounds inherit the same 
  ///           background as their parent. </summary>
  Transparent = 1,
  /// <summary> An enum constant representing the opaque option. Components 
  ///           with opaque backgrounds have their own background colors drawn. 
  ///           </summary>
  Opaque = 2
};

} // namespace uitk
} // namespace jvs

#endif