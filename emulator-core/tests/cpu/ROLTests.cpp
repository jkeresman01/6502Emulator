#include <emulator/core/CPU6502.h>
#include <emulator/core/Memory.h>

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502ROLTests : public ::testing::Test
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

TEST_F(CPU6502ROLTests, WillROLRotateLeftCorrectlyAccumulator)
{
    // GIVEN
    cpu.SetAccumulator(0b01000000);
    cpu.SetFlags(Flags{1, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x8000, 0x2A); // ROL Accumulator

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0b10000001);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
}

TEST_F(CPU6502ROLTests, WillROLSetZeroCorrectlyAccumulator)
{
    // GIVEN
    cpu.SetAccumulator(0x80);
    cpu.SetFlags(Flags{0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x8000, 0x2A); // ROL Accumulator

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 1);
    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
}

TEST_F(CPU6502ROLTests, WillROLRotateLeftCorrectlyZeroPage)
{
    // GIVEN
    Memory::Write(0x0010, 0b01000000);
    cpu.SetFlags(Flags{1, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x8000, 0x26); // ROL Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0b10000001);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
}

TEST_F(CPU6502ROLTests, WillROLRotateLeftCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0b01001011);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x36); // ROL Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0011), 0b10010110);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502ROLTests, WillROLSetCarryCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0b10000000);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x36); // ROL Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0011), 0x00);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 1);
    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
}

TEST_F(CPU6502ROLTests, WillROLSetNegativeCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0b01000000);
    cpu.SetFlags({1, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x36); // ROL Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0011), 0b10000001);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
}

TEST_F(CPU6502ROLTests, WillROLShiftLeftCorrectlyAbsolute)
{
    // GIVEN
    Memory::Write(0x1234, 0b01010101);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x2E); // ROL Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1234), 0b10101010);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502ROLTests, WillROLSetCarryCorrectlyAbsolute)
{
    // GIVEN
    Memory::Write(0x1234, 0b10000001);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x2E); // ROL Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1234), 0b00000010);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
}

TEST_F(CPU6502ROLTests, WillROLSetNegativeCorrectlyAbsolute)
{
    // GIVEN
    Memory::Write(0x1234, 0b01000000);
    cpu.SetFlags({1, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x2E); // ROL Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1234), 0b10000001);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
}

TEST_F(CPU6502ROLTests, WillROLShiftLeftCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0b01010101);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x3E); // ROL Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0b10101010);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
}

TEST_F(CPU6502ROLTests, WillROLSetCarryCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0b10000001);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x3E); // ROL Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0b00000010);
    EXPECT_EQ(cpu.GetStatusFlags().C, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().N, 0);
}

TEST_F(CPU6502ROLTests, WillROLSetNegativeCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0b01000000);
    cpu.SetFlags({1, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x3E); // ROL Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0b10000001);
    EXPECT_EQ(cpu.GetStatusFlags().N, 1);
    EXPECT_EQ(cpu.GetStatusFlags().Z, 0);
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
}
