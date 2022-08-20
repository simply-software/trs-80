#include <bitset>
#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//
// \file format_as_binary.inl
//
// \brief Formats the incoming argument as a binary value that can be
//        printed.
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{

    namespace detail
    {

        //! \brief Applies the format spec to the int already converted
        //         to binary string (in value)
        std::string _format_binary(
            std::string   value,
            BinaryPrefix  prefix
        );


        //! \brief Helper to avoid a lot of code duplication below.
        template <typename FmtSpec, typename T> inline
        std::string format_binary_helper(T value)
        {
            std::stringstream ss;
            ss << std::bitset<sizeof(T) * 8>(value);

            return _format_binary(
                ss.str(),
                FmtSpec::Prefix
            );
        }

    }


    //! \brief Format an 8-bit unsigned value to 8-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(uint8_t value)
    {
        return detail::format_binary_helper<FmtSpec>(value);
    }

    //! \brief Format an 8-bit signed value to 8-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(int8_t value)
    {
        return detail::format_binary_helper<FmtSpec>(value);
    }

    //! \brief Format a 16-bit unsigned value to 16-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(uint16_t value)
    {
        return detail::format_binary_helper<FmtSpec>(value);
    }

    //! \brief Format a 16-bit signed value to 16-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(int16_t value)
    {
        return detail::format_binary_helper<FmtSpec>(value);
    }

    //! \brief Format a 32-bit unsigned value to 32-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(uint32_t value)
    {
        return detail::format_binary_helper<FmtSpec>(value);
    }

    //! \brief Format a 32-bit signed value to 32-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(int32_t value)
    {
        return detail::format_binary_helper<FmtSpec>(value);
    }

    //! \brief Format a 64-bit unsigned value to 64-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(uint64_t value)
    {
        return detail::format_binary_helper<FmtSpec>(value);
    }

    //! \brief Format a 64-bit signed value to 64-char string
    template <typename FmtSpec = DefaultBinaryFormatTraits>
    std::string format_as_binary(int64_t value)
    {
        return detail::format_binary_helper<FmtSpec>(value);
    }

} // namespace format
