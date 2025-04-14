#pragma once

#include "../AbstractComponent.h"

#include <cstdint>

#include "imgui.h"

namespace emulator6502
{
using Byte = uint8_t;
using Word = uint16_t;

class HEXDisplay : public AbstractComponent
{
  public:
    virtual void Init() noexcept override;
    virtual void Render() noexcept override;
    virtual void Destroy() noexcept override;

  private:
    void DrawSevenSegmentDigit(ImDrawList *drawList, const ImVec2 &pos, const float size,
                               const uint8_t value);

  private:
    static const uint8_t NUM_DIGITS = 4;
    static const Word BASE_ADDR = 0x0602;
};
} // namespace emulator6502