#pragma once

#include "justification.h"
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file format_as_int.h
//
// \brief Formats the incoming argument as an integer that can be printed.
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{

    struct DefaultIntFormatTraits
    {
        //! \brief Character to prepend.  If blank, no prepend
        static constexpr char PrependChar = ' ';
    };


    //! \brief Format an 8-bit unsigned value
    template <typename FmtSpec = DefaultIntFormatTraits>
    std::string format_as_int(uint8_t value);

    //! \brief Format an 8-bit signed value
    template <typename FmtSpec = DefaultIntFormatTraits>
    std::string format_as_int(int8_t value);

    //! \brief Format a 16-bit unsigned value
    template <typename FmtSpec = DefaultIntFormatTraits>
    std::string format_as_int(uint16_t value);

    //! \brief Format a 16-bit signed value
    template <typename FmtSpec = DefaultIntFormatTraits>
    std::string format_as_int(int16_t value);

    //! \brief Format a 32-bit unsigned value
    template <typename FmtSpec = DefaultIntFormatTraits>
    std::string format_as_int(uint32_t value);

    //! \brief Format a 32-bit signed value
    template <typename FmtSpec = DefaultIntFormatTraits>
    std::string format_as_int(int32_t value);

    //! \brief Format a 64-bit unsigned value
    template <typename FmtSpec = DefaultIntFormatTraits>
    std::string format_as_int(uint64_t value);

    //! \brief Format a 64-bit signed value
    template <typename FmtSpec = DefaultIntFormatTraits>
    std::string format_as_int(int64_t value);

} // namespace format

#include "format_as_int.inl"
