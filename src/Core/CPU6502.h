#pragma once

#include <cstdint>

#include "../Util/Logger.h"

namespace emulator6502
{

class CPU6502
{
  public:
    CPU6502() = default;

    void Init();
    void Reset();
    void Step();

    uint8_t GetAccumulator() const { return m_A; };
    uint8_t GetRegisterX() const { return m_X; };
    uint8_t GetRegisterY() const { return m_Y; };
    uint16_t GetProgramCounter() const { return m_PC; };
    uint8_t GetStackPointer() const { return m_SP; };
    uint8_t GetStatusFlags() const { return m_Status; };

    std::string ToString() const;

  private:
    uint8_t ReadMemory(const uint16_t address) const;
    void WriteMemory(const uint16_t address, const uint8_t value);

  private:
    void Fetch();
    void DecodeAndExecute(const uint8_t opcode);

  private:
    void ExecuteLDA();
    void ExecuteSTA();

  private:
    void PrintRegisterState();

  private:
    uint8_t m_A;
    uint8_t m_X;
    uint8_t m_Y;
    uint16_t m_PC;
    uint8_t m_SP;
    uint8_t m_Status;
};
} // namespace emulator6502
