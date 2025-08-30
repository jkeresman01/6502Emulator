#include <emulator/core/CPU6502.h>
#include <emulator/core/Memory.h>

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502ASLTests : public ::testing::Test
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

TEST_F(CPU6502ASLTests, WillASLShiftLeftCorrectlyAccumulator)
{
    cpu.SetAccumulator(0b01000001);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x0A); // ASL Accumulator

    cpu.Step();

    EXPECT_EQ(cpu.GetAccumulator(), 0b10000010);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
}

TEST_F(CPU6502ASLTests, WillASLSetCarryCorrectlyAccumulator)
{
    cpu.SetAccumulator(0b10000001);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x0A); // ASL Accumulator

    cpu.Step();

    EXPECT_EQ(cpu.GetAccumulator(), 0b00000010);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
}

TEST_F(CPU6502ASLTests, WillASLSetZeroCorrectlyAccumulator)
{
    cpu.SetAccumulator(0b10000000);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x0A); // ASL Accumulator

    cpu.Step();

    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502ASLTests, WillASLShiftLeftCorrectlyZeroPage)
{
    Memory::Write(0x0010, 0b01000001);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x06); // ASL Zero Page
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x0010), 0b10000010);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
}

TEST_F(CPU6502ASLTests, WillASLShiftLeftCorrectlyZeroPageX)
{
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0b01000001);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x16); // ASL Zero Page,X
    Memory::Write(0x8001, 0x10);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x0011), 0b10000010);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
}

TEST_F(CPU6502ASLTests, WillASLShiftLeftCorrectlyAbsolute)
{
    Memory::Write(0x1234, 0b01000001);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x0E); // ASL Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x1234), 0b10000010);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
}

TEST_F(CPU6502ASLTests, WillASLShiftLeftCorrectlyAbsoluteX)
{
    cpu.SetRegisterX(0x01);
    Memory::Write(0x1235, 0b01000001);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x1E); // ASL Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    cpu.Step();

    EXPECT_EQ(Memory::Read(0x1235), 0b10000010);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
}
