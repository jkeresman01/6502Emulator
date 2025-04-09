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
    void WriteWord(const Word address, const Byte value);

    Byte FetchByte();
    Word FetchWord();

    Byte ReadByte(const Word address);

    void DecodeAndExecute(const Byte opcode);

  private:
    ////////////////////            LDA            ////////////////////
    void LDAImmediate();
    void LDAZeroPage();
    void LDAZeroPageX();
    void LDAAbsoulute();
    void LDAAbsouluteX();
    void LDAAbsouluteY();
    void LDAAIndirectX();
    void LDAAIndirectY();



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
