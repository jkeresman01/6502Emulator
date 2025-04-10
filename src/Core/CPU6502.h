#pragma once

#include <cstdint>

#include "../Util/Logger.h"

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

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

    ////////////////////            DEC (Decrement memory by one)            ////////////////////
    void DECZeroPage();
    void DECZeroPageX();
    void DECAbsoulute();
    void DECAbsouluteX();

    ////////////////////            NOP (No operation)                    ////////////////////
    void NOP();

    ////////////////////            STA            ////////////////////
    void ExecuteSTA();

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

    Byte C : 1;
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;

    ////////////////////            STATUS FLAGS        ////////////////////
};
} // namespace emulator6502
