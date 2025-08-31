#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <cstdint>
#include <sstream>

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

//////////////////////////////////////////////////////////////
///
/// @class Disassembler
///
/// @brief Translates 6502 machine code back into human-readable
///        assembly instructions.
///
/// The disassembler parses bytecode, decodes opcodes and operands,
/// and outputs a list of formatted assembly instructions.
///
//////////////////////////////////////////////////////////////
class Disassembler
{
public:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Default constructor
    ///
    //////////////////////////////////////////////////////////////
    Disassembler() = default;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Disassembles a block of machine code into assembly.
    ///
    /// @param [in] machineCode A vector of bytes representing
    ///        6502 machine code.
    ///
    /// @return A vector of strings, each containing one
    ///         disassembled assembly instruction.
    ///
    //////////////////////////////////////////////////////////////
    std::vector<std::string> Disassmble(const std::vector<Byte>& machineCode);

private:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Appends the operand(s) of an instruction to the
    ///        disassembly output stream.
    ///
    /// @param [out] ss              String stream receiving the
    ///                              formatted operand
    /// @param [in]  machineCode     Vector of machine code bytes
    /// @param [in,out] programCounter Current program counter index
    /// @param [in]  operandSize     Number of operand bytes to read
    ///
    //////////////////////////////////////////////////////////////
    void appendOperands(std::stringstream& ss,
                        const std::vector<Byte>& machineCode,
                        std::size_t& programCounter,
                        Byte operandSize);
};

} // namespace emulator6502

