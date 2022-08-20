#include "tokenize.h"
#include <cstdio>
#include <map>
#include <utility>

///////////////////////////////////////////////////////////////////////////////
//
// \file tokenize.cpp
//
// \brief Recognizes tokens in the assembler language
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Recognize the first token in the input_text
	//
	// \pre input_text does not start with leading whitespace, unless
	//      the text is all whitespace.
	Token recognize_token(std::string_view input_text)
	{
		static_assert(
			static_cast<int>(TokenID::NUM_VALUES) == 33,
			"This function probably needs to be updated!"
		);

		static const std::map<char, TokenID> single_char_tokens = {
			{ '.', TokenID::DOT },
			{ '#', TokenID::OCTOTHORPE },
			{ '%', TokenID::PERCENT_SIGN },
			{ '$', TokenID::DOLLAR_SIGN },
			{ '"', TokenID::DOUBLE_QUOTE },
			{ '\'', TokenID::SINGLE_QUOTE },
			{ '/', TokenID::FRONT_SLASH },
			{ ',', TokenID::COMMA },
			{ '[', TokenID::LEFT_BRACKET },
			{ ']', TokenID::RIGHT_BRACKET },
			{ '*', TokenID::ASTERISK },
			{ '^', TokenID::CARET },
			{ '&', TokenID::AMPERSAND },
			{ '|', TokenID::PIPE },
			{ '~', TokenID::TILDE },
			{ '=', TokenID::EQUAL_SIGN },
			{ '(', TokenID::LEFT_PARENTHESIS },
			{ ')', TokenID::RIGHT_PARENTHESIS },
			{ '{', TokenID::LEFT_BRACE },
			{ '}', TokenID::RIGHT_BRACE },
			{ '<', TokenID::LESS_THAN },
			{ '>', TokenID::GREATER_THAN },
			{ '+', TokenID::PLUS_SIGN },
			{ '-', TokenID::MINUS_SIGN },
			{ '!', TokenID::EXCLAMATION_POINT }
		};

		static const std::map<std::pair<char, char>, TokenID> double_char_tokens = {
			{ { '<', '=' }, TokenID::LESS_THAN_OR_EQUAL },
			{ { '<', '>' }, TokenID::NOT_EQUAL },
			{ { '!', '=' }, TokenID::NOT_EQUAL },
			{ { '>', '=' }, TokenID::GREATER_THAN_OR_EQUAL },
			{ { '+', '+' }, TokenID::INCREMENT },
			{ { '-', '-' }, TokenID::DECREMENT }
		};

		if (input_text.empty())
		{
			return Token(TokenID::NONE, input_text);
		}

		if (input_text.length() > 1)
		{
			auto iter = double_char_tokens.find(
				std::make_pair(input_text[0], input_text[1])
			);

			if (iter != double_char_tokens.end())
			{
				return Token(iter->second, input_text, 2);
			}
		}

		{ // Scoping "iter"
			auto iter = single_char_tokens.find(input_text[0]);
			if (iter != single_char_tokens.end())
			{
				return Token(iter->second, input_text, 1);
			}
		}

		if (input_text[0] == ';')
		{
			return Token(TokenID::COMMENT, input_text);
		}

		// We did not recognize any token, so either the input_text is
		// all whitespace (in which case there is no recognized token)
		// or the input_text begins with a non-blank character and we
		// return a TEXT token consisting of all characters from the
		// beginning of the input_text until the first whitespace or
		// or a newline or the end of the string.  In all cases, the
		// returned token text WILL NOT contain any whitespace.
		//
		size_t offset_of_last_non_whitespace = 0;
		while (
			offset_of_last_non_whitespace < input_text.length() &&
			!::isspace(input_text[offset_of_last_non_whitespace])
			  )
		{
			++offset_of_last_non_whitespace;
		}

		if (offset_of_last_non_whitespace == 0)
		{
			return Token(TokenID::NONE, input_text, 0);
		}

		return Token(TokenID::TEXT, input_text, offset_of_last_non_whitespace);
	}

} // namespace assembly
