#include "ColorsUtil.h"

namespace emulator6502
{
const ImVec4 ColorsUtil::s_Colors[] = {
    ImVec4(0, 0, 0, 1),       ImVec4(1, 1, 1, 1),          ImVec4(1, 0, 0, 1),     ImVec4(0, 1, 0, 1),
    ImVec4(0, 0, 1, 1),       ImVec4(1, 1, 0, 1),          ImVec4(1, 0, 1, 1),     ImVec4(0, 1, 1, 1),
    ImVec4(0.5, 0.5, 0.5, 1), ImVec4(0.75, 0.75, 0.75, 1), ImVec4(0.5, 0, 0, 1),   ImVec4(0, 0.5, 0, 1),
    ImVec4(0, 0, 0.5, 1),     ImVec4(0.5, 0.5, 0, 1),      ImVec4(0.5, 0, 0.5, 1), ImVec4(0, 0.5, 0.5, 1)};

ImVec4 ColorsUtil::GetPixelColor(const uint32_t index)
{
    if (index < 0 || index > COLORS_COUNT - 1)
    {
        EMULATOR_6502_ERROR(TEXT("Index out of bounds, must be in [0, %u]"), COLORS_COUNT - 1);
        return s_Colors[0];
    }

    return s_Colors[index];
}

ImVec4 ColorsUtil::GetFlagColor(const bool isSet)
{
    return isSet ? ImVec4(0.3f, 1.0f, 0.3f, 1.0f) : ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
}

} // namespace emulator6502