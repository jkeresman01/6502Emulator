#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <array>
#include <cstdint>
#include <string>
#include <emulator/shared/Logger.h>

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

//////////////////////////////////////////////////////////////
///
/// @struct Flags
///
/// @brief Represents the 6502 CPU status flags. Although the
///        real 6502 packs these into a single byte, exposing
///        them as bit fields improves readability when
///        inspecting/modifying individual flags.
///
//////////////////////////////////////////////////////////////
struct Flags
{
    Byte C : 1; ///< Carry Flag
    Byte Z : 1; ///< Zero Flag
    Byte I : 1; ///< Interrupt Disable
    Byte D : 1; ///< Decimal Mode
    Byte B : 1; ///< Break Command
    Byte _ : 1; ///< Unused (on real 6502 typically set to 1 when pushed)
    Byte V : 1; ///< Overflow Flag
    Byte N : 1; ///< Negative Flag
};

//////////////////////////////////////////////////////////////
///
/// @class CPU6502
///
/// @brief Emulates the MOS 6502 CPU: registers, status flags,
///        memory access, stack operations, instruction fetch/
///        decode/execute via a dispatch table, and a complete
///        set of opcode handlers.
///
/// Typical usage:
/// @code
/// CPU6502 cpu;
/// cpu.Init();
/// cpu.Reset();
/// while (running) {
///     cpu.Step();  // fetch, decode, execute one instruction
/// }
/// @endcode
///
//////////////////////////////////////////////////////////////
class CPU6502
{
    using Instruction = void (CPU6502::*)();

