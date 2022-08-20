#include "common/algorithms/for_each.h"
#include "processor_list.h"

///////////////////////////////////////////////////////////////////////////////
//
// \file processor_list.inl
//
// \brief Inline functions for ProcessorList
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	template <typename... ProcessorT> inline
    ProcessorList::ProcessorList(ProcessorT... processors)
    {
        auto lambda =
            [this](Processor p)
            {
                _processors.set(static_cast<int>(p));
            }
        ;

		algorithms::for_each(lambda, processors...);
    }

	template <typename... ProcessorT> inline
    bool ProcessorList::all(ProcessorT... processors) const
    {
        bool result = true;
        auto lambda =
            [this, &result](Processor p)
            {
                result &= has(p);
            }
        ;

		algorithms::for_each(lambda, processors...);
        return result;
    }

	template <typename... ProcessorT> inline
    bool ProcessorList::any(ProcessorT... processors) const
    {
        bool result = false;
        auto lambda =
            [this, &result](Processor p)
            {
                result |= has(p);
            }
        ;

		algorithms::for_each(lambda, processors...);
        return result;
    }

    inline bool ProcessorList::has(Processor processor) const
    {
        return _processors.test(static_cast<int>(processor));
    }

} // namespace assembly

