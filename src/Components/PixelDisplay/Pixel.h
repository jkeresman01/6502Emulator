#pragma once

#include "../AbstractComponent.h"

#include "imgui.h"

namespace emulator6502
{
class Pixel : public AbstractComponent
{
  public:
    virtual void Init() noexcept override;
    virtual void Render() noexcept override;
    virtual void Destroy() noexcept override;

    ImVec4 GetColor() const { return m_Color; }

    void SetColor(const ImVec4 &color) { m_Color = color; }

  private:
    ImVec4 m_Color = ImVec4(0, 0, 0, 1);

    static constexpr float PIXEL_SIZE = 6.0f;
};
} // namespace emulator6502