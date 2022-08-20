#include "source_line.h"
#include <cerrno>
#include <cstdlib>
#include <map>
#include <stdexcept>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
//
// \file source_line.cpp
//
// \brief Holds information about a single line of source code.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

    //! \brief Returns the requested parsed token [0...num_tokens()-1]
    std::string SourceLine::parsed_token(size_t index) const
    {
        if (index >= num_tokens())
        {
            throw std::range_error(
                "SourceLine: request to access token #" + std::to_string(index) +
                " is out of range (" + std::to_string(num_tokens()) + " on line"
            );
        }

        return _tokens[index]._parsed_token;
    }


    //! \brief Returns the char offsset into the line where token begins
    size_t SourceLine::token_offset(size_t index) const
    {
        if (index >= num_tokens())
        {
            throw std::range_error(
                "SourceLine: request to access token offset #" +
				std::to_string(index) + " is out of range (" +
				std::to_string(num_tokens()) + " on line"
            );
        }

        return _tokens[index]._offset_in_line;
    }


    //! \brief Returns the requested *unparsed* token [0...num_tokens()-1]
    std::string SourceLine::token_in_source(size_t index) const
    {
        if (index >= num_tokens())
        {
            throw std::range_error(
                "SourceLine: request to access token #" + std::to_string(index) +
                " is out of range (" + std::to_string(num_tokens()) + " on line"
            );
        }

        return _tokens[index]._original_token;
    }


    //! \brief Tokenizes the line
	//!
	//!        This is done with a state machine that implements an LL(0)
	//!        parser.
	//!
	//!        Each state has multiple possible valid inputs.  Thus, each
	//!        state is comprised of an array of ParserActions, only one
	//!        of which will be applied to the input.  The state machine
	//!        works by iterating the list of ParserActions and selecting
	//!        *the first* action that matches the input.  (Most states do
	//!        have multiple ParserActions whose input set overlaps).
	//!
	//!        A comment is recognized with by the semicolon character,
	//!        except when the semicolon is within a double-quoted string;
	//!        there it is interpreted as a semicolon.  Recognizing a
	//!        comment character causes the parse of the line to end
	//!        immediately; that is, the comment ends at the end of the
	//!        line.  Comments are not parsed as tokens.
	//!
	//!        A double-quoted string is a token that begins and ends with
	//!        a double-quote.  Double-quoted strings may themselves contain
	//!        double-quotes;  to do this, the embedded double-quotes must be
	//!        escaped with a backslash: "This is a \"double-quoted\" string".
	//!        Backslashes do not have any other meaning;  if they are not
	//!        followed immediately by a double-quote character then the
	//!        backslash is interpreted as a literal backslash.
	//!
	//!        Tokens may not contain embedded semicolons, which would be
	//!        interpreted as the beginning of a comment, except that the
	//!        parser requires at least one space between token and comment
	//!        (for readability of the assembler, not because of this
	//!        implementation).
	void SourceLine::_parse() // May throw ParseError
	{
		// Probably need to add actions if new CharTypes are defined
		static_assert(MAX_CHARTYPES == 10, "Check the code below");

		auto process_char =
			[this](char ch)
			{
				auto push_action =
					[this](char ch)
					{
						_current_token += ch;
						if (_current_token.size() == 1)
						{
							_token_start_offset = _current_offset;
						}
					};

				auto escaped_double_quote_action =
					[this](char ch)
					{
						// Replace the previous char, which must be a backslash,
						// with the double quote.
						_current_token[_current_token.size() - 1] = ch;
					};

				auto save_token_action =
					[this](char)
					{
						// Can hit this in End state; we may or may not have a token
						if (_current_token.empty())
						{
							return;
						}

						std::string token(
							_source_line.substr(
								_token_start_offset,
								_current_offset - _token_start_offset
							)
						);

						char* endptr = nullptr;
						unsigned long result = strtoul(token.c_str(), &endptr, 10);

						// Line numbers must:
						//   1) start at column 0 in the source code (my requirement)
						//   2) be actual numbers :)
						if (_token_start_offset == 0 && *endptr == '\0')
						{
							if (errno == ERANGE || result > _max_line_number())
							{
								throw_<ParseError>(ErrorType::LineNumberOutOfRange, *this);
							}

							_line_number = result;
						}
						else if (_num_tokens < MAX_TOKENS_PER_LINE)
						{
							_tokens[_num_tokens++] = {
								token,
								_current_token,
								_token_start_offset,
							};
						}
						else
						{
							throw_<ParseError>(ErrorType::TooManyTokensOnLine, *this);
						}
						_current_token.clear();
					};

				auto mark_comment_action =
					[this](char)
					{
						_has_comment = true;
					};

				auto no_action =
					[this](char)
					{
						// Nothing to do!
					};

				// State 0: RecognizeStartToken
				std::vector<ParserAction> s0_actions = {
					ParserAction(EndOfLine, no_action, End),
					ParserAction(Semicolon, mark_comment_action, End),
					ParserAction(DoubleQuote, push_action, RecognizeString),
					ParserAction(Whitespace, no_action, RecognizeStartToken),
					ParserAction(AnyChar, push_action, RecognizeToken)
				};

				// State 1: RecognizeString
				std::vector<ParserAction> s1_actions = {
					ParserAction(Backslash, push_action, RecognizeEscapeSequence),
					ParserAction(DoubleQuote, push_action, RequireWhitespace),
					ParserAction(EndOfLine, *this, ErrorType::UnterminatedString),
					ParserAction(NewLine, *this, ErrorType::UnterminatedString),
					ParserAction(AnyChar, push_action, RecognizeString)
				};

				// State 2: RecognizeToken
				std::vector<ParserAction> s2_actions = {
					ParserAction(EndOfLine, save_token_action, End),
					ParserAction(DoubleQuote, *this, ErrorType::UnexpectedDoubleQuote),
					ParserAction(Semicolon, *this, ErrorType::NoSpaceBeforeSemicolon),
					ParserAction(Whitespace, save_token_action, RecognizeStartToken),
					ParserAction(NonWhitespace, push_action, RecognizeToken),
				};

				// State 3: RecognizeEscapeSequence
				std::vector<ParserAction> s3_actions = {
					ParserAction(DoubleQuote, escaped_double_quote_action, RecognizeString),
					ParserAction(EndOfLine, *this, ErrorType::UnterminatedString),
					ParserAction(NewLine, *this, ErrorType::UnterminatedString),
					ParserAction(AnyChar, push_action, RecognizeString)
				};

				// State 4: RequireWhitespace (after closing double-quote)
				std::vector<ParserAction> s4_actions = {
					ParserAction(EndOfLine, save_token_action, End),
					ParserAction(Whitespace, save_token_action, RecognizeStartToken),
					ParserAction(NonWhitespace, *this, ErrorType::NoSpaceAfterClosingQuote)
				};

				// State 5: End (no chars after newline)
				std::vector<ParserAction> s5_actions = {
					ParserAction(EndOfInput, save_token_action, End)
				};

				std::vector<std::vector<ParserAction>> parser_actions = {
					s0_actions,
					s1_actions,
					s2_actions,
					s3_actions,
					s4_actions,
					s5_actions
				};

				const auto& current_state_actions = parser_actions[_parser_state];
				for(size_t i = 0; i < current_state_actions.size(); ++i)
				{
					if (current_state_actions[i].input_type_matches(ch))
					{
						_parser_state = current_state_actions[i].act(ch); // <-- may throw
						break;
					}
				}
			};

		for (_current_offset = 0; _current_offset < _source_line.size(); ++_current_offset)
		{
			process_char(_source_line[_current_offset]);
		}

		process_char(END_OF_LINE_CHAR);
	}


    //! \brief Is the given character handled by this action?
    bool SourceLine::ParserAction::input_type_matches(char ch) const
	{
		static_assert(MAX_CHARTYPES == 10, "Update this function");

		static const std::string newline("\n\r");
		static const std::string whitespace = newline + '\t' + ' ';

		switch (_input_type)
		{
			case EndOfLine:
				return ch == END_OF_LINE_CHAR;
			case Digit:
				return ch >= '0' && ch <= '9';
			case Semicolon:
				return ch == ';';
			case DoubleQuote:
				return ch == '"';
			case NewLine:
				return newline.find(ch) != std::string::npos;
			case Whitespace:
				return whitespace.find(ch) != std::string::npos;
			case NonWhitespace:
				return whitespace.find(ch) == std::string::npos;
			case AnyChar:
				return newline.find(ch) == std::string::npos && ch != END_OF_LINE_CHAR;
			case EndOfInput:
				return ch == END_OF_LINE_CHAR;
			case Backslash:
				return ch == '\\';
			case MAX_CHARTYPES:
				return false; // Should not get here
		}

		__builtin_unreachable();
	}


} // namespace assembly
