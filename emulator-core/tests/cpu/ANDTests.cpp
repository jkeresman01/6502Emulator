#include <emulator/core/CPU6502.h>
#include <emulator/core/Memory.h>

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502ANDTests : public ::testing::Test
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

TEST_F(CPU6502ANDTests, WillANDAffectAccumulatorCorrectlyImmediate)
{
    // GIVEN
    cpu.SetAccumulator(0b11001100);
    Memory::Write(0x8000, 0x29); // AND Immediate
    Memory::Write(0x8001, 0b10101010);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b10001000);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502ANDTests, WillANDAffectAccumulatorCorrectlyZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0b11110000);
    Memory::Write(0x0010, 0b00001111);
    Memory::Write(0x8000, 0x25); // AND Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b00000000);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 1);
    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
}

TEST_F(CPU6502ANDTests, WillANDAffectAccumulatorCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0b10101010);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0b11110000);
    Memory::Write(0x8000, 0x35); // AND Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b10100000);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502ANDTests, WillANDAffectAccumulatorCorrectlyAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0b11110000);
    Memory::Write(0x1234, 0b11000011);
    Memory::Write(0x8000, 0x2D); // AND Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b11000000);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502ANDTests, WillANDAffectAccumulatorCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0b11111111);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0b00001111);
    Memory::Write(0x8000, 0x3D); // AND Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b00001111);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
}

TEST_F(CPU6502ANDTests, WillANDAffectAccumulatorCorrectlyAbsoluteY)
{
    // GIVEN
    cpu.SetAccumulator(0b11110000);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x1235, 0b11111111);
    Memory::Write(0x8000, 0x39); // AND Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b11110000);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502ANDTests, WillANDAffectAccumulatorCorrectlyIndirectX)
{
    // GIVEN
    cpu.SetAccumulator(0b11110000);
    cpu.SetRegisterX(0x04);
    Memory::Write(0x0014, 0x34);
    Memory::Write(0x0015, 0x12);
    Memory::Write(0x1234, 0b11001100);
    Memory::Write(0x8000, 0x21); // AND (Indirect,X)
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b11000000);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502ANDTests, WillANDAffectAccumulatorCorrectlyIndirectY)
{
    // GIVEN
    cpu.SetAccumulator(0b11110000);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x0010, 0x33);
    Memory::Write(0x0011, 0x12);
    Memory::Write(0x1234, 0b10101010);
    Memory::Write(0x8000, 0x31); // AND (Indirect),Y
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b10100000);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}
