#pragma once

#include <cstdint>

///////////////////////////////////////////////////////////////////////////////
//
// \file cc_register.h
//
// \brief Definition of the Condition Codes (CC) register
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Defines the bits of the CC register
	class CCRegister
	{
	public:
		enum class Bits : uint8_t
		{
			C = 0x01, //!< Carry (8-bit operation caused carry or borrow)
			V = 0x02, //!< Overflow (operation caused signed overflow)
			Z = 0x04, //!< Zero (result of previous operation was zero)
			N = 0x08, //!< Negative (result of previous operation was negative)
			I = 0x10, //!< Interrupt (1=disable interrupts, 0=enable)
			H = 0x20, //!< Half Carry (Carry from bit 3)
			F = 0x40, //!< Fast Interrupt (1-disable fast interrupts)
			E = 0x80  //!< All registers saved on last interrupt
		};
	}; // class CCRegister

} // namespace assembly
