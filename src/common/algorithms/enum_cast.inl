#include "common/demangle.h"
#include "common/format/format_as_int.h"
#include "c_str.h"

namespace algorithms
{

    template <typename T, typename ValueType> inline
    void throw_enum_cast_exception(
        ValueType   value,
        const char* optional_error_text
    )
    {
        throw EnumCastException(
            c_str(::common::demangle<T>()),
            c_str(::format::format_as_int(value)),
            optional_error_text
        );
    }

} // namespace algorithms
