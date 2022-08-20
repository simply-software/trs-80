#ifdef NDEBUG
    #undef NDEBUG
#endif

#include "common/format/format_as_int.h"
#include <cassert>
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file test_format_as_int.cpp
//
// \brief Tests for formatting integers into strings
//
//////////////////////////////////////////////////////////////////////////////


struct Test2Traits : format::DefaultIntFormatTraits
{
	static constexpr char PrependChar = '$';
};

struct Test3Traits : format::DefaultIntFormatTraits
{
	static constexpr size_t FixedWidthSize = 10;
};



int main(int argc, char* argv[])
{
    // TEST 1: default formatting
    {
        std::string result = format::format_as_int<>(42);
        assert(result == "42");
    }

	// TEST 2: prepending a character
	{
		std::string result = format::format_as_int<Test2Traits>(123);
		assert(result == "$123");
	}

	// TEST 3: negative numbers
	{
        std::string result = format::format_as_int<Test3Traits>(-2);
		assert(result == "-2");
	}

    return 0; // Success
}
