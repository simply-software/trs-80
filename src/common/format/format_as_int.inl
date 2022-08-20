#include <sstream>

namespace format
{

    namespace detail
    {

        //! \brief Applies the format spec to the int already converted
        //         to string (in value)
        std::string _format_int(
            std::string   value,
            char          optional_prepend_char
        );


        //! \brief Helper to avoid a lot of code duplication below.
        //
        //         Performs the actual to-int conversion, then
        //         gives the result to the function that actually
        //         handles the format specification.
        template <typename FmtSpec, typename T> inline
        std::string format_int_helper(T value)
        {
            std::stringstream ss;
            ss << value;

            return _format_int(
                ss.str(),
                FmtSpec::PrependChar
            );
        }

    }


    //! \brief Format an 8-bit unsigned value
    template <typename FmtSpec = DefaultIntFormatTraits> inline
    std::string format_as_int(uint8_t value)
    {
        return detail::format_int_helper<FmtSpec>(value);
    }

    //! \brief Format an 8-bit signed value
    template <typename FmtSpec = DefaultIntFormatTraits> inline
    std::string format_as_int(int8_t value)
    {
        return detail::format_int_helper<FmtSpec>(value);
    }

    //! \brief Format a 16-bit unsigned value
    template <typename FmtSpec = DefaultIntFormatTraits> inline
    std::string format_as_int(uint16_t value)
    {
        return detail::format_int_helper<FmtSpec>(value);
    }

    //! \brief Format a 16-bit signed value
    template <typename FmtSpec = DefaultIntFormatTraits> inline
    std::string format_as_int(int16_t value)
    {
        return detail::format_int_helper<FmtSpec>(value);
    }

    //! \brief Format a 32-bit unsigned value
    template <typename FmtSpec = DefaultIntFormatTraits> inline
    std::string format_as_int(uint32_t value)
    {
        return detail::format_int_helper<FmtSpec>(value);
    }

    //! \brief Format a 32-bit signed value
    template <typename FmtSpec = DefaultIntFormatTraits> inline
    std::string format_as_int(int32_t value)
    {
        return detail::format_int_helper<FmtSpec>(value);
    }

    //! \brief Format a 64-bit unsigned value
    template <typename FmtSpec = DefaultIntFormatTraits> inline
    std::string format_as_int(uint64_t value)
    {
        return detail::format_int_helper<FmtSpec>(value);
    }

    //! \brief Format a 64-bit signed value
    template <typename FmtSpec = DefaultIntFormatTraits> inline
    std::string format_as_int(int64_t value)
    {
        return detail::format_int_helper<FmtSpec>(value);
    }

} // namespace format
