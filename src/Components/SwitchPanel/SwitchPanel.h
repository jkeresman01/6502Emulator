#pragma once

#include "../AbstractComponent.h"

namespace emulator6502
{
class SwitchPanel : public AbstractComponent
{
  public:
    virtual void Init() override;
    virtual void Render() override;
    virtual void Destroy() override;
};
} // namespace emulator6502