#include "CPU6502.h"

#include "Memory.h"

namespace emulator6502
{

void CPU6502::Init()
{
    Reset();
}

void CPU6502::Reset()
{
    m_A = 0x00;
    m_X = 0x00;
    m_Y = 0x00;
    m_SP = 0xFD;
    m_PC = 0x8000;
    m_Status = 0x00;
}

void CPU6502::ExecuteInstruction()
{
    uint8_t opcode = ReadMemory(m_PC);

    EMULATOR_6502_DEBUG(TEXT("Executing instruction: %04X", opcode));

    switch (opcode)
    {
    case 0xA9:
        m_A = ReadMemory(m_PC + 1);
        m_PC += 2;
        EMULATOR_6502_DEBUG(TEXT("LDA immediate: %x", opcode));
        break;
    case 0x00:
        EMULATOR_6502_DEBUG("CPU Break (BRK) encountered");
        break;
    default:
        EMULATOR_6502_DEBUG(TEXT("Unknown opcode: %x", opcode));
        break;
    }

    EMULATOR_6502_DEBUG(TEXT("Accumulator: %x", m_A));
    EMULATOR_6502_DEBUG(TEXT("Program counter: %x", m_PC));
}

uint8_t CPU6502::ReadMemory(const uint16_t address) const
{
    return Memory::Read(address);
}

void CPU6502::WriteMemory(const uint16_t address, const uint8_t value)
{
    Memory::Write(address, value);
}

std::string CPU6502::ToString() const
{
    std::stringstream ss;

    ss << "Accumulator (A): " << std::hex << std::uppercase << (int)m_A << "\r\n";
    ss << "X Register (X): " << std::hex << (int32_t)m_X << "\r\n";
    ss << "Y Register (Y): " << std::hex << (int32_t)m_Y << "\r\n";
    ss << "Stack Pointer (SP): " << std::hex << (int32_t)m_SP << "\r\n";
    ss << "Program Counter (PC): " << std::hex << (int32_t)m_PC << "\r\n";
    ss << "Status Register (Status): " << std::hex << (int32_t)m_Status << "\r\n";

    return ss.str();
}

} // namespace emulator6502
