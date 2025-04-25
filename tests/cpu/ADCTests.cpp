#include "../src/Core/CPU6502.h"
#include "../src/Core/Memory.h"
#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502ADCTests : public ::testing::Test
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

TEST_F(CPU6502ADCTests, WillADCAddCorrectlyWithoutCarryOrOverflow)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0}); // Clear Carry

    Memory::Write(0x8000, 0x69); // ADC Immediate
    Memory::Write(0x8001, 0x05);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x15);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetCarryFlagOnOverflow)
{
    // GIVEN
    cpu.SetAccumulator(0xF0);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x69); // ADC Immediate
    Memory::Write(0x8001, 0x20);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x10);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetZeroFlagWhenResultIsZero)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);
    cpu.SetFlags({1, 0, 0, 0, 0, 0, 0, 0}); // Set Carry

    Memory::Write(0x8000, 0x69); // ADC Immediate
    Memory::Write(0x8001, 0x00);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetNegativeFlagCorrectly)
{
    // GIVEN
    cpu.SetAccumulator(0x40);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});

    Memory::Write(0x8000, 0x69); // ADC Immediate
    Memory::Write(0x8001, 0x40);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x80);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_TRUE(cpu.GetStatusFlags().V);
}
