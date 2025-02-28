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
    m_A = 0;
    m_X = 0;
    m_Y = 0;
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

    // TODO print register state

    return ss.str();
}

} // namespace emulator6502
