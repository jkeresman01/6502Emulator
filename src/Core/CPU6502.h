#pragma once

#include <array>
#include <cstdint>

#include "../Util/Logger.h"

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

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

class CPU6502
{
    using Instruction = void (CPU6502::*)();

  public:
    CPU6502() = default;

    void Init();
    void Reset();

    void Step();

    Byte GetAccumulator() const { return m_A; };
    Byte GetRegisterX() const { return m_X; };
    Byte GetRegisterY() const { return m_Y; };
    Word GetProgramCounter() const { return m_PC; };
    Byte GetStackPointer() const { return m_SP; };
    Byte GetStatusFlags() const { return m_StatusRegisterFlags; };

    std::string ToString() const;

  private:
    void InitDispatchTable();

    void WriteByte(const Word address, const Byte value);

    Byte FetchByte();
    Word FetchWord();

    Byte ReadByte(const Word address);

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

    ////////////////////  SBC (Subtract with Carry)  ////////////////////
    void SBCImmediate();
    void SBCZeroPage();
    void SBCZeroPageX();
    void SBCAbsolute();
    void SBCAbsoluteX();
    void SBCAbsoluteY();
    void SBCIndirectX();
    void SBCIndirectY();

    ////////////////////  Register Transfers  ////////////////////
    void TAX();
    void TAY();
    void TXA();
    void TYA();

    ////////////////////  EOR (Exclusive OR)  ////////////////////
    void EORImmediate();
    void EORZeroPage();
    void EORZeroPageX();
    void EORAbsolute();
    void EORAbsoluteX();
    void EORAbsoluteY();
    void EORIndirectX();
    void EORIndirectY();

    ////////////////////  CMP (Compare Accumulator)  ////////////////////
    void CMPImmediate();
    void CMPZeroPage();
    void CMPZeroPageX();
    void CMPAbsolute();
    void CMPAbsoluteX();
    void CMPAbsoluteY();
    void CMPIndirectX();
    void CMPIndirectY();

    ////////////////////  INC (Increment Memory)  ////////////////////
    void INCZeroPage();
    void INCZeroPageX();
    void INCAbsolute();
    void INCAbsoluteX();

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

    ////////////////////        Invalid opcode         ////////////////////
    void InvalidOpcode();

  private:
    void PrintRegisterState();

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
        Flags StatusFlags;
    };

    ////////////////////            DISPATCH TABLE        ////////////////////
    std::array<Instruction, 256> m_InstructionSetDispatchTable;
};
} // namespace emulator6502
