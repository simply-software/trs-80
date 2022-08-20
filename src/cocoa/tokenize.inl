///////////////////////////////////////////////////////////////////////////////
//
// \file tokenize.inl
//
// \brief Recognizes tokens in the assembler language
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Token consumes all of text
	inline Token::Token(TokenID type, std::string_view text)
		: _type(type)
		, _text(text)
	{
		// Nothing to do
	}

	//! \brief Token consumes only first num_chars characters in text
	inline Token::Token(TokenID type, std::string_view text, size_t num_chars)
		: _type(type)
		, _text(text.substr(0, num_chars))
	{
		// Nothing to do
	}

	//! \brief Type of recognized token
	inline TokenID Token::type() const
	{
		return _type;
	}

	//! \brief Part of text consumed by the token
	inline std::string_view Token::text() const
	{
		return _text;
	}

} // namespace assembly
