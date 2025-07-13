#pragma once

#define MEMORY_64KB 65536

#include <cstdint>
#include <cstdio>
#include <vector>

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

////////////////////////////////////////////////////////////
///
/// @class Memory
///
/// @brief A utility class responsible for managing the emulator's
///        memory (64KB).
///        This class provides methods to initialize,
///        reset, read, and write data to memory locations.
///
////////////////////////////////////////////////////////////
class Memory
{
  public:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Deleted default constructor to prevent instantiation.
    ///
    //////////////////////////////////////////////////////////////
    Memory() = delete;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Initializes the memory system
    ///
    //////////////////////////////////////////////////////////////
    static void Init();

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Resets the memory, clearing all the values to their
    ///        initial state.
    ///
    //////////////////////////////////////////////////////////////
    static void Reset();

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Reads a byte from the specified memory address.
    ///
    /// @param [in] address The memory address to read from.
    ///
    /// @return The byte value stored at the given address.
    ///
    //////////////////////////////////////////////////////////////
    static Byte Read(const Word address);

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Writes a byte value to the specified memory address.
    ///
    /// @param [in] address The memory address to write to.
    /// @param [in] value The byte value to be written to memory.
    ///
    //////////////////////////////////////////////////////////////
    static void Write(const Word address, const Byte value);

    //////////////////////////////////////////////////////////////
    ///
    /// @brief A static array representing the 64KB of RAM for the emulator.
    ///
    //////////////////////////////////////////////////////////////
    static Byte s_RAM[MEMORY_64KB];
};

} // namespace emulator6502
