#include "format_as_int.h"

namespace format::detail
{

    std::string _format_int(
        std::string   value,
        char          optional_prepend_char
    )
    {
        if (optional_prepend_char != ' ')
        {
            value = optional_prepend_char + value;
        }

        return value;
    }

} // namespace format::detail
