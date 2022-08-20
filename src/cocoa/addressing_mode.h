#pragma once

#include <cstdint>
#include <iosfwd>

////////////////////////////////////////////////////////////////
//
// \file addressing_mode.h
//
// \brief CPU addressing modes
//
//        Inherent addressing
//        Inherent addressing is used when the target
//        operand is inherently specified in the instruction
//        itself.  For example, the CLRA instruction specifies
//        to clear the A register.
//
//        Immediate addressing
//        Similar to extended addressing, instructions that
//        use this addressing mode specify their target as
//        either an 8-bit or 16-bit constant value that is
//        encoded in the instruction itself.  "Immediate"
//        implies the constant is used as DATA.  For example,
//        ADDA #$30 adds 0x30 to A.
//
//        Extended addressing
//        Similar to immediate addressing, instructions that
//        use this addressing mode specify their target as
//        either a 16-bit constant value that is encoded
//        in the instruction itself.  "Extended" implies
//        the constant is used as an ADDRESS (and thus
//        is always 16-bit).  For example, JSR $1234 jumps
//        to address 0x1234 as a subroutine call.
//
//        Extended indirect addressing
//        This mode is similar to extended addressing,
//        except that the 16-bit constant encoded into the
//        instruction is used as the ADDRESS OF AN ADDRESS.
//        For example, JSR [$1234] (where the square braces
//        indicate extended indirect addressing) would jump
//        to the address formed by the 16-bit word at memory
//        locations $1234 and $1235.
//
//        Indexed
//        Instructions that use this mode have two operands:
//        an index register and EITHER a 5-bit constant or
//        an 8-bit register name.  When the two operands are
//        added together, the result forms the address on
//        which the instruction acts.  For example, STA 2,X
//        stores the A register in the memory location (2+X),
//        and STA B,X stores the A register in the memory
//        location (B+X).  Note that the addition is always
//        UNSIGNED.  Indexed addressing is implied by use
//        of the X index register as an operand.
//
//        Indexed indirect addressing
//        This mode combines the address-specification
//        ability of indexed addressing with the address-of-
//        address ability of extended indirect addressing.
//        For example, STA [2,X] (where the square braces
//        indicate indirect addressing, and use of the X
//        index register indicates indexed addressing) stores
//        the A register into the 16-bit memory location formed
//        from reading memory locations (2+X) and (2+X+1).
//
//        Relative addressing
//        In this mode, the constant operand is treated as
//        either an 8-bit SIGNED or 16-bit SIGNED offset
//        from the PCR (program counter register, instruction
//        pointer, whatever you want to call it).  Note that
//        the PCR is moved to the next instruction AFTER
//        evaluation of this value, so that if the instruction
//        BRA $0585 is at memory location $0580, this assembles
//        to a 16-bit instruction whose relative offset is +5.
//        For assembly programmers, the only relevance here is
//        that BRA is a 16-bit instruction whose offset is 8-bit
//        and has range -128...+127, whereas LBRA is a 24-bit
//        instruction whose offset is 16-bit and has range
//        -32768...+32767.
//
//        Direct
//        In general, instructions that use Extended addressing
//        also support Direct addressing.  Direct addressing
//        allows the programmer to specify only the LOWER 8
//        bits of the address;  the UPPER 8 bits are taken from
//        the DP (direct page) register.  To specify this mode,
//        the left angle bracket is used:  JSR <$15 will form
//        the target jump address by using the DP register as
//        the upper 8-bits and $15 as the lower 8 bits.
//
////////////////////////////////////////////////////////////////

namespace assembly
{

    enum class AddressingMode : uint8_t
    {
        INHERENT          = 0, // aka no addressing mode
        IMMEDIATE         = 1, // constant (data)
        EXTENDED          = 2, // constant (address)
        EXTENDED_INDIRECT = 3, // constant (address of addr)
        INDEXED           = 4, // index register w/offset
        INDEXED_INDIRECT  = 5, // index reg is addr of addr
        RELATIVE          = 6, // address relative to PC
        DIRECT            = 7, // DP with 8-bit constant
        NUM_VALUES
    };

    //! \brief Output the symbol name (eg, "INHERENT")
    std::ostream& operator<<(std::ostream& os, AddressingMode a);

} // namespace assembly
