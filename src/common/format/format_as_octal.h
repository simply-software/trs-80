#pragma once

#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file format_as_octal.h
//
// \brief Formats the incoming argument as an octal value that can be
//        printed.
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{
	//! \brief What should be added to the front of the value to
	//         denote octal?
	enum class OctalPrefix : uint8_t
	{
		PREFIX_NONE,   //!< Add nothing to the front
		LEADING_ZERO   //!< Add a "0" (zero) to the front
	};

	//! \brief Default formatting for octal values
    struct DefaultOctalFormatTraits
    {
		//! \brief Character(s) to put before the octal value
		static constexpr OctalPrefix Prefix = OctalPrefix::PREFIX_NONE;

        //! \brief Pad with leading zeroes to this width, if not zero
		//
		//         Note that it doesn't make sense to specify both
		//         LEADING_ZERO and NumberOfDigits > 0, since the
		//         user won't be able to tell if "0037" is decimal
		//         37 with two leading zeroes or octal 37 with one
		//         leading zero.
        static constexpr size_t      NumberOfDigits = 0;
    };


    //! \brief Format an 8-bit unsigned value
    template <typename FmtSpec = DefaultOctalFormatTraits>
    std::string format_as_octal(uint8_t value);

    //! \brief Format a 16-bit unsigned value
    template <typename FmtSpec = DefaultOctalFormatTraits>
    std::string format_as_octal(uint16_t value);

    //! \brief Format a 32-bit unsigned value
    template <typename FmtSpec = DefaultOctalFormatTraits>
    std::string format_as_octal(uint32_t value);

    //! \brief Format a 64-bit unsigned value
    template <typename FmtSpec = DefaultOctalFormatTraits>
    std::string format_as_octal(uint64_t value);

} // namespace format

#include "format_as_octal.inl"
