
#if !defined (JVS_UITK_BOUNDS_CHANGED_H_)
#define JVS_UITK_BOUNDS_CHANGED_H_

#include <cstdint>

namespace jvs 
{
namespace uitk
{
/// <summary> Internal enum used to help with component boundary and area 
///           changes. </summary>
/// <remarks> Jsmith, 12/24/2013. </remarks>
enum class BoundsChanged : int
{
	None = 0,
	X = 1,
	Y = 2,
	Location = 3,
	Width = 4,
	Height = 8,
	Size = 12,
	All = 15
};

/*C++11: constexpr*/ BoundsChanged operator|(BoundsChanged a, BoundsChanged b)
{
	return static_cast<BoundsChanged>(static_cast<int>(a) | static_cast<int>(b));
}

/*C++11: constexpr*/ BoundsChanged operator&(BoundsChanged a, BoundsChanged b)
{
	return static_cast<BoundsChanged>(static_cast<int>(a) & static_cast<int>(b));
}

BoundsChanged operator|=(BoundsChanged& a, BoundsChanged b)
{
	a = a | b;
	return a;
}

BoundsChanged operator&=(BoundsChanged& a, BoundsChanged b)
{
	a = a & b;
	return a;
}

} // namespace uitk
} // namespace jvs

#endif