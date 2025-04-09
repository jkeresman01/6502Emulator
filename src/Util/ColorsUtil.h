#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "Logger.h"
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

    static ImVec4 GetColor(const uint32_t index);

  private:
    static constexpr uint32_t COLORS_COUNT = 16;
    static const ImVec4 s_Colors[COLORS_COUNT];
};
} // namespace emulator6502