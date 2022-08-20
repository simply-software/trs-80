#pragma once

#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file format_as_binary.h
//
// \brief Formats the incoming argument as a binary value that can be
//        printed.
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{
    //! \brief What should be added to the front of the value to
    //         denote binary?
    enum class BinaryPrefix : uint8_t
    {
        PREFIX_NONE, //!< Add nothing to the front
        PREFIX_0b,   //!< Add "0b"
        PREFIX_b     //!< Add "b"
    };


    //! \brief Default formatting for binary values
    struct DefaultBinaryFormatTraits
    {
        //! \brief Character(s) to put before the binary value
        static constexpr BinaryPrefix  Prefix = BinaryPrefix::PREFIX_NONE;
    };


    //! \brief Format an 8-bit unsigned value to 8-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(uint8_t value);

    //! \brief Format an 8-bit signed value to 8-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(int8_t value);

    //! \brief Format a 16-bit unsigned value to 16-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(uint16_t value);

    //! \brief Format a 16-bit signed value to 16-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(int16_t value);

    //! \brief Format a 32-bit unsigned value to 32-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(uint32_t value);

    //! \brief Format a 32-bit signed value to 32-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(int32_t value);

    //! \brief Format a 64-bit unsigned value to 64-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(uint64_t value);

    //! \brief Format a 64-bit signed value to 64-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(int64_t value);

} // namespace format

#include "format_as_binary.inl"
