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
	using ComponentType = ComponentT;

	LayoutEngine()
		: suspendLayout_(false)
	{
	}

	virtual ~LayoutEngine()
	{
	}

	void Suspend()
	{
		this->suspendLayout_ = true;
	}

	void Resume()
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