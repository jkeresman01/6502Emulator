#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502DEXTests : public ::testing::Test
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

TEST_F(CPU6502DEXTests, WillDEXDecrementXCorrectly)
{
    cpu.SetRegisterX(0x43);
    Memory::Write(0x8000, 0xCA); // DEX

    cpu.Step();

    EXPECT_EQ(cpu.GetRegisterX(), 0x42);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502DEXTests, WillDEXSetZeroFlag)
{
    cpu.SetRegisterX(0x01);
    Memory::Write(0x8000, 0xCA); // DEX

    cpu.Step();

    EXPECT_EQ(cpu.GetRegisterX(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502DEXTests, WillDEXSetNegativeFlag)
{
    cpu.SetRegisterX(0x00);
    Memory::Write(0x8000, 0xCA); // DEX

    cpu.Step();

    EXPECT_EQ(cpu.GetRegisterX(), 0xFF);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}
