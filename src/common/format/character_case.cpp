#include "character_case.h"
#include <algorithm>
#include <cctype>


//////////////////////////////////////////////////////////////////////////////
//
// \file character_case.cpp
//
// \brief Enum for upper/lower case
//
//////////////////////////////////////////////////////////////////////////////

namespace format::detail
{

	std::string _format_chars(
		std::string text,
		CharCase    char_case
	)
	{
		std::transform(
			text.begin(),
			text.end(),
			text.begin(),
			char_case == CharCase::UPPER ? ::toupper : ::tolower
		);

		return text;
	}

} // namespace format::detail
