#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <cstdint>

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

//////////////////////////////////////////////////////////////
///
/// @class Assembler
///
/// @brief Translates assembly source code into 6502 machine code.
///
/// The assembler takes human-readable assembly instructions and
/// produces the corresponding bytecode representation that can be
/// executed by the CPU6502 emulator.
///
//////////////////////////////////////////////////////////////
class Assembler
{
public:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Default constructor
    ///
    //////////////////////////////////////////////////////////////
    Assembler() = default;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Assembles a block of assembly source code into
    ///        machine code bytes.
    ///
    /// @param [in] asmCode Assembly source code as a string
    ///
    /// @return A vector of bytes representing the assembled
    ///         machine code.
    ///
    //////////////////////////////////////////////////////////////
    std::vector<Byte> Assemble(const std::string& asmCode);

private:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Appends operand bytes to the machine code output.
    ///
    /// @param [out] machineCode Vector of machine code bytes to append to
    /// @param [in]  operand     Operand string from assembly code
    /// @param [in]  operandSize Expected size of the operand in bytes
    ///
    //////////////////////////////////////////////////////////////
    void appendOperands(std::vector<Byte>& machineCode,
                        const std::string& operand,
                        Byte operandSize);
};

} // namespace emulator6502

