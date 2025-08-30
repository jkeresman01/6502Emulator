#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502CMPTests : public ::testing::Test
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

TEST_F(CPU6502CMPTests, WillCMPCompareEqualImmediate)
{
    // GIVEN
    cpu.SetAccumulator(0x42);

    // WHEN
    Memory::Write(0x8000, 0xC9); // CMP Immediate
    Memory::Write(0x8001, 0x42);

    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareGreaterImmediate)
{
    // GIVEN
    cpu.SetAccumulator(0x50);

    // WHEN
    Memory::Write(0x8000, 0xC9); // CMP Immediate
    Memory::Write(0x8001, 0x40);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareLessImmediate)
{
    // GIVEN
    cpu.SetAccumulator(0x10);

    // WHEN
    Memory::Write(0x8000, 0xC9); // CMP Immediate
    Memory::Write(0x8001, 0x20);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareEqualZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0x42);
    Memory::Write(0x0010, 0x42);

    // WHEN
    Memory::Write(0x8000, 0xC5); // CMP Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareGreaterZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0x50);
    Memory::Write(0x0010, 0x40);

    // WHEN
    Memory::Write(0x8000, 0xC5); // CMP Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareLessZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    Memory::Write(0x0010, 0x20);

    // WHEN
    Memory::Write(0x8000, 0xC5); // CMP Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareEqualZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0x42);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0x42);

    // WHEN
    Memory::Write(0x8000, 0xD5); // CMP Zero Page,X
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareGreaterZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0x50);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0x40);

    // WHEN
    Memory::Write(0x8000, 0xD5); // CMP Zero Page,X
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareLessZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0x20);

    // WHEN
    Memory::Write(0x8000, 0xD5); // CMP Zero Page,X
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareEqualAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0x42);
    Memory::Write(0x1234, 0x42);

    // WHEN
    Memory::Write(0x8000, 0xCD); // CMP Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareGreaterAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0x50);
    Memory::Write(0x1234, 0x40);

    // WHEN
    Memory::Write(0x8000, 0xCD); // CMP Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareLessAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    Memory::Write(0x1234, 0x20);

    // WHEN
    Memory::Write(0x8000, 0xCD); // CMP Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareEqualAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0x42);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0x42);

    // WHEN
    Memory::Write(0x8000, 0xDD); // CMP Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareGreaterAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0x50);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0x40);

    // WHEN
    Memory::Write(0x8000, 0xDD); // CMP Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareLessAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0x20);

    // WHEN
    Memory::Write(0x8000, 0xDD); // CMP Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareEqualAbsoluteY)
{
    // GIVEN
    cpu.SetAccumulator(0x42);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x1235, 0x42);

    // WHEN
    Memory::Write(0x8000, 0xD9); // CMP Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareGreaterAbsoluteY)
{
    // GIVEN
    cpu.SetAccumulator(0x50);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x1235, 0x40);

    // WHEN
    Memory::Write(0x8000, 0xD9); // CMP Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareLessAbsoluteY)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x1235, 0x20);

    // WHEN
    Memory::Write(0x8000, 0xD9); // CMP Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareEqualIndirectX)
{
    // GIVEN
    cpu.SetAccumulator(0x42);
    cpu.SetRegisterX(0x04);
    Memory::Write(0x0009, 0x00);
    Memory::Write(0x000A, 0x12);
    Memory::Write(0x1200, 0x42);

    // WHEN
    Memory::Write(0x8000, 0xC1); // CMP (Indirect,X)
    Memory::Write(0x8001, 0x05);

    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareGreaterIndirectX)
{
    // GIVEN
    cpu.SetAccumulator(0x50);
    cpu.SetRegisterX(0x04);
    Memory::Write(0x0009, 0x00);
    Memory::Write(0x000A, 0x12);
    Memory::Write(0x1200, 0x40);

    // WHEN
    Memory::Write(0x8000, 0xC1); // CMP (Indirect,X)
    Memory::Write(0x8001, 0x05);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareLessIndirectX)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetRegisterX(0x04);
    Memory::Write(0x0009, 0x00);
    Memory::Write(0x000A, 0x12);
    Memory::Write(0x1200, 0x20);

    // WHEN
    Memory::Write(0x8000, 0xC1); // CMP (Indirect,X)
    Memory::Write(0x8001, 0x05);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareEqualIndirectY)
{
    // GIVEN
    cpu.SetAccumulator(0x42);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x0005, 0x00);
    Memory::Write(0x0006, 0x12);
    Memory::Write(0x1201, 0x42);

    // WHEN
    Memory::Write(0x8000, 0xD1); // CMP (Indirect),Y
    Memory::Write(0x8001, 0x05);

    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareGreaterIndirectY)
{
    // GIVEN
    cpu.SetAccumulator(0x50);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x0005, 0x00);
    Memory::Write(0x0006, 0x12);
    Memory::Write(0x1201, 0x40);

    // WHEN
    Memory::Write(0x8000, 0xD1); // CMP (Indirect),Y
    Memory::Write(0x8001, 0x05);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CMPTests, WillCMPCompareLessIndirectY)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetRegisterY(0x01);
    Memory::Write(0x0005, 0x00);
    Memory::Write(0x0006, 0x12);
    Memory::Write(0x1201, 0x20);

    // WHEN
    Memory::Write(0x8000, 0xD1); // CMP (Indirect),Y
    Memory::Write(0x8001, 0x05);

    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}
