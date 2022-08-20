#pragma once

#include <cstdint>
#include <iosfwd>

///////////////////////////////////////////////////////////////////////////////
//
// \file token_id.h
//
// \brief A single token in the assembler language
//
//        See tokenize.h for information on how tokens are recognized.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

    //! \brief The tokens that are recognized
    enum class TokenID : uint8_t
    {
		NONE,				   //!< No token found in input text
		DOT,                   //!< .
		OCTOTHORPE,            //!< #
		PERCENT_SIGN,          //!< %
		DOLLAR_SIGN,           //!< $
		LESS_THAN,             //!< <
		GREATER_THAN,          //!< >
		DOUBLE_QUOTE,          //!< "
		SINGLE_QUOTE,          //!< '
		FRONT_SLASH,           //!< /
		COMMA,                 //!< ,
		PLUS_SIGN,             //!< +
		INCREMENT,             //!< ++
		MINUS_SIGN,            //!< -
		DECREMENT,             //!< --
		LEFT_BRACKET,          //!< [
		RIGHT_BRACKET,         //!< ]
		ASTERISK,              //!< *
		CARET,                 //!< ^
		AMPERSAND,             //!< &
		EXCLAMATION_POINT,     //!< !
		PIPE,                  //!< |
		TILDE,                 //!< ~
		EQUAL_SIGN,            //!< =
		LESS_THAN_OR_EQUAL,    //!< <=
		GREATER_THAN_OR_EQUAL, //!< >=
		NOT_EQUAL,             //!< <> _OR_ !=
		LEFT_PARENTHESIS,      //!< (
		RIGHT_PARENTHESIS,     //!< )
		LEFT_BRACE,            //!< {
		RIGHT_BRACE,           //!< }
		COMMENT,			   //!< ; ... \n
		TEXT,				   //!< Any chars that aren't the above
        NUM_VALUES
    };


    //! \brief Output as the token ID, eg "COMMA"
    std::ostream& operator<<(std::ostream& os, TokenID token);

} // namespace assembly
