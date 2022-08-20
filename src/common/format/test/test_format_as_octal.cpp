#ifdef NDEBUG
    #undef NDEBUG
#endif

#include "common/format/format_as_octal.h"
#include <cassert>
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file test_format_as_octal.cpp
//
// \brief Tests for formatting integers into octal strings
//
//////////////////////////////////////////////////////////////////////////////

using format::OctalPrefix;

struct Test2Traits : format::DefaultOctalFormatTraits
{
    static constexpr OctalPrefix Prefix = OctalPrefix::LEADING_ZERO;
};

struct Test3Traits : format::DefaultOctalFormatTraits
{
    static constexpr size_t NumberOfDigits = 5;
};


int main(int argc, char* argv[])
{
    // TEST 1: default formatting
    {
        std::string result = format::format_as_octal<>(042u);
        assert(result == "42");
    }

    // TEST 2: leading zero prefix
    {
        std::string result = format::format_as_octal<Test2Traits>(073u);
        assert(result == "073");
    }

    // TEST 3: leading zeroes (not zero prefix)
    {
        std::string result = format::format_as_octal<Test3Traits>(031u);
        assert(result == "00031");
    }

    return 0; // Success
}
