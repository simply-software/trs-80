#ifdef NDEBUG
    #undef NDEBUG
#endif

#include "common/format/character_case.h"
#include <cassert>
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file test_char_case.cpp
//
// \brief Tests for converting strings to uppercase or lowercase
//
//////////////////////////////////////////////////////////////////////////////

using format::CharCase;


struct Test2Traits : format::DefaultCharCaseTraits
{
	static constexpr CharCase Case = CharCase::UPPER;
};

struct Test3Traits : format::DefaultCharCaseTraits
{
	static constexpr CharCase Case = CharCase::LOWER;
};


int main(int argc, char* argv[])
{
    // TEST 1: default formatting
    {
        std::string result = format::char_case<>("hello123");
        assert(result == "hello123");
    }

	// TEST 2: upper case
	{
		std::string result = format::char_case<Test2Traits>("987goodbye");
		assert(result == "987GOODBYE");
	}

	// TEST 3: lower case
	{
        std::string result = format::char_case<Test3Traits>("42colorMEBLUE");
		assert(result == "42colormeblue");
	}

    return 0; // Success
}
