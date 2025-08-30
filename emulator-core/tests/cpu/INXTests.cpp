#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502INXTests : public ::testing::Test
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

TEST_F(CPU6502INXTests, WillINXIncrementXRegisterCorrectly)
{
    // GIVEN
    cpu.Reset();
    cpu.SetRegisterX(0x42);
    Flags flagsBefore = cpu.GetStatusFlags();

    Memory::Write(0x8000, 0xE8); // INX

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x43);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Flags flagsAfter = cpu.GetStatusFlags();

    EXPECT_EQ(flagsAfter.C, flagsBefore.C);
    EXPECT_EQ(flagsAfter.I, flagsBefore.I);
    EXPECT_EQ(flagsAfter.D, flagsBefore.D);
    EXPECT_EQ(flagsAfter.B, flagsBefore.B);
    EXPECT_EQ(flagsAfter._, flagsBefore._);
    EXPECT_EQ(flagsAfter.V, flagsBefore.V);
}

TEST_F(CPU6502INXTests, WillINXSetZeroFlagWhenOverflowingFromFF)
{
    // GIVEN
    cpu.Reset();
    cpu.SetRegisterX(0xFF);
    Flags flagsBefore = cpu.GetStatusFlags();

    Memory::Write(0x8000, 0xE8); // INX

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Flags flagsAfter = cpu.GetStatusFlags();
    EXPECT_EQ(flagsAfter.C, flagsBefore.C);
    EXPECT_EQ(flagsAfter.I, flagsBefore.I);
    EXPECT_EQ(flagsAfter.D, flagsBefore.D);
    EXPECT_EQ(flagsAfter.B, flagsBefore.B);
    EXPECT_EQ(flagsAfter._, flagsBefore._);
    EXPECT_EQ(flagsAfter.V, flagsBefore.V);
}

TEST_F(CPU6502INXTests, WillINXSetNegativeFlagCorrectly)
{
    // GIVEN
    cpu.Reset();
    cpu.SetRegisterX(0x7F);
    Flags flagsBefore = cpu.GetStatusFlags();

    Memory::Write(0x8000, 0xE8); // INX

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x80);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);

    Flags flagsAfter = cpu.GetStatusFlags();
    EXPECT_EQ(flagsAfter.C, flagsBefore.C);
    EXPECT_EQ(flagsAfter.I, flagsBefore.I);
    EXPECT_EQ(flagsAfter.D, flagsBefore.D);
    EXPECT_EQ(flagsAfter.B, flagsBefore.B);
    EXPECT_EQ(flagsAfter._, flagsBefore._);
    EXPECT_EQ(flagsAfter.V, flagsBefore.V);
}
