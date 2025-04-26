#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "../Common/Logger.h"

#include "imgui.h"

namespace emulator6502
{
class ColorsUtil
{
  public:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Deleted default constructor to prevent instantiation.
    ///        Utility class.
    ///
    //////////////////////////////////////////////////////////////
    ColorsUtil() = delete;

    static ImVec4 GetPixelColor(const uint32_t index);
    static ImVec4 GetFlagColor(const bool isSet);

  private:
    static constexpr uint32_t COLORS_COUNT = 16;
    static const ImVec4 s_Colors[COLORS_COUNT];
};
} // namespace emulator6502