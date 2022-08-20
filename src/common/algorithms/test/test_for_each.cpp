#ifdef NDEBUG
    #undef NDEBUG
#endif

#include "../for_each.h"
#include <cassert>
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file test_for_each.cpp
//
// \brief Tests for the algorithms::for_each algorithm
//
//////////////////////////////////////////////////////////////////////////////

namespace
{

    std::string char_or_to_string(int x)
    {
        return std::to_string(x);
    }

    std::string char_or_to_string(char c)
    {
        return std::string(1, c);
    }

}


int main(int argc, char* argv[])
{
    // TEST 1: test for homogeneous parameters
    {
        std::string result;
        algorithms::for_each(
            [&result](int x)
            {
                result += std::to_string(x);
            },
            1, 2, 3, 4, 5
        );

        // Note: the order of invocation of the functor is undefined by
        // the C++ standard, however GCC is deterministic in this regard
        // and this version appears to invoke the function on the
        // arguments left-to-right.
        assert(result == "12345");
    }

    // TEST 2: test for non-homogenous parameters
    {
        std::string result;
        algorithms::for_each(
            [&result](auto x)
            {
                result += char_or_to_string(x);
            },
            1, 2, 'c', 3, 'Z'
        );

        assert(result == "12c3Z");
    }

    return 0; // Success
}
