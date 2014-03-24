
#if !defined (JVS_EVENT_H_)
#define JVS_EVENT_H_

#include <vector>
#include <tuple>
#include <initializer_list>
#include <mutex>
#include <algorithm>
#include "variadic_function_object.h"

namespace jvs
{

template <typename ...ArgsT>
class Event
{
public:

	// typedefs
	typedef Event<ArgsT...> Type;
	typedef std::tuple<ArgsT...> ArgumentTypes;
	typedef VariadicFunctionObject<void, ArgsT...> ValueType;
	typedef typename ValueType::FunctionType FunctionType;

private:

	// member fields
	std::vector<ValueType> funcs_;
	std::mutex lock_;

public:

	Event(void)
		: funcs_(),
		lock_()
	{
	}

	Event(const ValueType& eventFunction)
		: funcs_({eventFunction}),
		lock_()
	{
	}

	Event(const Event& src)
		: funcs_(src.funcs_),
		lock_()
	{
	}

	Event(Event&& src)
		: funcs_(std::move(src.funcs_)),
		lock_()
	{
	}

	virtual ~Event(void)
	{
	}

	Event& operator=(const Event& src)
	{
		this->funcs_ = src.funcs_;
		return *this;
	}

	Event& operator=(Event&& src)
	{
		this->funcs_ = std::move(src.funcs_);
		return *this;
	}

	Event& operator<<(const FunctionType& eventFunction)
	{
		this->funcs_.push_back(eventFunction);
		return *this;
	}

	Event& Add(const FunctionType& eventFunction)
	{
		this->funcs_.push_back(eventFunction);
		return *this;
	}

	Event& Remove(const FunctionType& eventFunction)
	{
		this->lock_.lock();
		for (auto it = this->funcs_.begin(); it != this->funcs_.end(), ++it)
		{
			if (eventFunction.Function.target<void(ArgsT...)>() == 
				it->Function.target<void(ArgsT...)>())
			{
				this->funcs_.erase(it);
				break;
			} // if
		} // for

		this->lock_.unlock();
	}

	Event& operator+=(const FunctionType& eventFunction)
	{
		return this->Add(eventFunction);
	}

	Event& operator-=(const FunctionType& eventFunction)
	{
		return this->Remove(eventFunction);
	}

	void Raise(ArgsT... args)
	{
		this->lock_.lock();
		for (ValueType& f : this->funcs_)
		{
			f(args...);
		}

		this->lock_.unlock();
	}

	void operator()(ArgsT... args)
	{
		this->Raise(args...);
	}

	bool operator==(const Event& b)
	{
		return (
			(this->funcs_.size() == b.funcs_.size())
			&& (std::mismatch(this->funcs_.begin(), this->funcs_.end(), 
				b.funcs_.begin()).first == this->funcs_.end())
			);
	}
};
} // namespace jvs

#endif  /* #if !defined (JVS_EVENT_H_) */