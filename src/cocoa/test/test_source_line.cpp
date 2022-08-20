#ifdef NDEBUG
    #undef NDEBUG
#endif

#include "cocoa/source_line.h"
#include <cassert>

//////////////////////////////////////////////////////////////////////////////
//
// \file test_source_line.cpp
//
// \brief Tests for the SourceLine class
//
//////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	// TEST 1: (3 operands) LABEL -> MNEMONIC -> OPERAND
	{
		try
		{
			const std::string text = "loop jmp     afar\n";
			assembly::SourceLine line(text);
			assert(line.has_source_line_number() == false);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 3);
			assert(line.parsed_token(0) == "loop");
			assert(line.token_offset(0) == text.find("loop"));
			assert(line.token_in_source(0) == "loop");
			assert(line.parsed_token(1) == "jmp");
			assert(line.token_offset(1) == text.find("jmp"));
			assert(line.token_in_source(1) == "jmp");
			assert(line.parsed_token(2) == "afar");
			assert(line.token_offset(2) == text.find("afar"));
			assert(line.token_in_source(2) == "afar");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 1: Caught unexpected ParseError exception");
		}
	}

	// TEST 2: (2 operands) LABEL -> MNEMONIC  -and-  MNEMONIC -> OPERAND
	{
		try
		{
			const std::string text = "clear   clra  ";
			assembly::SourceLine line(text);
			assert(line.has_source_line_number() == false);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 2);
			assert(line.parsed_token(0) == "clear");
			assert(line.token_offset(0) == text.find("clear"));
			assert(line.token_in_source(0) == "clear");
			assert(line.parsed_token(1) == "clra");
			assert(line.token_offset(1) == text.find("clra"));
			assert(line.token_in_source(1) == "clra");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 2: Caught unexpected ParseError exception");
		}
	}

	// TEST 3: (1 operand) MNEMONIC
	{
		try
		{
			assembly::SourceLine line("swi1");
			assert(line.has_source_line_number() == false);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 1);
			assert(line.parsed_token(0) == "swi1");
			assert(line.token_offset(0) == 0);
			assert(line.token_in_source(0) == "swi1");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 3: Caught unexpected ParseError exception");
		}
	}

	// TEST 4: LINE_NUMBER -> LABEL -> MNEMONIC -> OPERAND
	{
		try
		{
			const std::string text = "00100 main lda #0";
			assembly::SourceLine line(text);
			assert(line.has_source_line_number() == true);
			assert(line.source_line_number() == 100);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 3);
			assert(line.parsed_token(0) == "main");
			assert(line.token_offset(0) == text.find("main"));
			assert(line.token_in_source(0) == "main");
			assert(line.parsed_token(1) == "lda");
			assert(line.token_offset(1) == text.find("lda"));
			assert(line.token_in_source(1) == "lda");
			assert(line.parsed_token(2) == "#0");
			assert(line.token_offset(2) == text.find("#0"));
			assert(line.token_in_source(2) == "#0");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 4: Caught unexpected ParseError exception");
		}
	}

	// TEST 5: LINE_NUMBER -> MNEMONIC -> OPERAND
	{
		try
		{
			const std::string text = "10 org $3F00";
			assembly::SourceLine line(text);
			assert(line.has_source_line_number() == true);
			assert(line.source_line_number() == 10);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 2);
			assert(line.parsed_token(0) == "org");
			assert(line.token_offset(0) == text.find("org"));
			assert(line.token_in_source(0) == "org");
			assert(line.parsed_token(1) == "$3F00");
			assert(line.token_offset(1) == text.find("$3F00"));
			assert(line.token_in_source(1) == "$3F00");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 5: Caught unexpected ParseError exception");
		}
	}

	// TEST 6: Comment line
	{
		try
		{
			assembly::SourceLine line("  ;this line is a comment");
			assert(line.has_source_line_number() == false);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 0);
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 6: Caught unexpected ParseError exception");
		}
	}

	// TEST 7: Blank line
	{
		try
		{
			assembly::SourceLine line("   \n");
			assert(line.has_source_line_number() == false);
			assert(line.is_blank_line());
			assert(line.num_tokens() == 0);
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 7: Caught unexpected ParseError exception");
		}
	}

	// TEST 8: Double-quoted strings (with spaces) as a single token
	{
		try
		{
			const std::string text = "hello fcs \"hello world!\"";
			assembly::SourceLine line(text);
			assert(line.has_source_line_number() == false);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 3);
			assert(line.parsed_token(0) == "hello");
			assert(line.token_offset(0) == text.find("hello"));
			assert(line.token_in_source(0) == "hello");
			assert(line.parsed_token(1) == "fcs");
			assert(line.token_offset(1) == text.find("fcs"));
			assert(line.token_in_source(1) == "fcs");
			assert(line.parsed_token(2) == "\"hello world!\"");
			assert(line.token_offset(2) == text.find("\"hello world!\""));
			assert(line.token_in_source(2) == "\"hello world!\"");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 8: Caught unexpected ParseError exception");
		}
	}

	// TEST 9: Too many tokens on line
	{
		try
		{
			assembly::SourceLine line("token1 token2 token3 token4");
			assert(!"Test 9: Did not catch ParseError exception");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(err.error_type() == assembly::SourceLine::ErrorType::TooManyTokensOnLine);
		}
	}

	// TEST 10: LINE_NUMBER with no other tokens
	{
		try
		{
			assembly::SourceLine line("42");
			assert(line.has_source_line_number() == true);
			assert(line.source_line_number() == 42);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 0);
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 10: Caught unexpected ParseError exception");
		}
	}

	// TEST 11: LINE_NUMBER with only a comment token
	{
		try
		{
			assembly::SourceLine line("99 ; just a comment");
			assert(line.has_source_line_number() == true);
			assert(line.source_line_number() == 99);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 0);
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 11: Caught unexpected ParseError exception");
		}
	}

	// Test 12: First token on line begins with digit but is not a valid line number
	{
		// Likely this will result in some kind of ParseError eventually, but it is not
		// the SourceLine's responsibility to understand what constitutes valid LABELs,
		// MNEMONICs, or OPERANDs;  it only understands line numbers.
		try
		{
			assembly::SourceLine line("10clra");
			assert(line.has_source_line_number() == false);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 1);
			assert(line.parsed_token(0) == "10clra");
			assert(line.token_offset(0) == 0);
			assert(line.token_in_source(0) == "10clra");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 12: Caught unexpected ParseError exception");
		}
	}

	// Test 13: Double-quoted string with embedded double-quotes and other fun stuff
	{
		try
		{
			const std::string text = R"(nasty fcs "A \"string\" with \embedded \\quotes")";
			assembly::SourceLine line(text);
			assert(line.has_source_line_number() == false);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 3);
			assert(line.parsed_token(0) == "nasty");
			assert(line.token_offset(0) == text.find("nasty"));
			assert(line.token_in_source(0) == "nasty");
			assert(line.parsed_token(1) == "fcs");
			assert(line.token_offset(1) == text.find("fcs"));
			assert(line.token_in_source(1) == "fcs");
			assert(line.parsed_token(2) == R"("A "string" with \embedded \\quotes")");
			assert(line.token_offset(2) == text.find(R"("A \"string\" with \embedded \\quotes")"));
			assert(line.token_in_source(2) == R"("A \"string\" with \embedded \\quotes")");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 13: Caught unexpected ParseError exception");
		}
	}

	// Test 14: Space required after closing double-quote
	{
		try
		{
			assembly::SourceLine line("text fcs \"hello\";comment here");
			assert(!"Test 14: Did not catch ParseError exception");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(err.error_type() == assembly::SourceLine::ErrorType::NoSpaceAfterClosingQuote);
		}
	}

	// Test 15: Line number too large
	{
		try
		{
			assembly::SourceLine("1000000");
			assert(!"Test 15: Did not catch ParseError exception");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(err.error_type() == assembly::SourceLine::ErrorType::LineNumberOutOfRange);
		}
	}

	// Test 16: Unterminated string
	{
		try
		{
			assembly::SourceLine line("str fcs \"hello");
			assert(!"Test 16: Did not catch ParseError exception");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(err.error_type() == assembly::SourceLine::ErrorType::UnterminatedString);
		}
	}

	// Test 17: LINE_NUMBER must begin at column 0, otherwise it is a token
	{
		try
		{
			assembly::SourceLine line("\t42");
			assert(line.has_source_line_number() == false);
			assert(!line.is_blank_line());
			assert(line.num_tokens() == 1);
			assert(line.parsed_token(0) == "42");
		}
		catch (const assembly::SourceLine::ParseError& err)
		{
			assert(!"Test 17: Caught unexpected ParseError exception");
		}
	}

	return 0; // Success
}

