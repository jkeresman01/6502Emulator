#include <emulator/core/Memory.h>
#include <gtest/gtest.h>

using namespace emulator6502;

class MemoryTests : public ::testing::Test
{
  protected:
    void SetUp() override { Memory::Init(); }

    void TearDown() override { Memory::Reset(); }
};

TEST_F(MemoryTests, WillResetMemoryToZero)
{
    // GIVEN
    Memory::Write(0x1234, 0x42);
    Memory::Write(0x5678, 0x99);

    // WHEN
    Memory::Reset();

    // THEN
    EXPECT_EQ(Memory::Read(0x1234), 0x00);
    EXPECT_EQ(Memory::Read(0x5678), 0x00);
}

TEST_F(MemoryTests, WillWriteAndReadValueCorrectly)
{
    // GIVEN
    Byte value = 0xAB;

    // WHEN
    Memory::Write(0x1000, value);

    // THEN
    EXPECT_EQ(Memory::Read(0x1000), value);
}

TEST_F(MemoryTests, WillWriteAndReadMultipleValuesCorrectly)
{
    // GIVEN
    Byte firstValue = 0x11;
    Byte secondValue = 0x22;

    // WHEN
    Memory::Write(0x00FF, firstValue);
    Memory::Write(0xFF00, secondValue);

    // THEN
    EXPECT_EQ(Memory::Read(0x00FF), firstValue);
    EXPECT_EQ(Memory::Read(0xFF00), secondValue);
}

TEST_F(MemoryTests, WillOverwriteMemoryValueCorrectly)
{
    // GIVEN
    Memory::Write(0x1234, 0x55);

    // WHEN
    Memory::Write(0x1234, 0xAA);

    // THEN
    EXPECT_EQ(Memory::Read(0x1234), 0xAA);
}
