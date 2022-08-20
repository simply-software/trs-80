#include "addressing_mode.h"
#include <iostream>

namespace assembly
{

    std::ostream& operator<<(std::ostream& os, AddressingMode a)
    {
        static_assert(
            static_cast<int>(AddressingMode::NUM_VALUES) == 8,
            "Please update this function!"
        );

        switch (a)
        {
            case AddressingMode::INHERENT:
                return os << "INHERENT";

            case AddressingMode::IMMEDIATE:
                return os << "IMMEDIATE";

            case AddressingMode::EXTENDED:
                return os << "EXTENDED";

            case AddressingMode::EXTENDED_INDIRECT:
                return os << "EXTENDED_INDIRECT";

            case AddressingMode::INDEXED:
                return os << "INDEXED";

            case AddressingMode::INDEXED_INDIRECT:
                return os << "INDEXED_INDIRECT";

            case AddressingMode::RELATIVE:
                return os << "RELATIVE";

            case AddressingMode::DIRECT:
                return os << "DIRECT";

            default:
                return os << "Invalid (" << static_cast<int>(a) << ')';
        }
    }

} // namespace assembly
