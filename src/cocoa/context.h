#pragma once

#include <cstdint>
#include <iosfwd>

///////////////////////////////////////////////////////////////////////////////
//
// \file context.h
//
// \brief Base class for holding a context
//
//       A context is essentially a reference to a piece of source code.
//       It could be a single line of source code (LineContext),
//		 multiple contiguous lines of source code (BlockContext), or an
//       entire source file (FileContext).
//
//       ParseContext also inherits Context and is used to represent the
//		 the current source location from which the next token will be read.
//
//		 The purpose of the context is two-fold:
//       1) It is through the context that the assembler knows where to
//          find the next token.  This is how the include mechanism works.
//       2) To generate useful error messages.
//
//		 BlockContext is simply an object that represents a block of source
//       lines and is largely used for generation of error messages.
//
//       A FileContext contains a LineContext, which represents the current
//       source line being recognized/parsed in that file, and optionally
//       another FileContext if another source file is being included.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{


    //! \brief Base class for a source code context
    class Context
    {
	public:
		//! \brief Destructor, for polymorphic support
		virtual ~Context() = default;

		//! \brief Parse the context
		virtual void parse() = 0; // May throw ParseError
    }; // class Context

} // namespace assembly
