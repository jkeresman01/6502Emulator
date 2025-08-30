#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502CPXTests : public ::testing::Test
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

TEST_F(CPU6502CPXTests, WillCPXCompareEqualImmediate)
{
    // GIVEN
    cpu.SetRegisterX(0x42);

    Memory::Write(0x8000, 0xE0); // CPX #$42
    Memory::Write(0x8001, 0x42);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CPXTests, WillCPXCompareGreaterImmediate)
{
    // GIVEN
    cpu.SetRegisterX(0x50);

    Memory::Write(0x8000, 0xE0); // CPX #$20
    Memory::Write(0x8001, 0x20);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CPXTests, WillCPXCompareLessImmediate)
{
    // GIVEN
    cpu.SetRegisterX(0x10);

    Memory::Write(0x8000, 0xE0); // CPX #$20
    Memory::Write(0x8001, 0x20);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CPXTests, WillCPXCompareEqualZeroPage)
{
    // GIVEN
    cpu.SetRegisterX(0x42);
    Memory::Write(0x0010, 0x42);

    Memory::Write(0x8000, 0xE4); // CPX $10
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CPXTests, WillCPXCompareLessAbsolute)
{
    // GIVEN
    cpu.SetRegisterX(0x10);
    Memory::Write(0x1234, 0x20);

    Memory::Write(0x8000, 0xEC); // CPX $1234
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}
