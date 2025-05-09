#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502SEITests : public ::testing::Test
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

TEST_F(CPU6502SEITests, WillSetInterruptFlagCorrectly)
{
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedBefore = cpu.GetStatusFlags()._;
    Byte zeroBefore = cpu.GetStatusFlags().Z;
    Byte negativeBefore = cpu.GetStatusFlags().N;

    Memory::Write(0x8000, 0x78); // SEI

    cpu.Step();

    EXPECT_EQ(cpu.GetStatusFlags().I, 1);

    EXPECT_EQ(cpu.GetStatusFlags().C, carryBefore);
    EXPECT_EQ(cpu.GetStatusFlags().D, decimalBefore);
    EXPECT_EQ(cpu.GetStatusFlags().V, overflowBefore);
    EXPECT_EQ(cpu.GetStatusFlags()._, notUsedBefore);
    EXPECT_EQ(cpu.GetStatusFlags().Z, zeroBefore);
    EXPECT_EQ(cpu.GetStatusFlags().N, negativeBefore);
}
