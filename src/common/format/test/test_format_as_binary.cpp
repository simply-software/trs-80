#ifdef NDEBUG
    #undef NDEBUG
#endif

#include "common/format/format_as_binary.h"
#include <cassert>
#include <string>

//////////////////////////////////////////////////////////////////////////////
//
// \file test_format_as_binary.cpp
//
// \brief Tests for formatting integers into binary strings
//
//////////////////////////////////////////////////////////////////////////////

using format::BinaryPrefix;

template <BinaryPrefix PrefixValue>
struct Test2Traits : format::DefaultBinaryFormatTraits
{
	static constexpr BinaryPrefix Prefix = PrefixValue;
};


int main(int argc, char* argv[])
{
    // TEST 1: default formatting
    {
        std::string result1 = format::format_as_binary<>(
			(uint8_t)0b01100110);
        assert(result1 == "01100110");

		std::string result2 = format::format_as_binary<>(
			(int16_t)0b0000000001010110);
		assert(result2 == "0000000001010110");

		std::string result3 = format::format_as_binary<>(
			(uint32_t)0b10101010100001111);
		assert(result3 == "00000000000000010101010100001111");

		std::string result4 = format::format_as_binary<>(
			(int64_t)0b01011010011011101010101001001010);
		assert(result4 ==
			"0000000000000000000000000000000001011010011011101010101001001010");
    }

	// TEST 2: prepending characters
	{
		std::string result1 =
			format::format_as_binary<Test2Traits<BinaryPrefix::PREFIX_0b>>(
				(uint8_t)0b11001010
			);
		assert(result1 == "0b11001010");

		std::string result2 =
			format::format_as_binary<Test2Traits<BinaryPrefix::PREFIX_b>>(
				(uint8_t)0b11001010
			);
		assert(result2 == "b11001010");
	}

    return 0; // Success
}
