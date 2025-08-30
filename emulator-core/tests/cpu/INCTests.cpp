#include <emulator/core/CPU6502.h>
#include <emulator/core/Memory.h>

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502INCTests : public ::testing::Test
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

TEST_F(CPU6502INCTests, WillINCIncrementValueCorrectlyZeroPage)
{
    // GIVEN
    Memory::Write(0x0010, 0x42);
    Memory::Write(0x8000, 0xE6); // INC ZeroPage
    Memory::Write(0x8001, 0x10);

    cpu.Reset();

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0x43);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502INCTests, WillINCSetZeroFlagWhenWrappingZeroPage)
{
    // GIVEN
    Memory::Write(0x0010, 0xFF);
    Memory::Write(0x8000, 0xE6); // INC ZeroPage
    Memory::Write(0x8001, 0x10);

    cpu.Reset();

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0010), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502INCTests, WillINCSetNegativeFlagZeroPageX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);

    Memory::Write(0x0011, 0x7F);
    Memory::Write(0x8000, 0xF6); // INC ZeroPage,X
    Memory::Write(0x8001, 0x10);

    Memory::Write(0xFFFC, 0x00);
    Memory::Write(0xFFFD, 0x80);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x0011), 0x80);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502INCTests, WillINCIncrementValueCorrectlyAbsolute)
{
    // GIVEN
    Memory::Write(0x1234, 0x10);
    Memory::Write(0x8000, 0xEE); // INC Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1234), 0x11);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502INCTests, WillINCWrapAroundAbsoluteX)
{
    // GIVEN
    cpu.SetRegisterX(0x01);

    Memory::Write(0x1235, 0xFF);
    Memory::Write(0x8000, 0xFE); // INC Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(Memory::Read(0x1235), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}