#include "../src/Core/Memory.h"
#include "../src/Util/ProgramUtil.h"
#include <gtest/gtest.h>

using namespace emulator6502;

class ProgramUtilTests : public ::testing::Test
{
  protected:
    void SetUp() override { Memory::Init(); }

    void TearDown() override { Memory::Reset(); }
};

TEST_F(ProgramUtilTests, WillLoadProgramIntoMemoryCorrectly)
{
    // GIVEN
    std::vector<Byte> machineCode = {0xA9, 0x01, 0x8D, 0x00, 0x02}; // Example: LDA #$01, STA $0200

    // WHEN
    ProgramUtil::LoadProgramIntoMemory(machineCode);

    // THEN
    for (size_t i = 0; i < machineCode.size(); ++i)
    {
        EXPECT_EQ(Memory::Read(0x8000 + i), machineCode[i]);
    }
}

TEST_F(ProgramUtilTests, WillReadProgramFromMemoryCorrectly)
{
    // GIVEN
    std::vector<Byte> machineCode = {0xA2, 0xFF, 0x9A}; // Example: LDX #$FF, TXS
    ProgramUtil::LoadProgramIntoMemory(machineCode);

    // WHEN
    std::vector<Byte> result = ProgramUtil::ReadProgramFromMemory();

    // THEN
    ASSERT_EQ(result.size(), machineCode.size());
    for (size_t i = 0; i < machineCode.size(); ++i)
    {
        EXPECT_EQ(result[i], machineCode[i]);
    }
}

TEST_F(ProgramUtilTests, WillStopReadingWhenThreeConsecutiveZeros)
{
    // GIVEN
    std::vector<Byte> machineCode = {0xA9, 0x01, 0x00, 0x00, 0x00, 0xA2, 0x05};
    ProgramUtil::LoadProgramIntoMemory(machineCode);

    // WHEN
    std::vector<Byte> result = ProgramUtil::ReadProgramFromMemory();

    // THEN
    std::vector<Byte> expected = {0xA9, 0x01};

    ASSERT_EQ(result.size(), expected.size());

    for (size_t i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(result[i], expected[i]);
    }
}
