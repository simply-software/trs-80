#include "enum_cast.h"

namespace algorithms
{

    namespace
    {

        std::string make_error_string(
            const char* typename_t,
            const char* value,
            const char* optional_error_text
        )
        {
            if (value == nullptr)
            {
                throw std::runtime_error(
                    "While attempting to construct EnumCastException, "
                    "value was NULL"
                );
            }

            if (typename_t == nullptr)
            {
                throw std::runtime_error(
                    "While attempting to construct EnumCastException, "
                    "typename_t was NULL"
                );
            }

            std::string error_text =
                std::string("Cannot convert ") +
                value +
                " to " +
                typename_t
            ;

            if (optional_error_text)
            {
                error_text =
                    error_text +
                    '\n' +
                    optional_error_text
                ;
            }

            return error_text;
        }

    }

    EnumCastException::EnumCastException(
        const char* typename_t,
        const char* value,
        const char* optional_error_text
    ) : std::range_error(make_error_string(typename_t, value, optional_error_text))
    {
    }

} // namespace algorithms
