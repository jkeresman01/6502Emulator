#pragma once

#define MEMORY_64KB 65536

#include <cstdint>

namespace emulator6502
{

class Memory
{
  public:
    Memory() = delete;

    static void Init();
    static void Reset();

    static uint8_t Read(const uint16_t address);
    static void Write(const uint16_t address, const uint8_t value);

    static uint8_t s_RAM[MEMORY_64KB];
};

} // namespace emulator6502
