#pragma once

#include <string>

#include "../AbstractComponent.h"

namespace emulator6502
{
class Editor : public AbstractComponent
{
  public:
    Editor() = default;

    virtual void Init() noexcept override;
    virtual void Render() noexcept override;
    virtual void Destroy() noexcept override;

    std::string GetText() const;
};
} // namespace emulator6502