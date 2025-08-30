#include <emulator/core/CPU6502.h>
#include <emulator/core/Memory.h>

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502LDXTests : public ::testing::Test
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

TEST_F(CPU6502LDXTests, WillLDXLoadPositiveValueCorrectlyImmediate)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0xA2); // LDX Immediate
    Memory::Write(0x8001, 0x42);

    cpu.Reset();

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x42);
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

TEST_F(CPU6502LDXTests, WillLDXLoadZeroValueCorrectlyImmediate)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0xA2); // LDX Immediate
    Memory::Write(0x8001, 0x00);

    cpu.Reset();

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x00);
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

TEST_F(CPU6502LDXTests, WillLDXLoadNegativeValueCorrectlyImmediate)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0xA2); // LDX Immediate
    Memory::Write(0x8001, 0xFF);

    cpu.Reset();

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0xFF);
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

TEST_F(CPU6502LDXTests, WillLDXLoadPositiveValueCorrectlyZeroPage)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x0010, 0x42);
    Memory::Write(0x8000, 0xA6); // LDX Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Reset();

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x42);
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

TEST_F(CPU6502LDXTests, WillLDXLoadZeroValueCorrectlyZeroPage)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x0010, 0x00);
    Memory::Write(0x8000, 0xA6); // LDX Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Reset();

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x00);
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

TEST_F(CPU6502LDXTests, WillLDXLoadNegativeValueCorrectlyZeroPage)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x0010, 0xFF);
    Memory::Write(0x8000, 0xA6); // LDX Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Reset();

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0xFF);
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

TEST_F(CPU6502LDXTests, WillLDXLoadPositiveValueCorrectlyZeroPageY)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();

    cpu.SetRegisterY(0x01);

    Memory::Write(0x0002, 0x42);
    Memory::Write(0x8000, 0xB6); // LDX Zero Page, Y
    Memory::Write(0x8001, 0x01);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x42);
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

TEST_F(CPU6502LDXTests, WillLDXLoadZeroValueCorrectlyZeroPageY)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();

    cpu.SetRegisterY(0x01);

    Memory::Write(0x0010, 0x00);
    Memory::Write(0x8000, 0xB6); // LDX Zero Page, Y
    Memory::Write(0x8001, 0x09);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x00);
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

TEST_F(CPU6502LDXTests, WillLDXLoadNegativeValueCorrectlyZeroPageY)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();

    cpu.SetRegisterY(0x01);

    Memory::Write(0x0001, 0xFF);
    Memory::Write(0x8000, 0xB6); // LDX Zero Page, Y
    Memory::Write(0x8001, 0x00);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0xFF);
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

TEST_F(CPU6502LDXTests, WillLDXLoadPositiveValueAbsolute)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();

    cpu.SetRegisterY(0x01);

    Memory::Write(0x1234, 0x42);
    Memory::Write(0x8000, 0xAE); // LDX Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x42);
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

TEST_F(CPU6502LDXTests, WillLDXLoadZeroValueCorrectlyAbsolute)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();

    Memory::Write(0x1234, 0x00);
    Memory::Write(0x8000, 0xAE); // LDX Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x00);
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

TEST_F(CPU6502LDXTests, WillLDXLoadNegativeValueCorrectlyAbsolute)
{
    // GIVEN
    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    cpu.Reset();

    Memory::Write(0x1234, 0xFF);
    Memory::Write(0x8000, 0xAE); // LDX Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0xFF);
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

TEST_F(CPU6502LDXTests, WillLDXLoadPositiveValueCorrectlyAbsoluteY)
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
    Memory::Write(0x8000, 0xBE); // LDX Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x42);
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

TEST_F(CPU6502LDXTests, WillLDXLoadZeroValueCorrectlyAbsoluteY)
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
    Memory::Write(0x8000, 0xBE); // LDX Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0x00);
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

TEST_F(CPU6502LDXTests, WillLDXLoadNegativeValueCorrectlyAbsoluteY)
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
    Memory::Write(0x8000, 0xBE); // LDX Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetRegisterX(), 0xFF);
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
