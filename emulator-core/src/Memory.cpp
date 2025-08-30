#include <emulator/core/Memory.h>

#include <algorithm>
#include <cstdint>

#include <emulator/shared/Assert.h>
#include <emulator/shared/Logger.h>

namespace emulator6502
{

Byte Memory::s_RAM[MEMORY_64KB] = {};

void Memory::Init()
{
    Reset();
}

static_assert(MEMORY_64KB == 65536, "MEMORY_64KB must be 65536 bytes (64KB)");

void Memory::Reset()
{
    std::fill(std::begin(s_RAM), std::end(s_RAM), 0x00);
}

Byte Memory::Read(const Word address)
{
    ASSERT(address < MEMORY_64KB);
    return s_RAM[address];
}

void Memory::Write(const Word address, const Byte value)
{
    ASSERT(address < MEMORY_64KB);
    s_RAM[address] = value;
}

} // namespace emulator6502
