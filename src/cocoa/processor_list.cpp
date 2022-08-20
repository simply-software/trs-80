#include "common/algorithms/enum_cast.h"
#include "processor_list.h"
#include <iostream>

namespace assembly
{

    std::ostream& operator<<(std::ostream& os, const ProcessorList& p)
    {
        const char* pipe = "";
        for (size_t i = 0; i < static_cast<size_t>(Processor::NUM_VALUES); ++i)
        {
            if (p.has(algorithms::enum_cast<Processor>(i)))
            {
                os << pipe << algorithms::enum_cast<Processor>(i);
                pipe = "|";
            }
        }

		return os;
    }

} // namespace assembly

