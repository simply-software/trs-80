#pragma once

#include <cstdint>
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file justification.h
//
// \brief Formats the incoming text string according to justification and
//        field width
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{

    //! \brief Text justification within a printable field
    enum class Justification : uint8_t
    {
        LEFT,   //!< Text is left-justified
        CENTER, //!< Text is centered
        RIGHT   //!< Text is right-justified
    };


	//! \brief Example traits struct for using justify_text()
	//
	//         Consider inherting your Traits struct from this base
	//         one and overriding only the values you need to.
	struct DefaultJustificationTraits
	{
		//! Width of field in which to justify the text
		static constexpr size_t        FieldWidth = 0;

		//! Type of justification; ignored if FieldWidth == 0
		static constexpr Justification Justify = Justification::LEFT;

		//! Fill character to use when expanding the input string
		static constexpr char          FillChar = ' ';
	};


	template <typename JustificationTraits = DefaultJustificationTraits>
	std::string justify(const std::string& text_to_justify);

} // namespace format

#include "justification.inl"
