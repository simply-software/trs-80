#include "demangle.h"
#include <cxxabi.h>
#include <typeinfo>

//////////////////////////////////////////////////////////////////////////////
//
// \file demangle.cpp
//
// \brief Non-inline functions for the name demangler
//
//////////////////////////////////////////////////////////////////////////////

namespace common::detail
{

    std::string do_demangle(const std::string& type_id_name)
    {
        // Arbitrarily chosen
        static constexpr size_t BUF_SIZE = 1024;

        // According to the documentation found at:
        // https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.3/a01696.html
        // the buffer _must_ be malloced, because __cxa_demangle() will realloc()
        // it if it is too small.
        char*  realname = (char*)malloc(BUF_SIZE);
        size_t length = BUF_SIZE;
        int    status = 0;

        // If the buffer gets reallocated, the function will return a pointer
        // that is different from the one we passed in!
        realname = abi::__cxa_demangle(
            type_id_name.c_str(),
            realname,
            &length,
            &status
        );

        std::string demangled_name =
            status == 0 ? realname :
            type_id_name;

        free(realname);
        return demangled_name;
    }

} // namespace common::detail
