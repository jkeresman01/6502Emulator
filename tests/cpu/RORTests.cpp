#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502RORTests : public ::testing::Test
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

TEST_F(CPU6502RORTests, WillRORAccumulatorCorrectlyWithoutCarry)
{
    // GIVEN
    cpu.SetAccumulator(0b00000010);
    cpu.SetFlags({0, 0, 0, 0, 0, 1, 0, 0});

    Memory::Write(0x8000, 0x6A); // ROR Accumulator

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b00000001);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
}

TEST_F(CPU6502RORTests, WillRORAccumulatorCorrectlyWithCarry)
{
    // GIVEN
    cpu.SetAccumulator(0b00000001);
    cpu.SetFlags({1, 0, 0, 0, 0, 1, 0, 0});

    Memory::Write(0x8000, 0x6A); // ROR Accumulator

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b10000000);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
}

TEST_F(CPU6502RORTests, WillSetZeroFlagIfResultIsZero)
{
    // GIVEN
    cpu.SetAccumulator(0b00000001);
    cpu.SetFlags({0, 0, 0, 0, 0, 1, 0, 0});

    Memory::Write(0x8000, 0x6A); // ROR Accumulator

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502RORTests, WillRORRotateRightCorrectlyZeroPage)
{
    // GIVEN
    Memory::Write(0x0010, 0x96);
    Flags flags = {};
    flags.C = 1;
    cpu.SetFlags(flags);

    Memory::Write(0x8000, 0x66); // ROR Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0xCB);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502RORTests, WillRORSetCarryCorrectlyZeroPage)
{
    // GIVEN
    Memory::Write(0x0010, 0x01);
    Flags flags = {};
    cpu.SetFlags(flags);

    Memory::Write(0x8000, 0x66); // ROR Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0x00);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 1);
    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
}

TEST_F(CPU6502RORTests, WillRORSetNegativeCorrectlyZeroPage)
{
    // GIVEN
    Memory::Write(0x0010, 0x01);
    Flags flags = {};
    flags.C = 1;
    cpu.SetFlags(flags);

    Memory::Write(0x8000, 0x66); // ROR Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0x80);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
}

TEST_F(CPU6502RORTests, WillRORRotateRightCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0x96);
    cpu.SetFlags(Flags{1, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x76); // ROR Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0011), 0xCB);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502RORTests, WillRORSetCarryCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0x01);
    cpu.SetFlags(Flags{0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x76);
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0011), 0x00);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 1);
    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
}

TEST_F(CPU6502RORTests, WillRORSetNegativeCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0x01);
    cpu.SetFlags(Flags{1, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x76); // ROR Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0011), 0x80);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
}

TEST_F(CPU6502RORTests, WillRORRotateRightCorrectlyAbsolute)
{
    // GIVEN
    Memory::Write(0x1234, 0x96);
    cpu.SetFlags(Flags{1, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x6E); // ROR Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1234), 0xCB);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502RORTests, WillRORSetCarryCorrectlyAbsolute)
{
    // GIVEN
    Memory::Write(0x1234, 0x01);
    cpu.SetFlags(Flags{0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x6E); // ROR Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1234), 0x00);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 1);
    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
}

TEST_F(CPU6502RORTests, WillRORSetNegativeCorrectlyAbsolute)
{
    // GIVEN
    Memory::Write(0x1234, 0x01);
    cpu.SetFlags(Flags{1, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x6E); // ROR Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1234), 0x80);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
}

TEST_F(CPU6502RORTests, WillRORRotateRightCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0x96);
    cpu.SetFlags(Flags{1, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x7E); // ROR Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0xCB);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502RORTests, WillRORSetCarryCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0x01);
    cpu.SetFlags(Flags{0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x7E); // ROR Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0x00);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 1);
    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
}

TEST_F(CPU6502RORTests, WillRORSetNegativeCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0x01);
    cpu.SetFlags(Flags{1, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x7E); // ROR Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0x80);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
}
