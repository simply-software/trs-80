#ifdef NDEBUG
    #undef NDEBUG
#endif

#include "cocoa/tokenize.h"
#include <cassert>

//////////////////////////////////////////////////////////////////////////////
//
// \file test_tokenize.cpp
//
// \brief Tests for the token recognizer
//
//////////////////////////////////////////////////////////////////////////////

using assembly::Token;
using assembly::TokenID;

int main(int argc, char* argv[])
{
	// TEST 1: Single character token recognition
	{
		Token result = assembly::recognize_token("#abc");
		assert(result.type() == TokenID::OCTOTHORPE);
		assert(result.text() == "#");

		result = assembly::recognize_token(".*");
		assert(result.type() == TokenID::DOT);
		assert(result.text() == ".");

		result = assembly::recognize_token("%^");
		assert(result.type() == TokenID::PERCENT_SIGN);
		assert(result.text() == "%");

		result = assembly::recognize_token("%^");
		assert(result.type() == TokenID::PERCENT_SIGN);
		assert(result.text() == "%");

		result = assembly::recognize_token("$#!");
		assert(result.type() == TokenID::DOLLAR_SIGN);
		assert(result.text() == "$");

		result = assembly::recognize_token("\"hello");
		assert(result.type() == TokenID::DOUBLE_QUOTE);
		assert(result.text() == "\"");

		result = assembly::recognize_token("'a");
		assert(result.type() == TokenID::SINGLE_QUOTE);
		assert(result.text() == "'");

		result = assembly::recognize_token("/*");
		assert(result.type() == TokenID::FRONT_SLASH);
		assert(result.text() == "/");

		result = assembly::recognize_token(",:;");
		assert(result.type() == TokenID::COMMA);
		assert(result.text() == ",");

		result = assembly::recognize_token("[]");
		assert(result.type() == TokenID::LEFT_BRACKET);
		assert(result.text() == "[");

		result = assembly::recognize_token("]#$[");
		assert(result.type() == TokenID::RIGHT_BRACKET);
		assert(result.text() == "]");

		result = assembly::recognize_token("* $");
		assert(result.type() == TokenID::ASTERISK);
		assert(result.text() == "*");

		result = assembly::recognize_token("^!");
		assert(result.type() == TokenID::CARET);
		assert(result.text() == "^");

		result = assembly::recognize_token("&|");
		assert(result.type() == TokenID::AMPERSAND);
		assert(result.text() == "&");

		result = assembly::recognize_token("|&");
		assert(result.type() == TokenID::PIPE);
		assert(result.text() == "|");

		result = assembly::recognize_token("~\n");
		assert(result.type() == TokenID::TILDE);
		assert(result.text() == "~");

		result = assembly::recognize_token("=");
		assert(result.type() == TokenID::EQUAL_SIGN);
		assert(result.text() == "=");

		result = assembly::recognize_token("()");
		assert(result.type() == TokenID::LEFT_PARENTHESIS);
		assert(result.text() == "(");

		result = assembly::recognize_token(")))");
		assert(result.type() == TokenID::RIGHT_PARENTHESIS);
		assert(result.text() == ")");

		result = assembly::recognize_token("{struct}");
		assert(result.type() == TokenID::LEFT_BRACE);
		assert(result.text() == "{");

		result = assembly::recognize_token("};");
		assert(result.type() == TokenID::RIGHT_BRACE);
		assert(result.text() == "}");

		result = assembly::recognize_token("; this is a comment\n");
		assert(result.type() == TokenID::COMMENT);
		assert(result.text() == "; this is a comment\n");

		result = assembly::recognize_token("Text that does not fit");
		assert(result.type() == TokenID::TEXT);
		assert(result.text() == "Text");
	}

	// TEST 2: Multiple character token recognition
	{
		Token result = assembly::recognize_token("-=");
		assert(result.type() == TokenID::MINUS_SIGN);
		assert(result.text() == "-");

		result = assembly::recognize_token("--");
		assert(result.type() == TokenID::DECREMENT);
		assert(result.text() == "--");

		result = assembly::recognize_token("+=");
		assert(result.type() == TokenID::PLUS_SIGN);
		assert(result.text() == "+");

		result = assembly::recognize_token("++");
		assert(result.type() == TokenID::INCREMENT);
		assert(result.text() == "++");

		result = assembly::recognize_token("<7");
		assert(result.type() == TokenID::LESS_THAN);
		assert(result.text() == "<");

		result = assembly::recognize_token("<=7");
		assert(result.type() == TokenID::LESS_THAN_OR_EQUAL);
		assert(result.text() == "<=");

		result = assembly::recognize_token("<>7");
		assert(result.type() == TokenID::NOT_EQUAL);
		assert(result.text() == "<>");

		result = assembly::recognize_token(">a");
		assert(result.type() == TokenID::GREATER_THAN);
		assert(result.text() == ">");

		result = assembly::recognize_token(">=!");
		assert(result.type() == TokenID::GREATER_THAN_OR_EQUAL);
		assert(result.text() == ">=");

		result = assembly::recognize_token("!=%");
		assert(result.type() == TokenID::NOT_EQUAL);
		assert(result.text() == "!=");

		result = assembly::recognize_token("!%5");
		assert(result.type() == TokenID::EXCLAMATION_POINT);
		assert(result.text() == "!");
	}

	// TEST 3: Edge cases
	{
		Token result = assembly::recognize_token(" stuff after space\n");
		assert(result.type() == TokenID::NONE);
		assert(result.text() == "");

		result = assembly::recognize_token("");
		assert(result.type() == TokenID::NONE);
		assert(result.text() == "");
	}

	return 0; // Success
}

