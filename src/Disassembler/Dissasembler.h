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
