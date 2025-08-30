#include "../src/Util/ColorsUtil.h"
#include <gtest/gtest.h>

using namespace emulator6502;

class ColorsUtilTests : public ::testing::Test
{
  protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(ColorsUtilTests, WillReturnCorrectPixelColorForValidIndex)
{
    // GIVEN
    uint32_t index = 2; // Red color (ImVec4(1, 0, 0, 1))

    // WHEN
    ImVec4 color = ColorsUtil::GetPixelColor(index);

    // THEN
    EXPECT_FLOAT_EQ(color.x, 1.0f);
    EXPECT_FLOAT_EQ(color.y, 0.0f);
    EXPECT_FLOAT_EQ(color.z, 0.0f);
    EXPECT_FLOAT_EQ(color.w, 1.0f);
}

TEST_F(ColorsUtilTests, WillReturnDefaultColorForInvalidIndex)
{
    // GIVEN
    uint32_t invalidIndex = 9999;

    // WHEN
    ImVec4 color = ColorsUtil::GetPixelColor(invalidIndex);

    // THEN
    EXPECT_FLOAT_EQ(color.x, 0.0f);
    EXPECT_FLOAT_EQ(color.y, 0.0f);
    EXPECT_FLOAT_EQ(color.z, 0.0f);
    EXPECT_FLOAT_EQ(color.w, 1.0f);
}

TEST_F(ColorsUtilTests, WillReturnCorrectFlagColorWhenSet)
{
    // GIVEN
    bool flag = true;

    // WHEN
    ImVec4 color = ColorsUtil::GetFlagColor(flag);

    // THEN
    EXPECT_FLOAT_EQ(color.x, 0.3f);
    EXPECT_FLOAT_EQ(color.y, 1.0f);
    EXPECT_FLOAT_EQ(color.z, 0.3f);
    EXPECT_FLOAT_EQ(color.w, 1.0f);
}

TEST_F(ColorsUtilTests, WillReturnCorrectFlagColorWhenNotSet)
{
    // GIVEN
    bool flag = false;

    // WHEN
    ImVec4 color = ColorsUtil::GetFlagColor(flag);

    // THEN
    EXPECT_FLOAT_EQ(color.x, 0.5f);
    EXPECT_FLOAT_EQ(color.y, 0.5f);
    EXPECT_FLOAT_EQ(color.z, 0.5f);
    EXPECT_FLOAT_EQ(color.w, 1.0f);
}
