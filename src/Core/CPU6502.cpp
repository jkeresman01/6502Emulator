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
    m_PC = 0x0800;
    m_Status = 0x00;
}

void CPU6502::Step() 
{
    uint8_t opcode = ReadMemory(m_PC);
    m_PC++;
    DecodeAndExecute(opcode);
}

void CPU6502::DecodeAndExecute(const uint8_t opcode)
{
    switch (opcode)
    {
    case 0xA9:
        ExecuteLDA();
        break;

    case 0x8D:
        ExecuteSTA();
        break;

    case 0x00:
        EMULATOR_6502_DEBUG("CPU Break (BRK) encountered");
        break;

    default:
        EMULATOR_6502_DEBUG(TEXT("Unknown opcode: %02X"), opcode);
        break;
    }

    PrintRegisterState();
}

void CPU6502::ExecuteLDA()
{
    m_A = ReadMemory(m_PC);
    m_PC++;
    EMULATOR_6502_DEBUG(TEXT("LDA immediate: %02X"), m_A);
}

void CPU6502::ExecuteSTA()
{
    uint16_t address = ReadMemory(m_PC) | (ReadMemory(m_PC + 1) << 8);
    m_PC += 2;
    WriteMemory(address, m_A);
    EMULATOR_6502_DEBUG(TEXT("STA: Stored %02X at %04X"), m_A, address);
}

void CPU6502::PrintRegisterState()
{
    EMULATOR_6502_DEBUG(TEXT("Registers: A=%02X X=%02X Y=%02X SP=%02X PC=%04X"), m_A, m_X, m_Y, m_SP, m_PC);
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

    ss << "Accumulator (A): " << std::hex << std::uppercase << (int32_t)m_A << "\r\n";
    ss << "X Register (X): " << std::hex << (int32_t)m_X << "\r\n";
    ss << "Y Register (Y): " << std::hex << (int32_t)m_Y << "\r\n";
    ss << "Stack Pointer (SP): " << std::hex << (int32_t)m_SP << "\r\n";
    ss << "Program Counter (PC): " << std::hex << (int32_t)m_PC << "\r\n";
    ss << "Status Register (Status): " << std::hex << (int32_t)m_Status << "\r\n";

    return ss.str();
}

} // namespace emulator6502
