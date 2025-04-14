#pragma once

#include "../AbstractComponent.h"

namespace emulator6502
{
class LEDs : public AbstractComponent
{
  public:
    virtual void Init() noexcept override;
    virtual void Render() noexcept override;
    virtual void Destroy() noexcept override;

  private:
    static constexpr float RADIUS = 8.0f;
    static constexpr float SPACING = 4.0f;
};
} // namespace emulator6502