#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <cstdint>

namespace emulator6502
{
using Byte = uint8_t;

////////////////////////////////////////////////////////////
///
/// @struct Flags
///
/// @brief Represents the status flags of the 6502 CPU.
///
/// @details This struct encapsulates the eight status flags used by the 6502 CPU.
///          These flags are part of the processor's status register and are used
///          to control various aspects of the CPU's behavior. Each flag is represented
///          by a single bit in the byte, with a 1 or 0 indicating whether the flag is
///          set or cleared.
///
///////////////////////////////////////////////////////////
struct Flags
{
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Carry Flag (C)
    ///
    /// This flag is set when a carry-out occurs during an addition or a borrow during
    /// subtraction, or if the flag is manually set or cleared using specific instructions.
    ///
    //////////////////////////////////////////////////////////////
    Byte C : 1;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Zero Flag (Z)
    ///
    /// This flag is set if the result of an operation is zero. It is used to indicate
    /// whether an operation resulted in a zero value.
    ///
    //////////////////////////////////////////////////////////////
    Byte Z : 1;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Interrupt Disable Flag (I)
    ///
    /// This flag is used to disable interrupts when set. When clear, interrupts are enabled.
    ///
    //////////////////////////////////////////////////////////////
    Byte I : 1;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Decimal Mode Flag (D)
    ///
    /// This flag is used to enable or disable the decimal mode for arithmetic operations.
    ///
    //////////////////////////////////////////////////////////////
    Byte D : 1;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Break Command Flag (B)
    ///
    /// This flag is used internally to indicate a break (BRK) instruction. It is not typically
    /// used in normal operations, but it is set during software interrupts.
    ///
    //////////////////////////////////////////////////////////////
    Byte B : 1;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Unused Flag (_)
    ///
    /// This flag is reserved and always set to 1. It is not used in the 6502 CPU.
    ///
    //////////////////////////////////////////////////////////////
    Byte _ : 1;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Overflow Flag (V)
    ///
    /// This flag is set when an overflow occurs during an arithmetic operation.
    ///
    //////////////////////////////////////////////////////////////
    Byte V : 1;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Negative Flag (N)
    ///
    /// This flag is set if the result of an operation is negative (i.e., if bit 7 of the
    /// result is set). It reflects the sign of the result.
    ///
    //////////////////////////////////////////////////////////////
    Byte N : 1;
};

} // namespace emulator6502
