#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <cstdint>
#include <vector>

#include <emulator/core/Memory.h>

namespace emulator6502
{

using Byte = uint8_t;

//////////////////////////////////////////////////////////////
///
/// @class SoftwareLoader
///
/// @brief Utility class for loading machine code into the
///        emulator’s memory space.
///
/// Provides a static interface that takes compiled/assembled
/// bytecode and writes it into the memory used by the CPU.
///
//////////////////////////////////////////////////////////////
class SoftwareLoader
{
public:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Deleted default constructor.
    ///        This class is not meant to be instantiated.
    ///
    //////////////////////////////////////////////////////////////
    SoftwareLoader() = delete;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Loads a block of machine code into emulator memory.
    ///
    /// @param [in] machineCode A vector of bytes containing
    ///        the program or data to be written into memory.
    ///
    //////////////////////////////////////////////////////////////
    static void Load(const std::vector<Byte>& machineCode);
};

} // namespace emulator6502

