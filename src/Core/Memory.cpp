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
    if (addr >= 0x0000 && addr <= 0xFFFF)
    {
		return s_RAM[address];
    }
    else
    {
        EMULATOR_6502_ERROR(TEXT("Invalid address!"));
		return s_RAM[0x00];
    }
}

void Memory::Write(const Word address, const Byte value)
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
    {
		s_RAM[address] = value;
    }
    else
    {
        EMULATOR_6502_ERROR(TEXT("Invalid address!"));
    }
}

} // namespace emulator6502
