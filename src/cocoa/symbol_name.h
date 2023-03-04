#pragma once

#include <string>

///////////////////////////////////////////////////////////////////////////////
//
// \file symbol_name.h
//
// \brief Holds a symbol name
//
//        A symbol name is any token (identifier) that can symbolically
//        identify a user-level construct, such as the name of a procedure,
//		  struct, union, label, including special labels such as '<', '>',
//		  and '!'.
//
//        This class only holds the _name_, and not the 'value' of the
//        symbol (ie, body of the procedure, struct, union, or the
//		  constant for 'EQU' directives.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Holds a symbol name
	class SymbolName
	{
	public:
		//! \brief Construct from a string type
		template <typename StringType>
		SymbolName(const StringType& str);

		//! \brief Get the symbol name as it appears in source code
		const std::string& name() const;

		//! \brief Is the symbol the branch-point '!'?
		bool is_branch_point() const;

		//! \brief Is the symbol the previous-branch-point '<'?
		bool is_previous_branch_point() const;

		//! \brief Is the symbol the next-branch-point '>'?
		bool is_next_branch_point() const;

		//! \brief Is the symbol one of the special values '!', '<', or '>'?
		bool is_branch_point_symbol_type() const;

	private:
		std::string _symbol_name;
	}; // class SymbolName

} // namespace assembly

#include "symbol_name.inl"
