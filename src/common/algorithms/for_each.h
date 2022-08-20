#pragma once

//////////////////////////////////////////////////////////////////////////////
//
// \file for_each.h
//
// \brief "for_each" algorithm, similar to std::for_each
//
//        Whereas std::for_each is given two iterators, this algorithm
//        is given a parameter pack of homogeneous type.  And whereas
//        std::for_each takes the iterators first and the function last,
//        this algorithm takes the function first and the list of values
//        last.  Sorry, C++.
//
// \warning The order in which the functor is applied to the arguments
//          is *NOT DEFINED*!
//
// \code{.cpp}
//          algorithms::for_each(
//              1, 2, 3, 4, 5
//              [](int x){ std::cout << x; },
//              1, 2, 3, 4, 5,
//          );
// \endcode
//
// \example test/test_for_each.cpp
//
//////////////////////////////////////////////////////////////////////////////

namespace algorithms
{

    //! \brief Invokes fn(x) once for each x in [values].
    //
    //         The order in which fn() is called on each value is
    //         not defined.
    template <typename... ValueTypes, typename UnaryFn>
    void for_each(UnaryFn&& fn, ValueTypes... values);

} // namespace algorithms

#include "for_each.inl"
