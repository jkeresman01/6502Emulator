#pragma once

#include <cstdint>
#include <vector>

#include "../Core/Memory.h"

namespace emulator6502
{
using Byte = uint8_t;

class SoftwareLoader
{
  public:
    SoftwareLoader() = delete;

    static void Load(const std::vector<Byte> &machineCode);
};

}

