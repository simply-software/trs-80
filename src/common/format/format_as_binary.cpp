#include "format_as_binary.h"

//////////////////////////////////////////////////////////////////////////////
//
// \file format_as_binary.cpp
//
// \brief Formats the incoming argument as a binary value that can be
//        printed.
//
//////////////////////////////////////////////////////////////////////////////

namespace format::detail
{

    //! \brief Applies the format spec to the int already converted
    //         to binary string (in value)
    std::string _format_binary(
        std::string   value,
        BinaryPrefix  prefix
    )
	{
		switch (prefix)
		{
			case BinaryPrefix::PREFIX_0b:
				value = "0b" + value;
				break;

			case BinaryPrefix::PREFIX_b:
				value = 'b' + value;
				break;

			case BinaryPrefix::PREFIX_NONE:
				break;
		}

		return value;
	}

} // namespace format::detail
