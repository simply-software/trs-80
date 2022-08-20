#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//
// \file format_as_octal.inl
//
// \brief Formats the incoming argument as an octal value that can be
//        printed.
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{

    namespace detail
    {

        //! \brief Applies the format spec to the int already converted
        //         to string (in value)
        std::string _format_octal(
            std::string   value,
            OctalPrefix   prefix,
            size_t        field_width
        );


        //! \brief Helper to avoid a lot of code duplication below.
        //
        //         Performs the actual to-octal conversion, then
        //         gives the result to the function that actually
        //         handles the format specification.
        template <typename FmtSpec, typename T> inline
        std::string format_octal_helper(T value)
        {
            std::stringstream ss;
            ss << std::oct << value;

            return _format_octal(
                ss.str(),
                FmtSpec::Prefix,
                FmtSpec::NumberOfDigits
            );
        }

    }


    //! \brief Format an 8-bit unsigned value
    template <typename FmtSpec = DefaultOctalFormatTraits> inline
    std::string format_as_octal(uint8_t value)
    {
        return detail::format_octal_helper<FmtSpec>(value);
    }

    //! \brief Format a 16-bit unsigned value
    template <typename FmtSpec = DefaultOctalFormatTraits> inline
    std::string format_as_octal(uint16_t value)
    {
        return detail::format_octal_helper<FmtSpec>(value);
    }

    //! \brief Format a 32-bit unsigned value
    template <typename FmtSpec = DefaultOctalFormatTraits> inline
    std::string format_as_octal(uint32_t value)
    {
        return detail::format_octal_helper<FmtSpec>(value);
    }

    //! \brief Format a 64-bit unsigned value
    template <typename FmtSpec = DefaultOctalFormatTraits> inline
    std::string format_as_octal(uint64_t value)
    {
        return detail::format_octal_helper<FmtSpec>(value);
    }

} // namespace format
