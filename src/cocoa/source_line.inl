///////////////////////////////////////////////////////////////////////////////
//
// \file source_line.inl
//
// \brief Holds information about a single line of source code.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Construct from a line of source code
	inline SourceLine::SourceLine(const std::string& text) :
		_source_line(text),
		_line_number(0),
		_num_tokens(0),
		_has_comment(false),
		_parser_state(RecognizeStartToken),
		_current_offset(0),
		_token_start_offset(0)
	{
		_parse();
	}


    //! \brief Return the number of non-LINE_NUMBER, non-COMMENT tokens
    inline size_t SourceLine::num_tokens() const
	{
		return _num_tokens;
	}


    //! \brief Did we parse a line number?
    inline bool SourceLine::has_source_line_number() const
	{
		return _line_number != 0;
	}


    //! \brief Return the line number parsed.
    inline size_t SourceLine::source_line_number() const
	{
		return _line_number;
	}


	//! \brief Did the line have no token and no comment?
	inline bool SourceLine::is_blank_line() const
	{
		return !has_source_line_number() && !_has_comment && _num_tokens == 0;
	}


	//! \brief Max line number supported in user code
	inline uint32_t SourceLine::_max_line_number() const
	{
		// Arbitrarily, 6 digits.  Alternatively, 65535 could be a thematic limit
		return 999999;
	}


    //! \brief Construction for a normal parser action
    inline SourceLine::ParserAction::ParserAction(
		CharType    input_char,
		ActionFn    action,
		ParserState next_state
	) : _input_type(input_char)
	  , _action(action)
	  , _next_state(next_state)
      , _error_type(ErrorType::NONE)
	{
		// Nothing to do
	}


	//! \brief Constructor for a parse error handling action
	inline SourceLine::ParserAction::ParserAction(
		CharType          input_char,
		const SourceLine& line_with_error,
		ErrorType         type_of_error
	) : _input_type(input_char)
      , _action(
			[this, line_with_error](char ch)
            {
				throw_<ParseError>(_error_type, line_with_error);
            }
		)
      , _next_state(End)
	  , _error_type(type_of_error)
	{
		// Nothing to do
	}


	//! \brief Constructor of a ParseError
	inline SourceLine::ParseError::ParseError(
		ErrorType         error_type,
		const SourceLine& source_line
	) : _error_type(error_type)
	  , _source_line(source_line._source_line)
	  , _token_in_error(source_line._current_token)
	  , _offset_of_token(source_line._token_start_offset)
 	  , _length_of_token(source_line._current_offset - source_line._token_start_offset)
	{
		// Nothing to do
	}


	//! \brief Access the type of parse error that occurred
	inline SourceLine::ErrorType SourceLine::ParseError::error_type() const
	{
		return _error_type;
	}


    //! \brief Perform the action on the given input
    inline SourceLine::ParserState SourceLine::ParserAction::act(char ch) const
	{
		_action(ch);
		return _next_state;
	}

} // namespace assembly
