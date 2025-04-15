#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <memory>
#include <string>
#include <vector>

#include "../Assembler/Assembler.h"
#include "../Core/Memory.h"

namespace emulator6502
{
class ProgramUtil
{
  public:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Deleted default constructor to prevent instantiation.
    ///        Utility class.
    ///
    //////////////////////////////////////////////////////////////
    ProgramUtil() = delete;

    static void LoadProgramIntoMemory(const std::vector<Byte> &machineCode);
    static std::vector<Byte> ReadProgramFromMemory();
};
} // namespace emulator6502