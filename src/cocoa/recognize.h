#pragma once

#include <optional>

///////////////////////////////////////////////////////////////////////////////
//
// \file recognize.h
//
// \brief Parses a line of source code
//
//        A line of source code could be an instruction, assembler directive,
//        or a comment/blank line.  We further break down assembler directives
//        into sub-categories as follows: ........
//
//        Instruction:
//        A source line may have a label as the first token, so we parse as
//        follows:  we attempt to parse the first token as an instruction.
//        If that fails, and there are at least two tokens on the line, then
//        we assume the first token is a label and try to parse the second
//        token as an instruction.  If that also fails, then the parse fails,
//        but no error is generated because the source line may contain
//        something other than an instruction (for example an assembler
//        directive).
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	class SourceLine;


	//! \brief Parses a line of source code according to what it is
	class Recognize
	{

#define DECLARE_RECOGNIZE_METHOD(Name, ReturnType) \
	std::optional<ReturnType> Name(                \
        const SourceLine& source_line              \
    )

	public:
		//! \brief Tries to parse the given source line as a line containing
		//!        an executable instruction.
		//!
		//! \return An empty optional if no valid executable instruction
		//!         was found in the first or second token, otherwise
		//!         the recognized instruction.
		//!
		//! \note The following conditions will cause a RecognizerError to
		//!       be thrown:
		//!         * An instruction was recognized, but the source line
		//!           has the wrong number of operands.  WE DO NOT CHECK
		//!           THE ADDRESSING MODE HERE; WE ONLY CHECK THE NUMBER
		//!           OF OPERANDS.
		DECLARE_RECOGNIZE_METHOD(recognize_instruction, InstructionNode);

		DECLARE_RECOGNIZE_METHOD(recognize_title_directive, TitleNode);

		DECLARE_RECOGNIZE_METHOD(recognize_proc_directive, ProcNode);

		DECLARE_RECOGNIZE_METHOD(recognize_struct_directive, StructNode);

		DECLARE_RECOGNIZE_METHOD(recognize_union_directive, UnionNode);

		DECLARE_RECOGNIZE_METHOD(recognize_setdp_directive, SetDPNode);

		DECLARE_RECOGNIZE_METHOD(recognize_org_align_even_odd_directive, AlignNode);

		DECLARE_RECOGNIZE_METHOD(recognize_data_directive, DataNode);

		DECLARE_RECOGNIZE_METHOD(recognize_equ_set_directive, EquNode);

		DECLARE_RECOGNIZE_METHOD(recognize_endu_ends_endn_end_directive, EndBlockNode);

		DECLARE_RECOGNIZE_METHOD(recognize_namespace_directive, NamespaceNode);

		DECLARE_RECOGNIZE_METHOD(recognize_include_directive, IncludeNode);

		DECLARE_RECOGNIZE_METHOD(recognize_includebin_directive, IncludeBinaryNode);

		DECLARE_RECOGNIZE_METHOD(recognize_call_directive, CallNode);

	private:
	}; // class Recognize

} // namespace assembly
