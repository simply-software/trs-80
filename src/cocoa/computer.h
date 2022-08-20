#pragma once

#include <cstdint>
#include <iosfwd>

///////////////////////////////////////////////////////////////////////////////
//
// \file computer.h
//
// \brief An enumeration of the different TRS-80 computers supported
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

    //! \brief Enumerates the different TRS-80 computers supported
    enum class Computer : uint8_t
    {
        COCO_2,     // TRS-80 Color Computer 2
        COCO_3,     // TRS-80 Color Computer 3
        NUM_VALUES
    };

    //! \brief Output as the symbol name, eg "COCO_2"
    std::ostream& operator<<(std::ostream& os, Computer c);

} // namespace assembly
