#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502LDATests : public ::testing::Test
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

TEST_F(CPU6502LDATests, WillLDALoadPositiveValueCorrectlyImmediate)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().C;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0xA9);
    Memory::Write(0x8001, 0x42);

    cpu.Reset();
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x42);

    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);

    // Status flags not changed
    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().C;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502LDATests, WillLDALoadZeroValueCorrectlyImmediate)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().C;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0xA9);
    Memory::Write(0x8001, 0x00);

    cpu.Reset();
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);

    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 1);

    // Status flags not changed
    Byte carryAfter = cpu.GetStatusFlags().C;
    Byte interruptAfter = cpu.GetStatusFlags().I;
    Byte decimalAfter = cpu.GetStatusFlags().D;
    Byte overflowAfter = cpu.GetStatusFlags().C;
    Byte notUsedFlagAfter = cpu.GetStatusFlags()._;

    EXPECT_EQ(carryBefore, carryAfter);
    EXPECT_EQ(interruptBefore, interruptAfter);
    EXPECT_EQ(decimalBefore, decimalAfter);
    EXPECT_EQ(overflowBefore, overflowAfter);
    EXPECT_EQ(notUsedFlagBefore, notUsedFlagAfter);
}

TEST_F(CPU6502LDATests, WillLDALoadNegativeValueCorrectlyImmediate)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0xA9);
    Memory::Write(0x8001, 0xFF);

    cpu.Reset();
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0xFF);

    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);

    // Unrelated flags should remain unchanged
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

TEST_F(CPU6502LDATests, WillLDALoadPositiveValueCorrectlyAbsoluteX)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterX(0x01);

    Memory::Write(0x1235, 0x42);
    Memory::Write(0x8000, 0xBD); // LDA Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x42);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
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

TEST_F(CPU6502LDATests, WillLDALoadZeroValueCorrectlyAbsoluteX)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterX(0x01);

    Memory::Write(0x1235, 0x00);
    Memory::Write(0x8000, 0xBD); // LDA Absolute,X
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

TEST_F(CPU6502LDATests, WillLDALoadNegativeValueCorrectlyAbsoluteX)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterX(0x01);

    Memory::Write(0x1235, 0xFF);
    Memory::Write(0x8000, 0xBD); // LDA Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0xFF);
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

TEST_F(CPU6502LDATests, WillLDALoadPositiveValueCorrectlyAbsoluteY)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterY(0x01);

    Memory::Write(0x1235, 0x42);
    Memory::Write(0x8000, 0xB9); // LDA Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x42);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
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

TEST_F(CPU6502LDATests, WillLDALoadZeroValueCorrectlyAbsoluteY)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterY(0x01);

    Memory::Write(0x1235, 0x00);
    Memory::Write(0x8000, 0xB9); // LDA Absolute,Y
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

TEST_F(CPU6502LDATests, WillLDALoadNegativeValueCorrectlyAbsoluteY)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterY(0x01);

    Memory::Write(0x1235, 0xFF);
    Memory::Write(0x8000, 0xB9); // LDA Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0xFF);
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

TEST_F(CPU6502LDATests, WillLDALoadPositiveValueCorrectlyZeroPage)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    Memory::Write(0x0042, 0x69);
    Memory::Write(0x8000, 0xA5); // LDA Zero Page
    Memory::Write(0x8001, 0x42);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x69);
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

TEST_F(CPU6502LDATests, WillLDALoadZeroValueCorrectlyZeroPage)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    Memory::Write(0x0042, 0x00);
    Memory::Write(0x8000, 0xA5); // LDA Zero Page
    Memory::Write(0x8001, 0x42);

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

TEST_F(CPU6502LDATests, WillLDALoadNegativeValueCorrectlyZeroPage)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    Memory::Write(0x0042, 0xFF);
    Memory::Write(0x8000, 0xA5); // LDA Zero Page
    Memory::Write(0x8001, 0x42);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0xFF);
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

TEST_F(CPU6502LDATests, WillLDALoadPositiveValueCorrectlyZeroPageX)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterX(0x10);

    Memory::Write(0x0052, 0x42);
    Memory::Write(0x8000, 0xB5); // LDA Zero Page,X
    Memory::Write(0x8001, 0x42);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x42);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
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

TEST_F(CPU6502LDATests, WillLDALoadZeroValueCorrectlyZeroPageX)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterX(0x10);

    Memory::Write(0x0052, 0x00);
    Memory::Write(0x8000, 0xB5); // LDA Zero Page,X
    Memory::Write(0x8001, 0x42);

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

TEST_F(CPU6502LDATests, WillLDALoadNegativeValueCorrectlyZeroPageX)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterX(0x10);

    Memory::Write(0x0052, 0xFF);
    Memory::Write(0x8000, 0xB5); // LDA Zero Page,X
    Memory::Write(0x8001, 0x42);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0xFF);
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

TEST_F(CPU6502LDATests, WillLDALoadPositiveValueCorrectlyIndirectX)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterX(0x04);

    Memory::Write(0x8000, 0xA1); // LDA (Indirect,X)
    Memory::Write(0x8001, 0x20);

    Memory::Write(0x0024, 0x00); // Low byte of target address
    Memory::Write(0x0025, 0x90); // High byte of target address

    Memory::Write(0x9000, 0x42);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x42);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
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

TEST_F(CPU6502LDATests, WillLDALoadZeroValueCorrectlyIndirectX)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterX(0x04);

    Memory::Write(0x8000, 0xA1); // LDA (Indirect,X)
    Memory::Write(0x8001, 0x20);

    Memory::Write(0x0024, 0x00);
    Memory::Write(0x0025, 0x90);

    Memory::Write(0x9000, 0x00);

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

TEST_F(CPU6502LDATests, WillLDALoadNegativeValueCorrectlyIndirectX)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterX(0x04);

    Memory::Write(0x8000, 0xA1); // LDA (Indirect,X)
    Memory::Write(0x8001, 0x20);

    Memory::Write(0x0024, 0x00);
    Memory::Write(0x0025, 0x90);

    Memory::Write(0x9000, 0xFF);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0xFF);
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

TEST_F(CPU6502LDATests, WillLDALoadPositiveValueCorrectlyIndirectY)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterY(0x03);

    Memory::Write(0x8000, 0xB1); // LDA (Indirect),Y
    Memory::Write(0x8001, 0x20);

    Memory::Write(0x0020, 0x00); // Low byte of base address
    Memory::Write(0x0021, 0x90); // High byte of base address

    Memory::Write(0x9003, 0x42); // Final address = 0x9000 + Y

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x42);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
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

TEST_F(CPU6502LDATests, WillLDALoadZeroValueCorrectlyIndirectY)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterY(0x03);

    Memory::Write(0x8000, 0xB1); // LDA (Indirect),Y
    Memory::Write(0x8001, 0x20);

    Memory::Write(0x0020, 0x00);
    Memory::Write(0x0021, 0x90);

    Memory::Write(0x9003, 0x00);

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

TEST_F(CPU6502LDATests, WillLDALoadNegativeValueCorrectlyIndirectY)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();
    cpu.SetRegisterY(0x03);

    Memory::Write(0x8000, 0xB1); // LDA (Indirect),Y
    Memory::Write(0x8001, 0x20);

    Memory::Write(0x0020, 0x00);
    Memory::Write(0x0021, 0x90);

    Memory::Write(0x9003, 0xFF);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0xFF);
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
