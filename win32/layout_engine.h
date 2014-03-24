
#if !defined (JVS_UITK_WIN32_LAYOUTENGINE_H_)
#define JVS_UITK_WIN32_LAYOUTENGINE_H_

namespace jvs
{
namespace uitk
{
namespace win32
{

template <typename ComponentT>
class LayoutEngine
{
private:
	bool suspendLayout_;

public:
	typedef ComponentT ComponentType;

	LayoutEngine(void)
		: suspendLayout_(false)
	{
	}

	virtual ~LayoutEngine(void)
	{
	}

	void Suspend(void)
	{
		this->suspendLayout_ = true;
	}

	void Resume(void)
	{
		this->suspendLayout_ = false;
	}

	ComponentT& DoLayout(ComponentType& parent, Point originalSize, 
		Point newSize)
	{
		if (!this->suspendLayout_)
		{
			this->LayoutAnchoredChildren(parent, originalSize, newSize);
		}

		return parent;
	}

protected:
	virtual void LayoutAnchoredChildren(ComponentType&, Point, Point) = 0;

};

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif