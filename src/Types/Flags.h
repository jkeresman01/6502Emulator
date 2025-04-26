#pragma once


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <cstdint>

namespace emulator6502
{

using Byte = uint8_t;

struct Flags
{
    Byte C : 1;
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte _ : 1;
    Byte V : 1;
    Byte N : 1;
};

}