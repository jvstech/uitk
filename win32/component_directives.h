
#if !defined (JVS_UITK_WIN32_COMPONENT_DIRECTIVES_H_)
#define JVS_UITK_WIN32_COMPONENT_DIRECTIVES_H_

#include <memory>
#include "component.h"
#include "label.h"
#include "directive.h"
#include <jvs/uitk/dock_position.h>
#include "component_alignment_directives.h"

namespace jvs
{
namespace uitk
{
namespace win32
{

template <typename ComponentT>
struct NewComponentCreator
{
	template <typename DirectiveT>
	void operator()(DirectiveT& directive, const Component* anchorComponent, 
		const String& text, DockPosition posRelativeToAnchor, Point location, 
		int padding)
	{
		// nothing to do; 
	}
}; // struct NewComponentCreator

// cleans up Label components (sets AutoSize to true is all... for now...)
template <>
struct NewComponentCreator<Label>
{
	template <typename DirectiveT>
	void operator()(DirectiveT& directive, const Component* anchorComponent, 
		const String& text, DockPosition posRelativeToAnchor, Point location, 
		int padding)
	{
		static_cast<Label*>(directive.NewComponent.get())->set_AutoSize(true);
	}
}; // struct NewComponentCreator<Label>


// Used to create new components on-the-fly without having to first declare
// them.
template <typename ComponentT>
struct AddNewComponent : Directive<ComponentT&>
{
	typedef ComponentT ComponentType;

	Component::OwnedComponent NewComponent;

	AddNewComponent(
		// the component to use as a positional reference
		const Component& anchorComponent,
		// text
		const String& text = "",
		// where to position the new component relative to the anchor component
		DockPosition posRelativeToAnchor = DockPosition::None,
		// left
		int x = 0, 
		// top
		int y = 0,
		// padding offset (relative to dock position and anchor component)
		int padding = 0)
		: NewComponent(new ComponentType())
	{
		this->CreateNewComponent(&anchorComponent, text, posRelativeToAnchor,
			Point(x, y), padding);
	}

	AddNewComponent(
		// text
		const String& text = "",
		// where to position the new component relative to the anchor component
		DockPosition posRelativeToAnchor = DockPosition::None,
		// left
		int x = 0, 
		// top
		int y = 0,
		// padding offset (relative to dock position and anchor component)
		int padding = 0)
		: NewComponent(new ComponentType())
	{
		this->CreateNewComponent(nullptr, text, posRelativeToAnchor,
			Point(x, y), padding);
	}

	void CreateNewComponent(
		const Component* anchorComponent,
		const String& text,
		DockPosition posRelativeToAnchor,
		Point location,
		int padding)
	{
		auto& c = *this->NewComponent;
		c.set_Text(text);
		if (posRelativeToAnchor == DockPosition::None 
			|| posRelativeToAnchor == DockPosition::All)
		{
			c.set_Location(location);
		}
		else
		{
			// TODO: set component layout anchor to the same as the "anchor" control
			switch (posRelativeToAnchor)
			{
			case DockPosition::Left:
				c.set_Top(anchorComponent->get_Top() + location.y);
				c.set_Left(anchorComponent->get_Left() - c.get_Left() + location.x - 
					padding);
				// TODO: anchor modification
				break;

			case DockPosition::Right:
				c.set_Top(anchorComponent->get_Top() + location.y);
				c.set_Left(anchorComponent->get_Right() - location.x + padding);
				// TODO: anchor modification
				break;

			case DockPosition::Top:
				c.set_Top(anchorComponent->get_Top() - c.get_Height() + location.y -
					padding);
				c.set_Left(anchorComponent->get_Left() + location.x);
				// TODO: anchor modification
				break;

			case DockPosition::Bottom:
				c.set_Top(anchorComponent->get_Bottom() + location.y + padding);
				c.set_Left(anchorComponent->get_Left() + location.x);
				// TODO: anchor modification
				break;
			}
		} // if

		// functor for specialized modification depending on the component type
		NewComponentCreator<ComponentType> create;
		create(*this, anchorComponent, text, posRelativeToAnchor, location,
			padding);
	}

	ResultType operator()(Component& host)
	{
		auto& ret = static_cast<ResultType>(host.AddAndReturn(this->NewComponent));
		ret.set_Visible(true);
		return ret;
	}
}; // struct AddNewComponent

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif