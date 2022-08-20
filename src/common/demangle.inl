#include <cxxabi.h>
#include <typeinfo>

//////////////////////////////////////////////////////////////////////////////
//
// \file demangle.inl
//
// \brief Inline functions for the name demangler
//
//////////////////////////////////////////////////////////////////////////////

namespace common
{

    namespace detail
    {

        //! \brief Does the actual work of demangling a typeid(T).name()
        //
        //         On success, returns the demangled name.  On failure,
        //         returns type_id_name unmodified.
        std::string do_demangle(const std::string& type_id_name);

    }


    //! \brief Return a string representing the demangled name of a type
    //
    //         If the type could not be demangled for some reason, returns
    //         typeid(T).name() instead.
    template <typename T> inline std::string demangle()
    {
        return detail::do_demangle(typeid(T).name());
    }

} // namespace common
