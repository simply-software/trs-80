#pragma once

#include <cstdint>
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file character_case.h
//
// \brief Enum for upper/lower case
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{

	//! \brief Uppercase or lowercase?
	enum class CharCase : uint8_t
	{
		LOWER, //!< A-Z -> a-z
		UPPER  //!< a-z -> A-Z
	};

	//! \brief Default character case
    struct DefaultCharCaseTraits
    {
		//! \brief Use A-F or a-f?
		static constexpr CharCase Case = CharCase::LOWER;
    };

	//! \brief Convert the case of all characters in a string
    template <typename FmtSpec = DefaultCharCaseTraits>
    std::string char_case(const std::string& text);

} // namespace format

#include "character_case.inl"
