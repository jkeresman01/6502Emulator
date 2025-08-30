#include <emulator/core/CPU6502.h>
#include <emulator/core/Memory.h>

#include <gtest/gtest.h>

using namespace emulator6502;

class CPU6502CLCTests : public ::testing::Test
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

TEST_F(CPU6502CLCTests, WillClearCarryFlagCorrectly)
{
    // GIVEN
    cpu.SetFlags({1, 0, 0, 0, 0, 0, 0, 0});

    // WHEN
    Memory::Write(0x8000, 0x18); // CLC
    cpu.Step();

    // THEN
    EXPECT_EQ(cpu.GetStatusFlags().C, 0);
}
