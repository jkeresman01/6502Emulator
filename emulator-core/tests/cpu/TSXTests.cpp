#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502TSXTests : public ::testing::Test
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

TEST_F(CPU6502TSXTests, WillTSXTransferPositiveValueCorrectly)
{
    cpu.Reset();
    cpu.SetStackPointer(0x42);
    Memory::Write(0x8000, 0xBA); // TSX

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedBefore = cpu.GetStatusFlags()._;

    cpu.Step();

    EXPECT_EQ(cpu.GetRegisterX(), 0x42);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);

    EXPECT_EQ(carryBefore, cpu.GetStatusFlags().C);
    EXPECT_EQ(interruptBefore, cpu.GetStatusFlags().I);
    EXPECT_EQ(decimalBefore, cpu.GetStatusFlags().D);
    EXPECT_EQ(overflowBefore, cpu.GetStatusFlags().V);
    EXPECT_EQ(notUsedBefore, cpu.GetStatusFlags()._);
}

TEST_F(CPU6502TSXTests, WillTSXSetNegativeFlagCorrectly)
{
    cpu.Reset();
    cpu.SetStackPointer(0xFF);
    Memory::Write(0x8000, 0xBA); // TSX

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedBefore = cpu.GetStatusFlags()._;

    cpu.Step();

    EXPECT_EQ(cpu.GetRegisterX(), 0xFF);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);

    EXPECT_EQ(carryBefore, cpu.GetStatusFlags().C);
    EXPECT_EQ(interruptBefore, cpu.GetStatusFlags().I);
    EXPECT_EQ(decimalBefore, cpu.GetStatusFlags().D);
    EXPECT_EQ(overflowBefore, cpu.GetStatusFlags().V);
    EXPECT_EQ(notUsedBefore, cpu.GetStatusFlags()._);
}
