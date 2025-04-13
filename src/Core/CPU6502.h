#pragma once

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
    void WriteByte(const Word address, const Byte value);

    Byte FetchByte();
    Word FetchWord();

    Byte ReadByte(const Word address);

    void DecodeAndExecute(const Byte opcode);

  private:
    ////////////////////            LDA (Load accumulator)            ////////////////////
    void LDAImmediate();
    void LDAZeroPage();
    void LDAZeroPageX();
    void LDAAbsoulute();
    void LDAAbsouluteX();
    void LDAAbsouluteY();
    void LDAIndirectX();
    void LDAIndirectY();

    ////////////////////            LDX (Load X register)            ////////////////////
    void LDXImmediate();
    void LDXZeroPage();
    void LDXZeroPageY();
    void LDXAbsoulute();
    void LDXAbsouluteY();

    ////////////////////            LDY (Load Y register)            ////////////////////
    void LDYImmediate();
    void LDYZeroPage();
    void LDYZeroPageX();
    void LDYAbsoulute();
    void LDYAbsouluteX();

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
    void DECAbsoulute();
    void DECAbsouluteX();

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
    union 
    {
        Byte m_StatusRegisterFlags;
        Flags StatusFlags;
    };

};
} // namespace emulator6502
