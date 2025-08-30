#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502BITTests : public ::testing::Test
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

TEST_F(CPU6502BITTests, WillBITSetZeroFlagWhenResultIsZeroZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0x0F);
    Memory::Write(0x0010, 0xF0);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;

    // WHEN
    Memory::Write(0x8000, 0x24); // BIT Zero Page
    Memory::Write(0x8001, 0x10);
    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_TRUE(cpu.GetStatusFlags().V);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
}

TEST_F(CPU6502BITTests, WillBITSetNegativeAndOverflowZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);
    Memory::Write(0x0010, 0b11000000);

    // WHEN
    Memory::Write(0x8000, 0x24); // BIT Zero Page
    Memory::Write(0x8001, 0x10);
    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_TRUE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502BITTests, WillBITSetZeroFlagWhenResultIsZeroAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0x0F);
    Memory::Write(0x1234, 0xF0);

    // WHEN
    Memory::Write(0x8000, 0x2C); // BIT Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);
    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_TRUE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502BITTests, WillBITSetNegativeAndOverflowAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);
    Memory::Write(0x1234, 0b11000000);

    // WHEN
    Memory::Write(0x8000, 0x2C); // BIT Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);
    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_TRUE(cpu.GetStatusFlags().V);
}
