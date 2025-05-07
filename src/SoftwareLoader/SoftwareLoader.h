#pragma once

#include <cstdint>

#include "../Core/Memory.h"

namespace emulator6502
{
using Byte = uint8_t;

class SoftwareLoader
{
  public:
    SoftwareLoader() = delete;

    static void Load(const std::vector<Byte> &machineCode);
};

static void Load(const std::vector<Byte> &machineCode)
{
    for (size_t i = 0; i < machineCode.size(); ++i)
    {
        Memory::s_RAM[0x8000 + i] = machineCode[i];
    }
}

} // namespace emulator6502