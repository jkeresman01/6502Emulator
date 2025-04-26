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

////////////////////////////////////////////////////////////
///
/// @class ProgramUtil
///
/// @brief A utility class for loading and reading programs
///        (machine code) into and from memory.
///
////////////////////////////////////////////////////////////
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

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Loads the program (machine code) into memory.
    ///
    /// @param [in] machineCode A vector of bytes representing
    ///             the machine code of the program.
    ///
    //////////////////////////////////////////////////////////////
    static void LoadProgramIntoMemory(const std::vector<Byte> &machineCode);

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Reads the program (machine code) from memory.
    ///
    /// @return A vector of bytes representing the machine code
    ///         of the program read from memory.
    ///
    //////////////////////////////////////////////////////////////
    static std::vector<Byte> ReadProgramFromMemory();
};
} // namespace emulator6502
