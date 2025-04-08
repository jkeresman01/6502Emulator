#pragma once

#include <vector>
#include <string>

namespace emulator6502
{
class Assembler
{
  public:
    Assembler() = default;

    std::vector<uint8_t> Assemble(const std::string &asmCode);
};
}