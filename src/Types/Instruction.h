#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <string>

namespace emulator6502
{

using Byte = uint8_t;

struct Instruction
{
    Byte opcode;
    Byte operandCount;
};

struct DisassembledInstruction
{
    std::string mnemonic;
    Byte operandCount;
};


} // namespace emulator6502
