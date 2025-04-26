#pragma once

#include <array>
#include <cstdint>

#include "../Common/Logger.h"
#include "../Types/Flags.h"

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

class CPU6502
{
    using Instruction = void (CPU6502::*)();

  public:
    CPU6502() = default;

    void Init();
    void Reset();

    void Step();

    Byte GetAccumulator() const { return m_A; }
    Byte GetRegisterX() const { return m_X; }
    Byte GetRegisterY() const { return m_Y; }
    Word GetProgramCounter() const { return m_PC; }
    Byte GetStackPointer() const { return m_SP; }
    Flags GetStatusFlags() const { return m_StatusFlags; }
    bool HasStackOverflowed() const { return m_StackOverflow; }

    void SetAccumulator(const Byte value) { m_A = value; }
    void SetRegisterX(const Byte value) { m_X = value; }
    void SetRegisterY(const Byte value) { m_Y = value; }
    void SetStackPointer(const Byte value) { m_SP = value; }
    void SetFlags(const Flags &flags) { m_StatusFlags = flags; }

    void ClearStackOverflowFlag() { m_StackOverflow = false; }

    std::string ToString() const;

  private:
    void InitDispatchTable();
    void InvalidOpcode();

  private:
    Byte FetchByte();
    Word FetchWord();

    Byte ReadByte(const Word address);
    void WriteByte(const Word address, const Byte value);

    Byte PopByte();
    void PushByte(const Byte value);

    Word PopWord();
    void PushWord(const Word value);

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
    ////////////////////            REGISTERS            ////////////////////
    Byte m_A;
    Byte m_X;
    Byte m_Y;
    Word m_PC;
    Byte m_SP;

    ////////////////////            STATUS FLAGS        ////////////////////
    union {
        Byte m_StatusRegisterFlags;
        Flags m_StatusFlags;
    };

    ////////////////////            DISPATCH TABLE        ////////////////////
    std::array<Instruction, 256> m_InstructionSetDispatchTable;

    ////////////////////          Stack overflow flag        ////////////////////
    bool m_StackOverflow = false;
};
} // namespace emulator6502
