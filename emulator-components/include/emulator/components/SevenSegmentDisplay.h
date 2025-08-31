#pragma once

#include <emulator/components/AbstractComponent.h>

#include <cstdint>

#include "imgui.h"

namespace emulator6502
{
using Byte = uint8_t;
using Word = uint16_t;

class SevenSegmentDisplay : public AbstractComponent
{
  public:
    virtual void Init() noexcept override;
    virtual void Render() noexcept override;
    virtual void Destroy() noexcept override;

  private:
    void DrawSevenSegmentDigit(ImDrawList *drawList, const ImVec2 &pos, const float size,
                               const uint8_t value);

  private:
    static constexpr uint8_t DIGITS_NO = 4;

    static const Word BASE_ADDR = 0x0602;

    static constexpr float SIZE = 60.0f;
    static constexpr float SPACING = 20.0f;
};
} // namespace emulator6502
