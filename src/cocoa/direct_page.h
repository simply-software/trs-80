#pragma once

#include <cstdint>

///////////////////////////////////////////////////////////////////////////////
//
// \file direct_page.h
//
// \brief Holds an 8-bit value which represents the most significant byte
//        of a 16-bit address.
//
//        Certain opcodes that take a 16-bit address have a shortened form
//        that take only an 8-bit offset and use the value of the direct
//        page (DP) register as the upper 8-bits.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Holds an 8-bit value to be used as a Direct Page value
	class DirectPage
	{
	public:
		//! \brief Construct from an integer.
		explicit DirectPage(uint8_t page);

	private:
		uint8_t _direct_page; //!< The value
	}; // class DirectPage

} // namespace assembly

#include "direct_page.inl"
