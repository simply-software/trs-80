#ifdef NDEBUG
    #undef NDEBUG
#endif

#include "common/format/format_as_hex.h"
#include <cassert>
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file test_format_as_hex.cpp
//
// \brief Tests for formatting integers into hex strings
//
//////////////////////////////////////////////////////////////////////////////

using format::HexPrefix;

template <HexPrefix PrefixValue>
struct Test2Traits : format::DefaultHexFormatTraits
{
	static constexpr HexPrefix Prefix = PrefixValue;
};

template <size_t NumDigits>
struct Test3Traits : format::DefaultHexFormatTraits
{
	static constexpr size_t NumberOfDigits = NumDigits;
};

struct Test4Traits : format::DefaultHexFormatTraits
{
	static constexpr HexPrefix Prefix = HexPrefix::PREFIX_0x;
	static constexpr size_t    NumberOfDigits = 8;
};


int main(int argc, char* argv[])
{
    // TEST 1: default formatting
    {
        std::string result = format::format_as_hex<>(42u);
        assert(result == "2a");
    }

	// TEST 2: prefixes
	{
		std::string result1 =
			format::format_as_hex<Test2Traits<HexPrefix::PREFIX_0X>>(100u);
		assert(result1 == "0X64");

		std::string result2 =
			format::format_as_hex<Test2Traits<HexPrefix::PREFIX_0x>>(100u);
		assert(result2 == "0x64");

		std::string result3 =
			format::format_as_hex<Test2Traits<HexPrefix::PREFIX_X>>(100u);
		assert(result3 == "X64");

		std::string result4 =
			format::format_as_hex<Test2Traits<HexPrefix::PREFIX_x>>(100u);
		assert(result4 == "x64");
	}

	// TEST 3: leading zeroes
	{
        std::string result1 = format::format_as_hex<Test3Traits<5>>(49u);
		assert(result1 == "00031");

        std::string result2 = format::format_as_hex<Test3Traits<2>>(49u);
		assert(result2 == "31");

        std::string result3 = format::format_as_hex<Test3Traits<1>>(49u);
		assert(result3 == "31");
	}

	// TEST 4: prefixes and leading zeroes
	{
		std::string result = format::format_as_hex<Test4Traits>(0x1795u);
		assert(result == "0x00001795");
	}

    return 0; // Success
}
