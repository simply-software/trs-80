#include "token_id.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
//
// \file token_id.cpp
//
// \brief A single token in the assembler language
//
//        See tokenize.h for information on how tokens are recognized.
//
///////////////////////////////////////////////////////////////////////////////


namespace assembly
{

	std::ostream& operator<<(std::ostream& os, TokenID token)
	{
		static_assert(
			static_cast<uint8_t>(TokenID::NUM_VALUES) == 33,
			"Update this function please!"
		);

		switch (token)
		{
			case TokenID::NONE:                  return os << "NONE";
			case TokenID::DOT:					 return os << "DOT";
			case TokenID::OCTOTHORPE:            return os << "OCTOTHORPE";
			case TokenID::PERCENT_SIGN:          return os << "PERCENT_SIGN";
			case TokenID::DOLLAR_SIGN:           return os << "DOLLAR_SIGN";
			case TokenID::LESS_THAN:             return os << "LESS_THAN";
			case TokenID::GREATER_THAN:          return os << "GREATER_THAN";
			case TokenID::DOUBLE_QUOTE:          return os << "DOUBLE_QUOTE";
			case TokenID::SINGLE_QUOTE:          return os << "SINGLE_QUOTE";
			case TokenID::FRONT_SLASH:           return os << "FRONT_SLASH";
			case TokenID::COMMA:                 return os << "COMMA";
			case TokenID::PLUS_SIGN:             return os << "PLUS_SIGN";
			case TokenID::INCREMENT:             return os << "INCREMENT";
			case TokenID::MINUS_SIGN:            return os << "MINUS_SIGN";
			case TokenID::DECREMENT:             return os << "DECREMENT";
			case TokenID::LEFT_BRACKET:          return os << "LEFT_BRACKET";
			case TokenID::RIGHT_BRACKET:         return os << "RIGHT_BRACKET";
			case TokenID::ASTERISK:              return os << "ASTERISK";
			case TokenID::CARET:                 return os << "CARET";
			case TokenID::AMPERSAND:             return os << "AMPERSAND";
			case TokenID::EXCLAMATION_POINT:     return os << "EXCLAMATION_POINT";
			case TokenID::PIPE:                  return os << "PIPE";
			case TokenID::TILDE:                 return os << "TILDE";
			case TokenID::EQUAL_SIGN:            return os << "EQUAL_SIGN";
			case TokenID::LESS_THAN_OR_EQUAL:    return os << "LESS_THAN_OR_EQUAL";
			case TokenID::GREATER_THAN_OR_EQUAL: return os << "GREATER_THAN_OR_EQUAL";
			case TokenID::NOT_EQUAL:             return os << "NOT_EQUAL";
			case TokenID::LEFT_PARENTHESIS:      return os << "LEFT_PARENTHESIS";
			case TokenID::RIGHT_PARENTHESIS:     return os << "RIGHT_PARENTHESIS";
			case TokenID::LEFT_BRACE:            return os << "LEFT_BRACE";
			case TokenID::RIGHT_BRACE:           return os << "RIGHT_BRACE";
			case TokenID::COMMENT:               return os << "COMMENT";
			case TokenID::TEXT:                  return os << "TEXT";
			default: return os << "Invalid (" << static_cast<int>(token) << ')';
    	}
	}

} // namespace assembly
