#ifdef NDEBUG
    #undef NDEBUG
#endif

#include "common/format/justification.h"
#include <cassert>
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file test_justification.cpp
//
// \brief Tests for formatting strings using justification and fill chars
//
//////////////////////////////////////////////////////////////////////////////

using format::Justification;


struct Test2Traits : format::DefaultJustificationTraits
{
	static constexpr size_t FieldWidth = 10;
};

struct Test3Traits : format::DefaultJustificationTraits
{
	static constexpr size_t        FieldWidth = 8;
	static constexpr char          FillChar = 'X';
	static constexpr Justification Justify = Justification::LEFT;
};

struct Test4Traits : format::DefaultJustificationTraits
{
	static constexpr size_t        FieldWidth = 8;
	static constexpr char          FillChar = '-';
	static constexpr Justification Justify = Justification::RIGHT;
};

struct Test5Traits : format::DefaultJustificationTraits
{
	static constexpr size_t        FieldWidth = 6;
	static constexpr char          FillChar = '=';
	static constexpr Justification Justify = Justification::CENTER;
};

struct Test6Traits : format::DefaultJustificationTraits
{
	static constexpr size_t        FieldWidth = 9;
	static constexpr char          FillChar = '~';
	static constexpr Justification Justify = Justification::CENTER;
};

struct Test7Traits : format::DefaultJustificationTraits
{
	static constexpr size_t FieldWidth = 1;
};

struct Test8Traits : format::DefaultJustificationTraits
{
	static constexpr size_t FieldWidth = 5;
};



int main(int argc, char* argv[])
{
    // TEST 1: default formatting
    {
        std::string result = format::justify<>("hello");
        assert(result == "hello");
    }

	// TEST 2: fixed width
	{
		std::string result = format::justify<Test2Traits>("bob");
		assert(result.length() == Test2Traits::FieldWidth);
	}

	// TEST 3: fill char, left justify
	{
        std::string result = format::justify<Test3Traits>("pear");
		assert(result == "pearXXXX");
	}

	// TEST 4: fill char, right justify
	{
        std::string result = format::justify<Test4Traits>("red");
		assert(result == "-----red");
	}

	// TEST 5: fill char, centered, equal spacing both sides
	{
        std::string result = format::justify<Test5Traits>("AB");
		assert(result == "==AB==");
	}

	// TEST 6: fill char, centered, different spacing both sides
	{
        std::string result = format::justify<Test6Traits>("fork");
		assert(result == "~~fork~~~");
	}

	// TEST 7: fixed width too small
	{
        std::string result = format::justify<Test7Traits>("boat");
		assert(result == "boat");
	}

	// TEST 8: fixed width just right
	{
        std::string result = format::justify<Test8Traits>("eddie");
		assert(result == "eddie");
	}

    return 0; // Success
}
