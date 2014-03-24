
#if !defined (JVS_UITK_WIN32_CURSOR_TYPE_H_)
#define JVS_UITK_WIN32_CURSOR_TYPE_H_

namespace jvs
{
namespace uitk
{
namespace win32
{

enum class CursorType : int
{
  Custom = -1,
  Default = 0,
  Crosshair = 32515,
  Arrow = 32512,
  EastResize = 32644,
  Hand = 32649,
  Help = 32651,
  Move = 32646,
  No = 32648,
  NorthResize = 32645,
  NorthEastResize = 32643,
  NorthWestResize = 32642,
  SouthResize = 32645,
  SouthEastResize = 32642,
  SouthWestResize = 32643,
  Starting = 32650,
  Text = 32513,
  Up = 32516,
  WestResize = 32644,
  Wait = 32514
};

} // namespace win32
} // namespace uitk
} // namespace jvs


#endif