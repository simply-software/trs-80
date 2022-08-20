#include "format_as_hex.h"

//////////////////////////////////////////////////////////////////////////////
//
// \file format_as_hex.cpp
//
// \brief Adds leading zeroes and optional hex prefix to the string
//
//////////////////////////////////////////////////////////////////////////////

namespace format::detail
{

    std::string _format_hex(
        std::string   value,
		HexPrefix     prefix,
		size_t	 	  number_of_digits
    )
    {
		if (value.length() < number_of_digits)
		{
			value = std::string(number_of_digits - value.length(), '0') +
				value;
		}

		switch (prefix)
		{
			case HexPrefix::PREFIX_0X:
				value = "0X" + value;
				break;

			case HexPrefix::PREFIX_0x:
				value = "0x" + value;
				break;

			case HexPrefix::PREFIX_X:
				value = 'X' + value;
				break;

			case HexPrefix::PREFIX_x:
				value = 'x' + value;
				break;

			case HexPrefix::PREFIX_NONE:
				break;
		}

        return value;
    }

} // namespace format::detail
