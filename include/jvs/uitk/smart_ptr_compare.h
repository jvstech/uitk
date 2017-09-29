
#if !defined (JVS_SMART_PTR_COMPARE_H)
#define JVS_SMART_PTR_COMPARE_H

#include <memory>

namespace jvs
{
	template <typename PtrT>
	struct SmartPtrComparerer
	{
		PtrT* Pointer;

		SmartPtrComparerer(PtrT* pointer)
			: Pointer(pointer)
		{
		}

		template <typename SmartPtrT>
		bool operator()(SmartPtrT& p1)
		{
			return (p1.get() == this->Pointer);
		}
	};

} // namespace jvs

#endif