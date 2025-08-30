#include <emulator/core/CPU6502.h>
#include <emulator/core/Memory.h>

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

TEST_F(CPU6502ADCTests, WillADCAddCorrectlyZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x0010, 0x05);
    Memory::Write(0x8000, 0x65); // ADC Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x15);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetCarryZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0xF0);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x0010, 0x20);
    Memory::Write(0x8000, 0x65); // ADC Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x10);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetZeroFlagZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);
    cpu.SetFlags({1, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x0010, 0x00);
    Memory::Write(0x8000, 0x65); // ADC Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetNegativeAndOverflowZeroPage)
{
    // GIVEN
    cpu.SetAccumulator(0x40);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x0010, 0x40);
    Memory::Write(0x8000, 0x65); // ADC Zero Page
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x80);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_TRUE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCAddCorrectlyZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetRegisterX(0x01);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x0011, 0x05);
    Memory::Write(0x8000, 0x75); // ADC Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x15);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetCarryZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0xF0);
    cpu.SetRegisterX(0x01);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x0011, 0x20);
    Memory::Write(0x8000, 0x75); // ADC Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x10);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetZeroFlagZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);
    cpu.SetRegisterX(0x01);
    cpu.SetFlags({1, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x0011, 0x00);
    Memory::Write(0x8000, 0x75); // ADC Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetNegativeAndOverflowZeroPageX)
{
    // GIVEN
    cpu.SetAccumulator(0x40);
    cpu.SetRegisterX(0x01);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x0011, 0x40);
    Memory::Write(0x8000, 0x75); // ADC Zero Page,X
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x80);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_TRUE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCAddCorrectlyAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1234, 0x05);
    Memory::Write(0x8000, 0x6D); // ADC Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x15);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetCarryAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0xF0);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1234, 0x20);
    Memory::Write(0x8000, 0x6D); // ADC Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x10);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetZeroFlagAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);
    cpu.SetFlags({1, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1234, 0x00);
    Memory::Write(0x8000, 0x6D); // ADC Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetNegativeAndOverflowAbsolute)
{
    // GIVEN
    cpu.SetAccumulator(0x40);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1234, 0x40);
    Memory::Write(0x8000, 0x6D); // ADC Absolute
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x80);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_TRUE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCAddCorrectlyAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetRegisterX(0x01);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1235, 0x05);
    Memory::Write(0x8000, 0x7D); // ADC Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x15);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetCarryAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0xF0);
    cpu.SetRegisterX(0x01);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1235, 0x20);
    Memory::Write(0x8000, 0x7D); // ADC Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x10);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetZeroFlagAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);
    cpu.SetRegisterX(0x01);
    cpu.SetFlags({1, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1235, 0x00);
    Memory::Write(0x8000, 0x7D); // ADC Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetNegativeAndOverflowAbsoluteX)
{
    // GIVEN
    cpu.SetAccumulator(0x40);
    cpu.SetRegisterX(0x01);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1235, 0x40);
    Memory::Write(0x8000, 0x7D); // ADC Absolute,X
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x80);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_TRUE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCAddCorrectlyAbsoluteY)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetRegisterY(0x01);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1235, 0x05);
    Memory::Write(0x8000, 0x79); // ADC Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x15);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetCarryAbsoluteY)
{
    // GIVEN
    cpu.SetAccumulator(0xF0);
    cpu.SetRegisterY(0x01);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1235, 0x20);
    Memory::Write(0x8000, 0x79); // ADC Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x10);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetZeroFlagAbsoluteY)
{
    // GIVEN
    cpu.SetAccumulator(0xFF);
    cpu.SetRegisterY(0x01);
    cpu.SetFlags({1, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1235, 0x00);
    Memory::Write(0x8000, 0x79); // ADC Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x00);
    EXPECT_TRUE(cpu.GetStatusFlags().C);
    EXPECT_TRUE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCSetNegativeAndOverflowAbsoluteY)
{
    // GIVEN
    cpu.SetAccumulator(0x40);
    cpu.SetRegisterY(0x01);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    Memory::Write(0x1235, 0x40);
    Memory::Write(0x8000, 0x79); // ADC Absolute,Y
    Memory::Write(0x8001, 0x34);
    Memory::Write(0x8002, 0x12);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x80);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_TRUE(cpu.GetStatusFlags().N);
    EXPECT_TRUE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCAddCorrectlyIndirectX)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    cpu.SetRegisterX(0x01);
    Memory::Write(0x0011, 0x00);
    Memory::Write(0x0012, 0x90);
    Memory::Write(0x9000, 0x05);
    Memory::Write(0x8000, 0x61); // ADC (Indirect,X)
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x15);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}

TEST_F(CPU6502ADCTests, WillADCAddCorrectlyIndirectY)
{
    // GIVEN
    cpu.SetAccumulator(0x10);
    cpu.SetFlags({0, 0, 0, 0, 0, 0, 0, 0});
    cpu.SetRegisterY(0x01);
    Memory::Write(0x0010, 0xFF);
    Memory::Write(0x0011, 0x12);
    Memory::Write(0x1300, 0x05);
    Memory::Write(0x8000, 0x71); // ADC (Indirect),Y
    Memory::Write(0x8001, 0x10);

    // WHEN
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetAccumulator(), 0x15);
    EXPECT_FALSE(cpu.GetStatusFlags().C);
    EXPECT_FALSE(cpu.GetStatusFlags().Z);
    EXPECT_FALSE(cpu.GetStatusFlags().N);
    EXPECT_FALSE(cpu.GetStatusFlags().V);
}
