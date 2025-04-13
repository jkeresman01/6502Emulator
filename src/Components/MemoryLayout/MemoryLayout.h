#pragma once

#include <vector>

#include "../AbstractComponent.h"

namespace emulator6502
{
using Byte = uint8_t;

class MemoryLayout : public AbstractComponent
{
  public:
    MemoryLayout() = default;

    virtual void Init() noexcept override;
    virtual void Render() noexcept override;
    virtual void Destroy() noexcept override;
};
} // namespace emulator6502