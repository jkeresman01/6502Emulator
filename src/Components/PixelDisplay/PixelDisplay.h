#pragma once

#include <vector>

#include "../AbstractComponent.h"

namespace emulator6502
{

using Word = uint16_t;

class PixelDisplay : public AbstractComponent
{
  public:
    PixelDisplay() = default;

    virtual void Init() noexcept override;
    virtual void Render() noexcept override;
    virtual void Destroy() noexcept override;

  private:
    static const uint32_t GRID_SIZE = 32;
    static const Word START_ADDR = 0x0200;
};
} // namespace emulator6502