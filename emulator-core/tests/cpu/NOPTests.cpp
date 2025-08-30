#include <emulator/core/CPU6502.h>
#include <emulator/core/Memory.h>

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502NOPTests : public ::testing::Test
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

TEST_F(CPU6502NOPTests, WillNOPNotAffectAnyFlagsWhenAllSet)
{
    // GIVEN
    Memory::Write(0x8000, 0xEA); // NOP

    Flags flagsBefore{};
    flagsBefore.C = 1;
    flagsBefore.Z = 1;
    flagsBefore.I = 1;
    flagsBefore.D = 1;
    flagsBefore.B = 1;
    flagsBefore._ = 1;
    flagsBefore.V = 1;
    flagsBefore.N = 1;

    cpu.Reset();
    cpu.SetFlags(flagsBefore);

    // WHEN
    cpu.Step();

    // THEN
    Flags flagsAfter = cpu.GetStatusFlags();

    EXPECT_EQ(flagsAfter.C, flagsBefore.C);
    EXPECT_EQ(flagsAfter.Z, flagsBefore.Z);
    EXPECT_EQ(flagsAfter.I, flagsBefore.I);
    EXPECT_EQ(flagsAfter.D, flagsBefore.D);
    EXPECT_EQ(flagsAfter.B, flagsBefore.B);
    EXPECT_EQ(flagsAfter._, flagsBefore._);
    EXPECT_EQ(flagsAfter.V, flagsBefore.V);
    EXPECT_EQ(flagsAfter.N, flagsBefore.N);
}

TEST_F(CPU6502NOPTests, WillNOPNotAffectAnyFlagsWhenAllCleared)
{
    // GIVEN
    Memory::Write(0x8000, 0xEA); // NOP

    Flags flagsBefore{};

    cpu.Reset();
    cpu.SetFlags(flagsBefore);

    // WHEN
    cpu.Step();

    // THEN
    Flags flagsAfter = cpu.GetStatusFlags();

    EXPECT_EQ(flagsAfter.C, flagsBefore.C);
    EXPECT_EQ(flagsAfter.Z, flagsBefore.Z);
    EXPECT_EQ(flagsAfter.I, flagsBefore.I);
    EXPECT_EQ(flagsAfter.D, flagsBefore.D);
    EXPECT_EQ(flagsAfter.B, flagsBefore.B);
    EXPECT_EQ(flagsAfter._, flagsBefore._);
    EXPECT_EQ(flagsAfter.V, flagsBefore.V);
    EXPECT_EQ(flagsAfter.N, flagsBefore.N);
}
