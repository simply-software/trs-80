#include "processor.h"
#include <iostream>

namespace assembly
{

    std::ostream& operator<<(std::ostream& os, Processor p)
    {
        static_assert(
            static_cast<uint8_t>(Processor::NUM_VALUES) == 1,
            "Update this function please!"
        );

        switch (p)
        {
            case Processor::MC68B09E: return os << "MC68B09E";
            default: return os << "Invalid (" << static_cast<int>(p) << ')';
        }
    }

} // namespace assembly
