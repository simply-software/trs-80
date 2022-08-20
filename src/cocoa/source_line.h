#pragma once

#include "exception.H"
#include <cstdint>
#include <functional>
#include <string>

///////////////////////////////////////////////////////////////////////////////
//
// \file source_line.h
//
// \brief Parses and holds information about a single line of source code.
//
//        This class does a pre-parse of the line according to the
//        following GRAMMAR:
//
//        STATEMENT ::= (blank line or comment)
//           |                   LABEL        ->  MNEMONIC  ->  OPERAND
//           |                   LABEL        ->  MNEMONIC
//           |                                    MNEMONIC  ->  OPERAND
//           |                                    MNEMONIC
//           |  LINE_NUMBER  ->  LABEL        ->  MNEMONIC  ->  OPERAND
//           |  LINE_NUMBER  ->                   MNEMONIC  ->  OPERAND
//			 |  LINE_NUMBER
//           ;
//
//        All rules end with an optional COMMENT.  COMMENTs are
//        recognized by a leading semicolon and end at the end of line.
//
//        Except for COMMENTs and quoted strings,  all other tokens are
//        delimited by whitespace;  this means that "1,X" would be recognized
//        as a valid OPERAND, "1, X" would be recognized as two separate
//        tokens "1," and "X", and '"1, X"' -- where there are actual
//        double-quotes in the source -- would be recognized as a single
//        token "1, X" (with the quotes).
//
//        LINE_NUMBER is recognized if the first token on the line begins
//        at column 0 and contains only the digits [0-9].  Line numbers may
//        begin with leading zeroes and are always parsed as base 10.
//
//        sourceLine does NOT understand the concept of a LABEL, MNEMONIC,
//        or OPERAND.  SourceLine only parses a line into an optional
//        line number followed by zero or more non-comment tokens.  Comments
//        are ignored.  As such, the grammar recognized by this class is
//        more generally and succintly defined as follows, where square
//        brackets indicate optionality:
//
//        STATEMENT ::= [LINE_NUMBER] [TOKEN] [TOKEN] [TOKEN] [COMMENT]
//
//        where ('man grep' as a starting point for help):
//            LINE_NUMBER = regex("[0-9]{1,}")
//            TOKEN       = regex("[^;\w]{1,}")
//            COMMENT     = regex(";.*")
//
// \note This class checks for numeric overflow on line numbers out of
//       practicality since we store line numbers in a C type.  But we
//       don't check for numeric overflow on numeric tokens that are
//       not line numbers for three reasons:
//
//         1. "numeric" to this class means base-10, whereas cocoa
//            allows users to use binary, octal, and hexadecimal
//            notations, all of which are parsed elsewhere;
//         2. What it means to "overflow" is not well-defined here,
//            as, for example, an fcb mnemonic (form constant byte)
//            would overflow at 256.
//         3. If we checked for overflow here, presumably we would
//            also need to check for underflow, which requires parsing
//            negative numbers, but this class does not recognize '-'
//            specially since line numbers cannot be negative.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

    //! \brief A source line along with its parsed representation
    class SourceLine
    {
	private:
		// As above, LABEL, MNEMONIC, and OPERAND
		static constexpr size_t MAX_TOKENS_PER_LINE = 3;

		// When EOL is reached, parser handles this "input" as final action
		static constexpr char   END_OF_LINE_CHAR    = '\0';

	public:
		//! \brief Construct and parses a line of source code according
		//!        to the GRAMMAR.
		//!
		//!        May throw ParseError
		explicit SourceLine(const std::string& text);

		//! \brief Return the number of non-LINE_NUMBER, non-COMMENT tokens
		size_t num_tokens() const;

		//! \brief Returns the requested parsed token [0...num_tokens()-1]
		std::string parsed_token(size_t index) const;

		//! \brief Returns the char offset into the line where token begins
		size_t token_offset(size_t index) const;

		//! \brief Returns the given token as it appeared in the original source line
		//!        (escape characters will be included)
		std::string token_in_source(size_t index) const;

		//! \brief Did we parse a line number?
		bool has_source_line_number() const;

		//! \brief Return the line number parsed.
		//! \pre   has_source_line_number() returns true
		size_t source_line_number() const;

		//! \brief Did the line have no tokens or comments?
		bool is_blank_line() const;

	private:
		//! \brief Tokenizes the line.  May throw ParseError
		void _parse();

		//! \brief Max line number supported
		uint32_t _max_line_number() const;

	private:
		struct Token
		{
			std::string _original_token;  //!< Token as it appeared in _source_line
			std::string _parsed_token;    //!< Unescaped version of token
			size_t      _offset_in_line;  //!< Where in _source_line the token started
		}; // struct Token

	public:
		//! \brief Enumeration of all parse errors this class may encounter
		enum class ErrorType : uint8_t
		{
			NONE                     = 0, //!< Used in absence of other errors
			TooManyTokensOnLine      = 1, //!< More than MAX_TOKENS_PER_LINE tokens
			UnterminatedString       = 2, //!< No closing double-quote found on line
			UnexpectedDoubleQuote    = 3, //!< Token may not contain double-quote
			NoSpaceBeforeSemicolon   = 4, //!< Token may not contain semicolon
			NoSpaceAfterClosingQuote = 5, //!< String must have whitespace after it
			LineNumberOutOfRange     = 6, //!< Line number > max value
			NUM_ERRORS
		};

		//! \brief The class that is thrown for all user-code that has parse errors
		class ParseError : public Exception
		{
		public:
	        //! \brief Construction
    	    ParseError(
        	    ErrorType          error_type, //!< Which error occurred
				const SourceLine&  source_line //!< SourceLine that caused error
        	);

			//! \brief Access the type of error that occurred
	        ErrorType error_type() const;

	    private:
    	    ErrorType   _error_type;      //!< Which error occurred
			std::string _source_line;     //!< Line of user code in error
			std::string _token_in_error;  //!< Token that caused the error
			size_t      _offset_of_token; //!< Where the token is in the source line
			size_t      _length_of_token; //!< Length of the token in the source line
		}; // class ParseError

	private:
		std::string  _source_line;                  //!< Original line of code
		uint32_t     _line_number;                  //!< Line number, if present, 0 otherwise
		size_t		 _num_tokens;                   //!< Non line-number tokens recgonized
		Token        _tokens[MAX_TOKENS_PER_LINE];  //!< Non-line number, non-comment tokens
		bool		 _has_comment;                  //!< Was there a comment on the line?

	private: // See comments to _parse() in .cpp file
		//! \brief Current state of the state machine in _parse()
        enum ParserState
        {
            RecognizeStartToken     = 0,
            RecognizeString         = 1,
            RecognizeToken          = 2,
			RecognizeEscapeSequence = 3,
			RequireWhitespace       = 4,
            End                     = 5
        };

		//! \brief Type of input that triggers an associated action
		enum CharType
		{
			EndOfLine     = 0, //!< End-of-input
			Digit         = 1, //!< Any digit [0-9]
			Semicolon     = 2, //!< Specifically a semi-colon
			DoubleQuote   = 3, //!< Specifically a double-quote
			NewLine       = 4, //!< \n or \r;  ASCII 0x0D or 0x0A
			Whitespace    = 5, //!< Newline, tab, or space
			NonWhitespace = 6, //!< *any character* that is not Whitespace
			AnyChar       = 7, //!< Neither EndOfLine nor a NewLine
			EndOfInput    = 8, //!< END_OF_LINE_CHAR specifically
			Backslash     = 9, //!< Used for escaping double-quotes
			MAX_CHARTYPES      //!< Used for static_assertions
		};

		//! \brief Defines the action to take in a given state for a given char input
		class ParserAction
		{
		private:
			using ActionFn = std::function<void(char input_char)>;

		public:
			//! \brief Construction for a normal action
			ParserAction(CharType input_char, ActionFn action, ParserState next_state);

			//! \brief Constructor for a parse error
			ParserAction(
				CharType          input_char,
				const SourceLine& line,
				ErrorType         error
			);

			//! \brief Is the given character handled by this action?
			bool input_type_matches(char ch) const;

			//! \brief Perform the action on the given input
			ParserState act(char ch) const;

		private:
			CharType    _input_type;  //!< Input handled by this action
			ActionFn    _action;      //!< Action to perform
			ParserState _next_state;  //!< State to transition to
			ErrorType   _error_type;  //!< Parse error that occurred
		}; // class ParserAction

	private: // Helpers used by _parse()
		std::string                _current_token;      //!< Token being recognized
		ParserState                _parser_state;       //!< State machine state
		size_t		               _current_offset;     //!< Offset into _source_line
		size_t                     _token_start_offset; //!< Offset in line where token started
    }; // class SourceLine

} // namespace assembly

#include "source_line.inl"
