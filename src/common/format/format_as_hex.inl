#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//
// \file format_as_hex.inl
//
// \brief Formats the incoming argument as a hex value that can be
//        printed.
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{

    namespace detail
    {

        //! \brief Applies the format spec to the int already converted
        //         to string (in value)
        std::string _format_hex(
            std::string   value,
            HexPrefix     prefix,
            size_t        field_width
        );


        //! \brief Helper to avoid a lot of code duplication below.
        //
        //         Performs the actual to-hex conversion, then
        //         gives the result to the function that actually
        //         handles the format specification.
        template <typename FmtSpec, typename T> inline
        std::string format_hex_helper(T value)
        {
            std::stringstream ss;
            ss << std::hex << value;

            return _format_hex(
                ss.str(),
                FmtSpec::Prefix,
                FmtSpec::NumberOfDigits
            );
        }

    }


    //! \brief Format an 8-bit unsigned value
    template <typename FmtSpec = DefaultHexFormatTraits> inline
    std::string format_as_hex(uint8_t value)
    {
        return detail::format_hex_helper<FmtSpec>(value);
    }

    //! \brief Format a 16-bit unsigned value
    template <typename FmtSpec = DefaultHexFormatTraits> inline
    std::string format_as_hex(uint16_t value)
    {
        return detail::format_hex_helper<FmtSpec>(value);
    }

    //! \brief Format a 32-bit unsigned value
    template <typename FmtSpec = DefaultHexFormatTraits> inline
    std::string format_as_hex(uint32_t value)
    {
        return detail::format_hex_helper<FmtSpec>(value);
    }

    //! \brief Format a 64-bit unsigned value
    template <typename FmtSpec = DefaultHexFormatTraits> inline
    std::string format_as_hex(uint64_t value)
    {
        return detail::format_hex_helper<FmtSpec>(value);
    }

} // namespace format
