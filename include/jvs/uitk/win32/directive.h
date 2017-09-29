
#if !defined (JVS_UITK_WIN32_DIRECTIVE_H_)
#define JVS_UITK_WIN32_DIRECTIVE_H_

namespace jvs
{
namespace uitk
{
namespace win32
{

class Component;

// This class provides a means of extending or manipulating a component
// without the need for using properties.
template <typename ResultT>
struct Directive
{
	typedef ResultT ResultType;
	
	virtual ~Directive()
	{
	}

	virtual ResultT operator()(Component&) = 0;
};

template <typename ResultT>
typename Directive<ResultT>::ResultType 
	operator<<(Component& component, Directive<ResultT>& directive)
{
	return directive(component);
}

} // namespace win32
} // namespace uitk
} // namespace jvs

#endif