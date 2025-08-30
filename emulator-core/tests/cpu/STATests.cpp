#include <emulator/core/CPU6502.h>
#include <emulator/core/Memory.h>

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502STATests : public ::testing::Test
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

TEST_F(CPU6502STATests, WillSTAStorePositiveValueCorrectlyZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0x42);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x85); // STA Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0x42);

    // Status flags not changed
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

TEST_F(CPU6502STATests, WillSTAStoreZeroValueCorrectlyZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x85); // STA Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0x00);

    // Status flags not changed
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

TEST_F(CPU6502STATests, WillSTAStoreNegativeValueCorrectlyZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x85); // STA Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0xFF);

    // Status flags not changed
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

TEST_F(CPU6502STATests, WillSTAStorePositiveValueCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0x42);
    cpu.SetRegisterX(0x10);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x95); // STA Zero Page,X
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0020), 0x42);

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

TEST_F(CPU6502STATests, WillSTAStoreZeroValueCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0x00);
    cpu.SetRegisterX(0x10);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x95); // STA Zero Page,X
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0020), 0x00);

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

TEST_F(CPU6502STATests, WillSTAStoreNegativeValueCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);
    cpu.SetRegisterX(0x10);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x95); // STA Zero Page,X
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0020), 0xFF);

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

TEST_F(CPU6502STATests, WillSTAStorePositiveValueCorrectlyAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0x42);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x8D); // STA Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
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

TEST_F(CPU6502STATests, WillSTAStoreZeroValueCorrectlyAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0x00);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x8D); // STA Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
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

TEST_F(CPU6502STATests, WillSTAStoreNegativeValueCorrectlyAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x8D); // STA Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
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

TEST_F(CPU6502STATests, WillSTAStorePositiveValueCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0x42);
    cpu.SetRegisterX(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x9D); // STA Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0x42);

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

TEST_F(CPU6502STATests, WillSTAStoreZeroValueCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0x00);
    cpu.SetRegisterX(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x9D); // STA Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0x00);

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

TEST_F(CPU6502STATests, WillSTAStoreNegativeValueCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);
    cpu.SetRegisterX(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // WHEN
    Memory::Write(0x8000, 0x9D); // STA Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0xFF);

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
TEST_F(CPU6502STATests, WillSTAStorePositiveValueCorrectlyAbsoluteY)
{
    cpu.SetAccumulator(0x42);
    cpu.SetRegisterY(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x99); // STA Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x1235), 0x42);

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

TEST_F(CPU6502STATests, WillSTAStoreZeroValueCorrectlyAbsoluteY)
{
    cpu.SetAccumulator(0x00);
    cpu.SetRegisterY(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x99); // STA Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x1235), 0x00);

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

TEST_F(CPU6502STATests, WillSTAStoreNegativeValueCorrectlyAbsoluteY)
{
    cpu.SetAccumulator(0xFF);
    cpu.SetRegisterY(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x8000, 0x99); // STA Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x1235), 0xFF);

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

TEST_F(CPU6502STATests, WillSTAStorePositiveValueCorrectlyIndirectX)
{
    cpu.SetAccumulator(0x42);
    cpu.SetRegisterX(0x04);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    // Address pointer (0x0004 + X = 0x0008), points to 0x1234
    Memory::Write(0x0008, 0x34);
    Memory::Write(0x0009, 0x12);

    Memory::Write(0x8000, 0x81); // STA (Indirect,X)
    Memory::Write(0x8001, 0x04);

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

TEST_F(CPU6502STATests, WillSTAStoreZeroValueCorrectlyIndirectX)
{
    cpu.SetAccumulator(0x00);
    cpu.SetRegisterX(0x04);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x0008, 0x34);
    Memory::Write(0x0009, 0x12);

    Memory::Write(0x8000, 0x81); // STA (Indirect,X)
    Memory::Write(0x8001, 0x04);

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

TEST_F(CPU6502STATests, WillSTAStoreNegativeValueCorrectlyIndirectX)
{
    cpu.SetAccumulator(0xFF);
    cpu.SetRegisterX(0x04);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x0008, 0x34);
    Memory::Write(0x0009, 0x12);

    Memory::Write(0x8000, 0x81); // STA (Indirect,X)
    Memory::Write(0x8001, 0x04);

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

TEST_F(CPU6502STATests, WillSTAStorePositiveValueCorrectlyIndirectY)
{
    cpu.SetAccumulator(0x42);
    cpu.SetRegisterY(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x0004, 0x33); // Pointer at zero page
    Memory::Write(0x0005, 0x12); // Pointer high byte

    Memory::Write(0x8000, 0x91); // STA (Indirect),Y
    Memory::Write(0x8001, 0x04);

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

TEST_F(CPU6502STATests, WillSTAStoreZeroValueCorrectlyIndirectY)
{
    cpu.SetAccumulator(0x00);
    cpu.SetRegisterY(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x0004, 0x33);
    Memory::Write(0x0005, 0x12);

    Memory::Write(0x8000, 0x91); // STA (Indirect),Y
    Memory::Write(0x8001, 0x04);

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

TEST_F(CPU6502STATests, WillSTAStoreNegativeValueCorrectlyIndirectY)
{
    cpu.SetAccumulator(0xFF);
    cpu.SetRegisterY(0x01);

    Byte carryBefore = cpu.GetStatusFlags().C;
    Byte interruptBefore = cpu.GetStatusFlags().I;
    Byte decimalBefore = cpu.GetStatusFlags().D;
    Byte overflowBefore = cpu.GetStatusFlags().V;
    Byte notUsedFlagBefore = cpu.GetStatusFlags()._;

    Memory::Write(0x0004, 0x33);
    Memory::Write(0x0005, 0x12);

    Memory::Write(0x8000, 0x91); // STA (Indirect),Y
    Memory::Write(0x8001, 0x04);

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
