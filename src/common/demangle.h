#pragma once

#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file demangle.h
//
// \brief "demangle" algorithm: returns the demangled name for a given type
//
//////////////////////////////////////////////////////////////////////////////

namespace common
{

    //! \brief Return a string representing the demangled name of a type
    //
    //         If the type could not be demangled for some reason, returns
    //         typeid(T).name() instead.
    template <typename T> std::string demangle();

} // namespace common

#include "demangle.inl"
