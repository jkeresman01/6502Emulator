#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

TEST(CPU6502, LDAImmediate)
{
    Memory::Reset();
    CPU6502 cpu;

    Memory::Write(0x8000, 0xA9);
    Memory::Write(0x8001, 0x42);

    cpu.Reset();
    cpu.Step();

    EXPECT_EQ(cpu.GetAccumulator(), 0x42);
}