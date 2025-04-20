#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502ORATests : public ::testing::Test
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

TEST_F(CPU6502ORATests, WillORAWithPositiveValueImmediate)
{
    // GIVEN
    cpu.SetAccumulator(0x22);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x09); // ORA Immediate
    Memory::Write(0x8001, 0x11);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x33);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetZeroFlagCorrectlyImmediate)
{
    // GIVEN
    cpu.SetAccumulator(0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x09); // ORA Immediate
    Memory::Write(0x8001, 0x00);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetNegativeFlagCorrectlyImmediate)
{
    // GIVEN
    cpu.SetAccumulator(0x80);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x09); // ORA Immediate
    Memory::Write(0x8001, 0x01);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x81);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyZeroPage_Positive)
{
    // GIVEN
    cpu.SetAccumulator(0x22);    // 0010 0010
    Memory::Write(0x0010, 0x11); // 0001 0001

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x05); // ORA Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x33); // 0011 0011
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyZeroPage_Zero)
{
    // GIVEN
    cpu.SetAccumulator(0x00);
    Memory::Write(0x0010, 0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x05); // ORA Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyZeroPage_Negative)
{
    // GIVEN
    cpu.SetAccumulator(0x80);    // 1000 0000
    Memory::Write(0x0010, 0x01); // 0000 0001

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x05); // ORA Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x81); // 1000 0001
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyZeroPageX_Positive)
{
    // GIVEN
    cpu.SetAccumulator(0x22);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0x11);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x15); // ORA Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x33);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyZeroPageX_Zero)
{
    // GIVEN
    cpu.SetAccumulator(0x00);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x15); // ORA Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyZeroPageX_Negative)
{
    // GIVEN
    cpu.SetAccumulator(0x80);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x15); // ORA Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x81);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyAbsolute_Positive)
{
    // GIVEN
    cpu.SetAccumulator(0x22);
    Memory::Write(0x1234, 0x11);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x0D); // ORA Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x33);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyAbsolute_Zero)
{
    // GIVEN
    cpu.SetAccumulator(0x00);
    Memory::Write(0x1234, 0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x0D); // ORA Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyAbsolute_Negative)
{
    // GIVEN
    cpu.SetAccumulator(0x80);
    Memory::Write(0x1234, 0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x0D); // ORA Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x81);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyAbsoluteX_Positive)
{
    // GIVEN
    cpu.SetAccumulator(0x22);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0x11);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x1D); // ORA Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x33);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyAbsoluteX_Zero)
{
    // GIVEN
    cpu.SetAccumulator(0x00);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x1D); // ORA Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyAbsoluteX_Negative)
{
    // GIVEN
    cpu.SetAccumulator(0x80);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x1D); // ORA Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x81);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyAbsoluteY_Positive)
{
    // GIVEN
    cpu.SetAccumulator(0x22);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x1235, 0x11);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x19); // ORA Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x33);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyAbsoluteY_Zero)
{
    // GIVEN
    cpu.SetAccumulator(0x00);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x1235, 0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x19); // ORA Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyAbsoluteY_Negative)
{
    // GIVEN
    cpu.SetAccumulator(0x80);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x1235, 0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x19); // ORA Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x81);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyIndirectX_Positive)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetRegisterX(0x04);
    Memory::Write(0x0009, 0x34); // Pointer at zero page: address = 0x1234
    Memory::Write(0x000A, 0x12);
    Memory::Write(0x1234, 0x22);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x01); // ORA (Indirect,X)
    Memory::Write(0x8001, 0x05);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x32);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyIndirectX_Zero)
{
    // GIVEN
    cpu.SetAccumulator(0x00);
    cpu.SetRegisterX(0x04);
    Memory::Write(0x0009, 0x34);
    Memory::Write(0x000A, 0x12);
    Memory::Write(0x1234, 0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x01); // ORA (Indirect,X)
    Memory::Write(0x8001, 0x05);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}


TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyIndirectX_Negative)
{
    // GIVEN
    cpu.SetAccumulator(0x80);
    cpu.SetRegisterX(0x04);
    Memory::Write(0x0009, 0x34);
    Memory::Write(0x000A, 0x12);
    Memory::Write(0x1234, 0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x01); // ORA (Indirect,X)
    Memory::Write(0x8001, 0x05);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x81);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyIndirectY_Positive)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x0005, 0x34); // Base address: 0x1234
    Memory::Write(0x0006, 0x12);
    Memory::Write(0x1235, 0x22); // Final effective address = 0x1234 + Y = 0x1235

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x11); // ORA (Indirect),Y
    Memory::Write(0x8001, 0x05);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x32);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyIndirectY_Zero)
{
    // GIVEN
    cpu.SetAccumulator(0x00);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x0020, 0x34);
    Memory::Write(0x0021, 0x12);
    Memory::Write(0x1235, 0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x11); // ORA (Indirect),Y
    Memory::Write(0x8001, 0x20);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502ORATests, WillORASetAccumulatorCorrectlyIndirectY_Negative)
{
    // GIVEN
    cpu.SetAccumulator(0x80);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x0020, 0x34);
    Memory::Write(0x0021, 0x12);
    Memory::Write(0x1235, 0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x11); // ORA (Indirect),Y
    Memory::Write(0x8001, 0x20);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x81);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);

    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().V;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}
