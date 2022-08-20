#include "format_as_octal.h"

//////////////////////////////////////////////////////////////////////////////
//
// \file format_as_octal.cpp
//
// \brief Adds leading zeroes and optional octal prefix to the string
//
//////////////////////////////////////////////////////////////////////////////

namespace format::detail
{

    std::string _format_octal(
        std::string   value,
        OctalPrefix   prefix,
        size_t        number_of_digits
    )
    {
        if (value.length() < number_of_digits)
        {
            value = std::string(number_of_digits - value.length(), '0') +
                value;
        }

        switch (prefix)
        {
            case OctalPrefix::LEADING_ZERO:
                value = '0' + value;
                break;

            case OctalPrefix::PREFIX_NONE:
                break;
        }

        return value;
    }

} // namespace format::detail
