#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502DECTests : public ::testing::Test
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

TEST_F(CPU6502DECTests, WillDECDecrementValueCorrectlyZeroPage)
{
    // GIVEN
    Memory::Write(0x0010, 0x43);
    Memory::Write(0x8000, 0xC6); // DEC ZeroPage
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0x42);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502DECTests, WillDECSetZeroFlagZeroPage)
{
    // GIVEN
    Memory::Write(0x0010, 0x01);
    Memory::Write(0x8000, 0xC6); // DEC ZeroPage
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502DECTests, WillDECSetNegativeFlagZeroPageX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);

    Memory::Write(0x0011, 0x00);
    Memory::Write(0x8000, 0xD6); // DEC ZeroPage,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0011), 0xFF);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502DECTests, WillDECDecrementValueCorrectlyAbsolute)
{
    // GIVEN
    Memory::Write(0x1234, 0x22);
    Memory::Write(0x8000, 0xCE); // DEC Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1234), 0x21);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502DECTests, WillDECWrapAroundAbsoluteX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);

    Memory::Write(0x1235, 0x00);
    Memory::Write(0x8000, 0xDE); // DEC Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0xFF);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}
