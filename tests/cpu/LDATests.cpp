#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502Test : public ::testing::Test
{
  protected:
    CPU6502 cpu;

    void SetUp() override
    {
        Memory::Reset();
        cpu.Init();
    }

    void TearDown() override
    {
        cpu.Reset();
        Memory::Reset();
    }
};

TEST_F(CPU6502Test, LDAImmediate)
{
    Memory::Write(0x8000, 0xA9);
    Memory::Write(0x8001, 0x42);

    cpu.Reset();
    cpu.Step();

    EXPECT_EQ(cpu.GetAccumulator(), 0x42);
}
