#pragma once

#include <string>
#include <vector>

namespace emulator6502
{
struct Instruction
{
    uint8_t opcode;
    uint8_t operandSize;
};

class Assembler
{
  public:
    Assembler() = default;

    std::vector<uint8_t> Assemble(const std::string &asmCode);

  private:
    void appendOperand(std::vector<uint8_t> &machineCode, const std::string &operand, uint8_t operandSize);
};

}