  public:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Default constructor
    ///
    //////////////////////////////////////////////////////////////
    CPU6502() = default;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Initializes CPU internals (e.g., dispatch table).
    ///        Call once before using the CPU.
    ///
    //////////////////////////////////////////////////////////////
    void Init();

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Resets CPU to power-on state: registers, flags,
    ///        program counter, and stack pointer.
    ///
    //////////////////////////////////////////////////////////////
    void Reset();

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Executes a single instruction (fetch, decode,
    ///        execute). Advances PC and updates flags as needed.
    ///
    //////////////////////////////////////////////////////////////
    void Step();

    //////////////////////////////////////////////////////////////
    ///
    /// @name Register Accessors
    ///
    //////////////////////////////////////////////////////////////
    ///@{
    Byte GetAccumulator() const { return m_A; }
    Byte GetRegisterX() const { return m_X; }
    Byte GetRegisterY() const { return m_Y; }
    Word GetProgramCounter() const { return m_PC; }
    Byte GetStackPointer() const { return m_SP; }
    Flags GetStatusFlags() const { return m_StatusFlags; }
    bool HasStackOverflowed() const { return m_StackOverflow; }
    ///@}

    //////////////////////////////////////////////////////////////
    ///
    /// @name Register Mutators
    ///
    //////////////////////////////////////////////////////////////
    ///@{
    void SetAccumulator(const Byte value) { m_A = value; }
    void SetRegisterX(const Byte value) { m_X = value; }
    void SetRegisterY(const Byte value) { m_Y = value; }
    void SetStackPointer(const Byte value) { m_SP = value; }
    void SetFlags(const Flags &flags) { m_StatusFlags = flags; }
    ///@}

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Clears the internal stack overflow indicator.
    ///
    //////////////////////////////////////////////////////////////
    void ClearStackOverflowFlag() { m_StackOverflow = false; }

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Returns a human-readable dump of the CPU state
    ///        (registers, flags, program counter).
    ///
    //////////////////////////////////////////////////////////////
    std::string ToString() const;

  private:
    //////////////////////////////////////////////////////////////
    ///
    /// @brief Sets up the opcode->handler dispatch table.
    ///
    //////////////////////////////////////////////////////////////
    void InitDispatchTable();

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Handler invoked when an invalid/unimplemented
    ///        opcode is encountered.
    ///
    //////////////////////////////////////////////////////////////
    void InvalidOpcode();

  private:
    //////////////////////////////////////////////////////////////
    ///
    /// @name Fetch / Memory / Stack helpers
    ///
    //////////////////////////////////////////////////////////////
    ///@{

    /// @brief Fetches the next byte from memory and increments PC.
    Byte FetchByte();

    /// @brief Fetches the next word (little-endian) from memory and increments PC by 2.
    Word FetchWord();

    /// @brief Reads a byte from memory at @p address.
    Byte ReadByte(const Word address);

    /// @brief Writes a byte @p value to memory at @p address.
    void WriteByte(const Word address, const Byte value);

    /// @brief Pops a byte from the stack into a register.
    Byte PopByte();

    /// @brief Pushes a byte @p value onto the stack.
    void PushByte(const Byte value);

    /// @brief Pops a word (high byte after low byte) from the stack.
    Word PopWord();

    /// @brief Pushes a word @p value onto the stack (low, then high).
    void PushWord(const Word value);
    ///@}

  private:
    ////////////////////            LDA (Load accumulator)            ////////////////////
    void LDAImmediate();
    void LDAZeroPage();
    void LDAZeroPageX();
    void LDAAbsolute();
    void LDAAbsoluteX();
    void LDAAbsoluteY();
    void LDAIndirectX();
    void LDAIndirectY();

    ////////////////////            LDX (Load X register)            ////////////////////
    void LDXImmediate();
    void LDXZeroPage();
    void LDXZeroPageY();
    void LDXAbsolute();
    void LDXAbsoluteY();

    ////////////////////            LDY (Load Y register)            ////////////////////
    void LDYImmediate();
    void LDYZeroPage();
    void LDYZeroPageX();
    void LDYAbsolute();
    void LDYAbsoluteX();

    ////////////////////            CLC (Clear carry flag)                ////////////////////
    void CLC();

    ////////////////////            CLD (Clear decimal mode)              ////////////////////
    void CLD();

    ////////////////////            CLD (Clear interrupt disabled bit)    ////////////////////
    void CLI();

    ////////////////////            CLD (Clear overrflow flag)            ////////////////////
    void CLV();

    ////////////////////            DEX (Decrement X)                    ////////////////////
    void DEX();

    ////////////////////            DEY (Decrement Y)                    ////////////////////
    void DEY();

    ////////////////////            DEC (Decrement memory by one)        ////////////////////
    void DECZeroPage();
    void DECZeroPageX();
    void DECAbsolute();
    void DECAbsoluteX();

    ////////////////////            NOP (No operation)                   ////////////////////
    void NOP();

    ////////////////////            STA (Store accumulator)              ////////////////////
    void STAZeroPage();
    void STAZeroPageX();
    void STAAbsolute();
    void STAAbsoluteX();
    void STAAbsoluteY();
    void STAIndirectX();
    void STAIndirectY();

    ////////////////////            STX (Store X register)              ////////////////////
    void STXZeroPage();
    void STXZeroPageY();
    void STXAbsolute();

    ////////////////////            STY (Store Y register)              ////////////////////
    void STYZeroPage();
    void STYZeroPageX();
    void STYAbsolute();

    ////////////////////            AND (AND memory with acumulator)              ////////////////////
    void ANDImmediate();
    void ANDZeroPage();
    void ANDZeroPageX();
    void ANDAbsolute();
    void ANDAbsoluteX();
    void ANDAbsoluteY();
    void ANDIndirectX();
    void ANDIndirectY();

    ////////////////////            OR (OR memory with acumulator)              ////////////////////
    void ORAImmediate();
    void ORAZeroPage();
    void ORAZeroPageX();
    void ORAAbsolute();
    void ORAAbsoluteX();
    void ORAAbsoluteY();
    void ORAIndirectX();
    void ORAIndirectY();

    ////////////////////        ASL ( Shift Left One Bit (Memory or Accumulator) )    ////////////////////
    void ASLAccumulator();
    void ASLZeroPage();
    void ASLZeroPageX();
    void ASLAbsolute();
    void ASLAbsoluteX();

    ////////////////////        LSR ( Shift One Bit Right (Memory or Accumulator))   ////////////////////
    void LSRAccumulator();
    void LSRZeroPage();
    void LSRZeroPageX();
    void LSRAbsolute();
    void LSRAbsoluteX();

    ////////////////////        ADC ( Add Memory to Accumulator with Carry )   ////////////////////
    void ADCImmediate();
    void ADCZeroPage();
    void ADCZeroPageX();
    void ADCAbsolute();
    void ADCAbsoluteX();
    void ADCAbsoluteY();
    void ADCIndirectX();
    void ADCIndirectY();

    /// @brief Helper for ADC family: adds @p value + Carry to A and updates flags.
    void AddWithCarry(const Byte value);

    ////////////////////  SBC (Subtract with Borrow)  ////////////////////
    void SBCImmediate();
    void SBCZeroPage();
    void SBCZeroPageX();
    void SBCAbsolute();
    void SBCAbsoluteX();
    void SBCAbsoluteY();
    void SBCIndirectX();
    void SBCIndirectY();

    /// @brief Helper for SBC family: A = A - value - (1 - Carry), updates flags.
    void SubtractWithBorrow(const Byte value);

    ////////////////////  Register Transfers  ////////////////////
    void TAX();
    void TAY();
    void TXA();
    void TYA();
    void TSX();
    void TXS();

    ////////////////////  EOR (Exclusive OR)  ////////////////////
    void EORImmediate();
    void EORZeroPage();
    void EORZeroPageX();
    void EORAbsolute();
    void EORAbsoluteX();
    void EORAbsoluteY();
    void EORIndirectX();
    void EORIndirectY();

    /// @brief Helper for EOR family: A ^= value; updates Z/N.
    void ExclusiveOR(const Byte value);

    ////////////////////  CMP (Compare Accumulator)  ////////////////////
    void CMPImmediate();
    void CMPZeroPage();
    void CMPZeroPageX();
    void CMPAbsolute();
    void CMPAbsoluteX();
    void CMPAbsoluteY();
    void CMPIndirectX();
    void CMPIndirectY();

    /// @brief Helper for CMP/CPX/CPY: sets C/Z/N as if (register - value) occurred.
    void Compare(const Byte registerValue, const Byte value);

    ////////////////////  INC (Increment Memory)  ////////////////////
    void INCZeroPage();
    void INCZeroPageX();
    void INCAbsolute();
    void INCAbsoluteX();

    ////////////////////  INX (Increment X register)  ////////////////////
    void INX();

    ////////////////////  INY (Increment Y register)  ////////////////////
    void INY();

    ////////////////////  Branch Instructions  ////////////////////
    void BNE();
    void BEQ();
    void BPL();
    void BMI();
    void BVC();
    void BVS();
    void BCC();
    void BCS();

    ////////////////////  Control Flow  ////////////////////
    void RTI();
    void RTS();
    void JSR();
    void BRK();

    ////////////////////  Flag Set Instructions  ////////////////////
    void SEC();
    void SED();
    void SEI();

    ////////////////////  Stack Instructions  ////////////////////
    void PHA();
    void PHP();
    void PLA();
    void PLP();

    ////////////////////  Compare Instructions  ////////////////////
    void CPXImmediate();
    void CPXZeroPage();
    void CPXAbsolute();

    void CPYImmediate();
    void CPYZeroPage();
    void CPYAbsolute();

    ////////////////////  Bitwise / Rotate / Test Instructions  ////////////////////
    void ROLAccumulator();
    void ROLZeroPage();
    void ROLZeroPageX();
    void ROLAbsolute();
    void ROLAbsoluteX();

    void RORAccumulator();
    void RORZeroPage();
    void RORZeroPageX();
    void RORAbsolute();
    void RORAbsoluteX();

    void BITZeroPage();
    void BITAbsolute();

    ////////////////////  Unconditional Jump  ////////////////////
    void JMPAbsolute();
    void JMPIndirect();

  private:
    //////////////////////////////////////////////////////////////
    ///
    /// @name CPU Registers
    ///
    //////////////////////////////////////////////////////////////
    ///@{
    Byte m_A;  ///< Accumulator
    Byte m_X;  ///< Index register X
    Byte m_Y;  ///< Index register Y
    Word m_PC; ///< Program counter
    Byte m_SP; ///< Stack pointer
    ///@}

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Program status register. Exposed both as a raw
    ///        byte and as bitfields for convenience.
    ///
    //////////////////////////////////////////////////////////////
    union {
        Byte  m_StatusRegisterFlags; ///< Raw processor status (P)
        Flags m_StatusFlags;         ///< Bitfield access to P
    };

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Opcode dispatch table (0x00–0xFF) mapping to
    ///        instruction handlers.
    ///
    //////////////////////////////////////////////////////////////
    std::array<Instruction, 256> m_InstructionSetDispatchTable;

    //////////////////////////////////////////////////////////////
    ///
    /// @brief Indicates that a stack overflow condition occurred
    ///        (implementation-defined; useful for UI warnings).
    ///
    //////////////////////////////////////////////////////////////
    bool m_StackOverflow = false;
};

} // namespace emulator6502

