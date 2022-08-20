#pragma once

#include <stdexcept>
#include <string>

///////////////////////////////////////////////////////////////////////////////
//
// \file exception.h
//
// \brief Base class for all exceptions thrown by the assembler.
//
//        These exceptions can be:
//          1) Internal errors in the coding of the assembler;
//          2) As a result of errors in the user code
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Base class for all exceptions thrown by the assembler
	//!
	//!        Since the exceptions themselves don't know how to build
	//!        their error messages (this is elsewhere, in a common place
	//!        so we can easily change the format in the future), in order
	//!        to comply with what(), we have to have some memory allocated
	//!        somewhere to return a const char*.  This class holds that
	//!        memory.
	class Exception : public std::exception
	{
	protected:
		//! \brief Return the error message
		const char* what() const noexcept final;

	private:
		std::string _error_buffer; //!< Memory to hold error message
	}; // class Exception


	template <typename DerivedExceptionType, typename... Args>
	void throw_(Args&&... args) __attribute__ ((noreturn));

} // namespace assembly

#include "exception.inl"
