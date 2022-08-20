#pragma once

#include "token_id.h"
#include <string>
#include <string_view>

///////////////////////////////////////////////////////////////////////////////
//
// \file tokenize.h
//
// \brief Recognizes tokens in the assembler language
//
//        Tokens are delimited by whitespace (tabs or spaces) or newlines.
//
//        The following tokens are recognized specially:
//
//        COMMENTs, which begin with a semicolon and end at a newline,
//        are recognized as a single token.  Consecutive lines containing
//        nothing but comments are recognized as multiple tokens, one for
//        each line.
//
//        LESS_THAN_OR_EQUAL is recognized in preference to LESS_THAN.
//        That is, LESS_THAN is recognized only if the character immediately
//        following the '<' is not '='.
//
//        GREATER_THAN_OR_EQUAL is recognized in preference to GREATER_THAN.
//        That is, GREATER_THAN is recognized only if the character
//        immediately following the '>' is not '='.
//
//        INCREMENT is recognized in preference to PLUS_SIGN.  That is,
//        PLUS_SIGN is recognized only if the character immediately
//        following the first '+' is not another '+'.  The upshot to this
//		  is that the text "x++2" will be recognized as the three tokens
//        TEXT -> INCREMENT -> TEXT which likely will result in a parse
//        error.  The text "x+ +2" will be recognized as the four tokens
//		  TEXT -> PLUS_SIGN -> PLUS_SIGN -> TEXT and would be parsed
//		  as adding +2 to x.
//
//        DECREMENT is recognized in preference to MINUS_SIGN.  That is,
//		  MINUS_SIGN is recognized only if the character immediately
//		  following the first '-' is not another '-'.  The upshot to this
//		  is that the text "x--" will be recognized as the three tokens
//        TEXT -> DECREMENT -> TEXT which likely will result in a parse
//        error.  The text "x- -2" will be recognized as the four tokens
//        TEXT -> MINUS_SIGN -> MINUS_SIGN -> TEXT and would be parsed
//        as subtracting -2 from x.
//
//        NONE is recognized only if the input text consists entirely of
//        whitespace or is just a newline.
//
//        TEXT is recognized only if the input text is not empty (only
//		  a newline), not whitespace, and does not match any other token.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Information about a recognized token
	struct Token
	{
		//! \brief Token consumes all characters in text
		Token(TokenID type, std::string_view text);

		//! \brief Token consumes only first num_chars characters in text
		Token(TokenID type, std::string_view text, size_t num_chars);

		//! \brief Type of recognized token
		TokenID type() const;

		//! \brief Part of text consumed by the token
		std::string_view text() const;

	private:
		TokenID     _type; //!< Type of token recognized
		std::string _text; //!< Token as it appeared in the source code
	}; // struct Token


	//! \brief Recognize the first token in the input_text
	Token recognize_token(std::string_view input_text);

} // namespace assembly

#include "tokenize.inl"
