#pragma once

#include "logical_memory_address.h"
#include "symbol_name.h"

///////////////////////////////////////////////////////////////////////////////
//
// \file label.h
//
// \brief Holds a label
//
//        A label is the first (optional) token on a source line.  In
//        this context, a label's 'value' is its address in memory.
//        It can be used as an operand to various instructions.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Holds a symbol and its address
	class Label
	{
	public:
		//! \brief Construct from a name and address
		Label(const SymbolName& symbol, LogicalMemoryAddress address);

		//! \brief Get the symbol name as it appears in source code
		const SymbolName& symbol_name() const;

		//! \brief Get the address that the symbol refers to
		LogicalMemoryAddress address() const;

	private:
		SymbolName           _symbol_name; //!< Name as it appears in source code
		LogicalMemoryAddress _address;     //!< Address that the symbol references
	}; // class Label

} // namespace assembly

#include "label.inl"
