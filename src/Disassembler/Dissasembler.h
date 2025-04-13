#pragma once

#include <string>
#include <vector>

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

struct DisassembledInstruction
{
    std::string mnemonic;
    Byte operandSize;
};

class Disassembler
{
  public:
    Disassembler() = default;

    std::vector<std::string> Disassmble(const std::vector<Byte> &machineCode);

  private:
    void appendOperands(std::stringstream &ss, const std::vector<Byte> &machineCode,
                        std::size_t &programCounter, Byte operandSize);
};
} // namespace emulator6502
