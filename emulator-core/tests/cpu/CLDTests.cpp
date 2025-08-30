#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502CLDTests : public ::testing::Test
{
  protected:
    CPU6502 cpu;

    void SetUp() override
    {
        Memory::Init();
        cpu.Init();
    }

    void TearDown() override
    {
        cpu.Reset();
        Memory::Reset();
    }
};

TEST_F(CPU6502CLDTests, WillClearDecimalFlagCorrectly)
{
    // GIVEN
    cpu.SetFlags({0, 0, 0, 0, 1, 0, 0, 0});

    // WHEN
    Memory::Write(0x8000, 0xD8); // CLD
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetStatusFlags().D, 0);
}
