#pragma once

#include <string>
#include <vector>

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

struct Instruction
{
    Byte opcode;
    Byte operandSize;
};

class Assembler
{
  public:
    Assembler() = default;

    std::vector<Byte> Assemble(const std::string &asmCode);

  private:
    void appendOperands(std::vector<Byte> &machineCode, const std::string &operand, Byte operandSize);
};

}