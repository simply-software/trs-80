#include "computer.h"
#include <iostream>

namespace assembly
{

    std::ostream& operator<<(std::ostream& os, Computer c)
    {
        static_assert(
            static_cast<uint8_t>(Computer::NUM_VALUES) == 2,
            "Update this function please!"
        );

        switch (c)
        {
            case Computer::COCO_2: return os << "COCO_2";
            case Computer::COCO_3: return os << "COCO_3";
            default: return os << "Invalid (" << static_cast<int>(c) << ')';
        }
    }

} // namespace assembly
