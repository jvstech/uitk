
#if !defined (JVS_VARIADIC_FUNCTION_OBJECT_H_)
#define JVS_VARIADIC_FUNCTION_OBJECT_H_

#include <functional>
#include <tuple>
#include <utility>

namespace jvs
{

template <typename ReturnT, typename ...ArgsT>
class VariadicFunctionObject
{
public:

	// typedefs
	typedef ReturnT ReturnType;
	typedef VariadicFunctionObject<ReturnT, ArgsT...> Type;
	typedef std::tuple<ArgsT...> ArgumentTypes;
	typedef std::function<ReturnType(ArgsT...)> FunctionType;

private:

	// member fields
	FunctionType function_;

public:
	FunctionType& Function;

	VariadicFunctionObject(const FunctionType& function)
		: function_(function),
		Function(function_)
	{
	}

	VariadicFunctionObject(const VariadicFunctionObject& src)
		: function_(src.function_),
		Function(function_)
	{
	}

	VariadicFunctionObject(VariadicFunctionObject&& src)
		: function_(std::move(src.function_)),
		Function(function_)
	{
	}

	virtual ~VariadicFunctionObject(void)
	{
	}

	VariadicFunctionObject& operator=(const VariadicFunctionObject& src)
	{
		this->function_ = src.function_;
		return *this;
	}

	VariadicFunctionObject& operator=(VariadicFunctionObject&& src)
	{
		this->function_ = std::move(src.function_);
		return *this;
	}
	
	bool operator==(const VariadicFunctionObject& b)
	{
		return (this->function_.target<ReturnType(ArgsT...)>() == 
			b.function_.target<ReturnType(ArgsT...)>());
	}

	ReturnType operator()(ArgsT... args) const
	{
		return this->function_(args...);
	}
}; // class VariadicFunctionObject

} // namespace jvs

#endif