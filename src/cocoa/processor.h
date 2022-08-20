#pragma once

#include <cstdint>
#include <iosfwd>
#include "common/algorithms/enum_cast.h"

///////////////////////////////////////////////////////////////////////////////
//
// \file processor.h
//
// \brief An enumeration of the different CPUs supported by the toolchain
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

    //! \brief Enumerates the different CPUs supported by the toolchain
    enum class Processor : uint8_t
    {
        MC68B09E = 0,  // TRS-80 Color Computer 2 and 3
        NUM_VALUES
    };


    //! \brief Output as the symbol name, eg "MC68B09E"
    std::ostream& operator<<(std::ostream& os, Processor p);

} // namespace assembly


namespace algorithms
{

    //! \brief Convert integer to Processor (throws EnumCastException)
    template <> ::assembly::Processor enum_cast(size_t i);

} // namespace algorithms

#include "processor.inl"
