#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502CPYTests : public ::testing::Test
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

TEST_F(CPU6502CPYTests, WillCPYCompareEqualImmediate)
{
    // GIVEN
    cpu.SetRegisterY(0x42);

    Memory::Write(0x8000, 0xC0); // CPY #$42
    Memory::Write(0x8001, 0x42);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CPYTests, WillCPYCompareGreaterImmediate)
{
    // GIVEN
    cpu.SetRegisterY(0x50);

    Memory::Write(0x8000, 0xC0); // CPY #$20
    Memory::Write(0x8001, 0x20);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CPYTests, WillCPYCompareLessImmediate)
{
    // GIVEN
    cpu.SetRegisterY(0x20);

    Memory::Write(0x8000, 0xC0); // CPY #$50
    Memory::Write(0x8001, 0x50);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CPYTests, WillCPYCompareEqualZeroPage)
{
    // GIVEN
    cpu.SetRegisterY(0x42);
    Memory::Write(0x0010, 0x42);

    Memory::Write(0x8000, 0xC4); // CPY $10
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502CPYTests, WillCPYCompareLessAbsolute)
{
    // GIVEN
    cpu.SetRegisterY(0x10);
    Memory::Write(0x1234, 0x20);

    Memory::Write(0x8000, 0xCC); // CPY $1234
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}
