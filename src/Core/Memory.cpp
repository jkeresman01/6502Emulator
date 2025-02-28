#include "Memory.h"

#include <cstdint>

namespace emulator6502
{

void Memory::Init()
{
    Reset();
}

void Memory::Reset()
{
    for (std::size_t i = 0; i < MEMORY_16KB; ++i)
        s_RAM[i] = 0;
}

uint8_t Memory::Read(uint16_t address)
{
    return s_RAM[address];
}

void Memory::Write(const uint16_t address, const uint8_t value)
{
    s_RAM[address] = value;
}

} // namespace emulator6502
