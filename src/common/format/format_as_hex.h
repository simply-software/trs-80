#pragma once

#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file format_as_hex.h
//
// \brief Formats the incoming argument as a hexadecimal value that can be
//        printed.
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{
    //! \brief What should be added to the front of the value to
    //         denote hexadecimal?
    enum class HexPrefix : uint8_t
    {
        PREFIX_NONE, //!< Add nothing to the front
        PREFIX_0X,   //!< Add "0X"
        PREFIX_0x,   //!< Add "0x"
        PREFIX_X,    //!< Add "X"
        PREFIX_x     //!< Add "x"
    };

    //! \brief Default formatting for hexadecimal values
    struct DefaultHexFormatTraits
    {
        //! \brief Character(s) to put before the hex value
        static constexpr HexPrefix Prefix = HexPrefix::PREFIX_NONE;

        //! \brief Pad with leading zeroes to this width, if not zero
        static constexpr size_t    NumberOfDigits = 0;
    };


    //! \brief Format an 8-bit unsigned value
    template <typename FmtSpec = DefaultHexFormatTraits>
    std::string format_as_hex(uint8_t value);

    //! \brief Format a 16-bit unsigned value
    template <typename FmtSpec = DefaultHexFormatTraits>
    std::string format_as_hex(uint16_t value);

    //! \brief Format a 32-bit unsigned value
    template <typename FmtSpec = DefaultHexFormatTraits>
    std::string format_as_hex(uint32_t value);

    //! \brief Format a 64-bit unsigned value
    template <typename FmtSpec = DefaultHexFormatTraits>
    std::string format_as_hex(uint64_t value);

} // namespace format

#include "format_as_hex.inl"
