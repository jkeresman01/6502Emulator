#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502DEYTests : public ::testing::Test
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

TEST_F(CPU6502DEYTests, WillDEYDecrementYCorrectly)
{
    cpu.SetRegisterY(0x43);
    Memory::Write(0x8000, 0x88); // DEY

    cpu.Step();

    EXPECT_EQ(cpu.GetRegisterY(), 0x42);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502DEYTests, WillDEYSetZeroFlag)
{
    cpu.SetRegisterY(0x01);
    Memory::Write(0x8000, 0x88); // DEY

    cpu.Step();

    EXPECT_EQ(cpu.GetRegisterY(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
}

TEST_F(CPU6502DEYTests, WillDEYSetNegativeFlag)
{
    cpu.SetRegisterY(0x00);
    Memory::Write(0x8000, 0x88); // DEY

    cpu.Step();

    EXPECT_EQ(cpu.GetRegisterY(), 0xFF);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
}
