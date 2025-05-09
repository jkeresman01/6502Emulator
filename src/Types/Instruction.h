#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <string>

namespace emulator6502
{
using Byte = uint8_t;

////////////////////////////////////////////////////////////
///
/// @struct Instruction
///
/// @brief Represents an instruction with its opcode
///        and operand count.
//
////////////////////////////////////////////////////////////
struct Instruction
{
    //////////////////////////////////////////////////////////////
    ///
    /// @brief The operation code for the instruction.
    ///
    //////////////////////////////////////////////////////////////
    Byte opcode;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief The number of operands for this instruction (0, 1, 2)
    ///
    //////////////////////////////////////////////////////////////
    Byte operandCount;
};

////////////////////////////////////////////////////////////
///
/// @struct DisassembledInstruction
///
/// @brief Represents a disassembled instruction with
///        its mnemonic and operand count.
///
////////////////////////////////////////////////////////////
struct DisassembledInstruction
{
    //////////////////////////////////////////////////////////////
    ///
    /// @brief The mnemonic representing the instruction.
    ///
    //////////////////////////////////////////////////////////////
    std::string mnemonic;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief The number of operands for this instruction (0, 1, 2)
    ///
    //////////////////////////////////////////////////////////////
    Byte operandCount;
};

} // namespace emulator6502
