#include "justification.h"

//////////////////////////////////////////////////////////////////////////////
//
// \file justification.cpp
//
// \brief Formats the incoming text string according to justification and
//        field width
//
//////////////////////////////////////////////////////////////////////////////

namespace format::detail
{


	//! \brief Function that actually does the justification.
	std::string do_justify(
		std::string   value,
		Justification justification,
		size_t		  field_width,
		char		  fill_char
	)
	{
         if (value.length() < field_width)
         {
             switch (justification)
             {
                 case Justification::LEFT:
                     value = value +
						std::string(field_width - value.length(), fill_char);
                     break;

                 case Justification::RIGHT:
                     value =
						std::string(field_width - value.length(), fill_char) +
						value;
                     break;

                 case Justification::CENTER:
                     value =
                         std::string((field_width - value.length()) / 2, fill_char) +
                         value +
                         std::string((field_width - value.length()) / 2, fill_char);
                     if (field_width % 2)
                     {
                         value += fill_char;
                     }
                     break;
             }
         }

		return value;
	}

} // namespace format::detail
