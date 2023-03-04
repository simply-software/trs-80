#pragma once

#include "direct_page.h"
#include <cstdint>

///////////////////////////////////////////////////////////////////////////////
//
// \file logical_memory_address.h
//
// \brief Holds a 16-bit TRS-80 logical memory address
//
//        A logical address is an address that is directly accessible by
//        the CPU.  Regardless of the amount of RAM, the CPU only can
//        access 64K of memory (RAM/ROM).
//
//		  Although technically addressable, we consider memory location 0
//        as a 'null' address, which essentially means unspecified.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Holds a memory address
	class LogicalMemoryAddress
	{
	public:
		//! \brief Construct from an integer.
		explicit LogicalMemoryAddress(uint16_t address);

		//! \brief Is the address null?
		bool is_null() const;

		//! \brief Obtain the direct page that contains this address
		//!
		//!        The return value is not valid if is_null().
		DirectPage direct_page() const;

	private:
		uint16_t _memory_address; //!< The address
	}; // class LogicalMemoryAddress

} // namespace assembly

#include "logical_memory_address.inl"
