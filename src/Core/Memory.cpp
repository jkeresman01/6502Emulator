#include "Memory.h"

#include <cstdint>

namespace emulator6502
{

Byte Memory::s_RAM[MEMORY_64KB] = {0};

void Memory::Init()
{
    Reset();
}

void Memory::Reset()
{
    for (size_t i = 0; i < MEMORY_64KB; ++i)
    {
        s_RAM[i] = 0x00;
    }
}

Byte Memory::Read(const Word address)
{
    return s_RAM[address];
}

void Memory::Write(const Word address, const Byte value)
{
    s_RAM[address] = value;
}

} // namespace emulator6502
