#pragma once

#include <cstdint>

#include <emulator/components/AbstractComponent.h>

namespace emulator6502
{
class SwitchPanel : public AbstractComponent
{
  public:
    virtual void Init() override;
    virtual void Render() override;
    virtual void Destroy() override;

  private:
    static constexpr int SWITCHES_COUNT = 9;
};
} // namespace emulator6502
