#pragma once

#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file c_str.h
//
// \brief "c_str" algorithm: converts a value of a given type to const char*
//
//        The resulting string must be null-terminated; the algorithm
//        must guarantee that c_str(V) is ostream-able.
//
//////////////////////////////////////////////////////////////////////////////

namespace algorithms
{

    //! \brief Return a null-terminated string representing the given value
    //
    //         The base template is left unimplemented so as to generate
    //         a compile error if the conversion is not well-defined.
    //
    //         When implementing your own overload, please be VERY
    //         CAREFUL that the lifetime of the const char* is longer
    //         than the c_str() function call itself.  DO NOT use a
    //         static to guarantee this, as this makes the function
    //         thread unsafe.
    template <typename T> const char* c_str(const T& value);

    //! \brief Overload for const char*
    const char* c_str(const char* value);

    //! \brief Overload for std::string
    const char* c_str(const std::string& value);

    // Do NOT implement this one;  string_view::data() does NOT
    // guarantee null-termination!
    // const char* c_str(const std::string_view& value);

} // namespace algorithms

#include "c_str.inl"
