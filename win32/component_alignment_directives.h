
#if !defined (JVS_UITK_WIN32_COMPONENT_ALIGNMENT_DIRECTIVES_H_)
#define JVS_UITK_WIN32_COMPONENT_ALIGNMENT_DIRECTIVES_H_

#include "component.h"
#include "directive.h"
#include <jvs/uitk/position_alignment.h>

namespace jvs
{
namespace uitk
{
namespace win32
{

struct AlignWith : Directive<Component&>
{
	Component& OppositeComponent;
	PositionAlignment Alignment;

	AlignWith(
		// the component with which to align
		Component& oppositeComponent,
		// what type of alignment
		PositionAlignment alignment
		)
		: OppositeComponent(oppositeComponent),
		Alignment(alignment)
	{
	}

	ResultType operator()(Component& component)
	{
		switch (this->Alignment)
		{
		case PositionAlignment::Bottom:
			component.set_top(this->OppositeComponent.bottom() - 
				component.height());
			break;
		case PositionAlignment::HorizontalCenter:
			component.set_left((this->OppositeComponent.left() + 
				(this->OppositeComponent.width() / 2)) - (component.width() / 
				2));
			break;

		case PositionAlignment::Left:
			component.set_left(this->OppositeComponent.left());
			break;

		case PositionAlignment::Right:
			component.set_left(this->OppositeComponent.right() - 
				component.width());
			break;

		case PositionAlignment::Top:
			component.set_top(this->OppositeComponent.top());
			break;

		case PositionAlignment::VerticalCenter:
			component.set_top((this->OppositeComponent.top() +
				(this->OppositeComponent.height() / 2)) - (component.height() / 
				2));
			break;
		}

		return component;
	}
}; // struct AlignWith

struct CenterHorizontally : Directive<Component&>
{
	bool RemoveAnchoring;

	CenterHorizontally(void)
		: RemoveAnchoring(true)
	{
	}

	CenterHorizontally(bool removeAnchoring)
		: RemoveAnchoring(RemoveAnchoring)
	{
	}

	ResultType operator()(Component& component)
	{
		if (component.parent() != nullptr)
		{
			auto size = component.parent()->client_size();
			component.set_left((size.x / 2) - (component.width() / 2));
			if (this->RemoveAnchoring)
			{
				AnchorStyles newAnchor = component.anchor();
				newAnchor &= ~AnchorStyles::Left;
				newAnchor &= ~AnchorStyles::Right;
				component.set_anchor(newAnchor);
			}
		}

		return component;
	}

}; // struct CenterHorizontally

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif