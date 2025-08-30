#include <emulator/core/CPU6502.h>
#include <emulator/core/Memory.h>

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502STXTests : public ::testing::Test
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

TEST_F(CPU6502STXTests, WillSTXStorePositiveValueCorrectlyZeroPage)
{
    cpu.SetRegisterX(0x42);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x86); // STX Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x0010), 0x42);

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

TEST_F(CPU6502STXTests, WillSTXStoreZeroValueCorrectlyZeroPage)
{
    cpu.SetRegisterX(0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x86); // STX Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x0010), 0x00);

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

TEST_F(CPU6502STXTests, WillSTXStoreNegativeValueCorrectlyZeroPage)
{
    cpu.SetRegisterX(0xFF);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x86); // STX Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x0010), 0xFF);

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

TEST_F(CPU6502STXTests, WillSTXStorePositiveValueCorrectlyZeroPageY)
{
    cpu.SetRegisterX(0x42);
    cpu.SetRegisterY(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x96); // STX Zero Page,Y
    Memory::Write(0x8001, 0x0F);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x0010), 0x42);

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

TEST_F(CPU6502STXTests, WillSTXStoreZeroValueCorrectlyZeroPageY)
{
    cpu.SetRegisterX(0x00);
    cpu.SetRegisterY(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x96); // STX Zero Page,Y
    Memory::Write(0x8001, 0x0F);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x0010), 0x00);

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

TEST_F(CPU6502STXTests, WillSTXStoreNegativeValueCorrectlyZeroPageY)
{
    cpu.SetRegisterX(0xFF);
    cpu.SetRegisterY(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x96); // STX Zero Page,Y
    Memory::Write(0x8001, 0x0F);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x0010), 0xFF);

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

TEST_F(CPU6502STXTests, WillSTXStorePositiveValueCorrectlyAbsolute)
{
    cpu.SetRegisterX(0x42);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x8E); // STX Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x1234), 0x42);

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

TEST_F(CPU6502STXTests, WillSTXStoreZeroValueCorrectlyAbsolute)
{
    cpu.SetRegisterX(0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x8E); // STX Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x1234), 0x00);

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

TEST_F(CPU6502STXTests, WillSTXStoreNegativeValueCorrectlyAbsolute)
{
    cpu.SetRegisterX(0xFF);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x8E); // STX Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x1234), 0xFF);

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
