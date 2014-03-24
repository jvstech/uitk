
#if !defined (JVS_NULL_DELETER_H_)
#define JVS_NULL_DELETER_H_

#include <memory>

namespace jvs
{

struct NullDeleter
{
	template <typename T>
	void operator()(T*)
	{
		// do nothing;
	}

	template <typename T>
	void operator()(const T*)
	{
		// do nothing;
	}
};

template <typename T>
std::shared_ptr<T> MakeNullShared(const T& src)
{
	return std::shared_ptr<T>(&src, jvs::NullDeleter());
}

}

#endif