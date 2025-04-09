#pragma once

#define MEMORY_64KB 65536

#include <cstdint>

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

class Memory
{
  public:
    Memory() = delete;

    static void Init();
    static void Reset();

    static Byte Read(const Word address);
    static void Write(const Word address, const Byte value);

    static Byte s_RAM[MEMORY_64KB];
};

} // namespace emulator6502
