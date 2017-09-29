
#if !defined (JVS_UITK_ANCHOR_STYLES_H_)
#define JVS_UITK_ANCHOR_STYLES_H_

namespace jvs
{
namespace uitk
{

enum class AnchorStyles : int
{
	None = 0,
	Left = 1,
	Top = 2,
	Right = 4,
	Bottom = 8,
	All = Left | Top | Right | Bottom
};

/*C++11: constexpr*/ AnchorStyles operator|(AnchorStyles a, AnchorStyles b)
{
	return static_cast<AnchorStyles>(static_cast<int>(a) | static_cast<int>(b));
}

/*C++11: constexpr*/ AnchorStyles operator&(AnchorStyles a, AnchorStyles b)
{
	return static_cast<AnchorStyles>(static_cast<int>(a) & static_cast<int>(b));
}

/*C++11: constexpr*/ AnchorStyles operator~(AnchorStyles a)
{
	return static_cast<AnchorStyles>(~static_cast<int>(a));
}

AnchorStyles operator|=(AnchorStyles& a, AnchorStyles b)
{
	a = a | b;
	return a;
}

AnchorStyles operator&=(AnchorStyles& a, AnchorStyles b)
{
	a = a & b;
	return a;
}

bool IsAnchored(AnchorStyles anchor, AnchorStyles requestedAnchor)
{
	return ((anchor & requestedAnchor) != AnchorStyles::None);
}

} // namespace uitk
} // namespace jvs

#endif