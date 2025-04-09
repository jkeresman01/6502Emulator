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
    ////////////////////             REGISTERS            ////////////////////

    m_A = 0x00;
    m_X = 0x00;
    m_Y = 0x00;
    m_SP = 0xFD;
    m_PC = 0x0800;

    ////////////////////            STATUS FLAGS        ////////////////////

    C = 0;
    Z = 0;
    I = 0;
    D = 0;
    B = 0;
    V = 0;
    N = 0;
}

Byte CPU6502::FetchByte()
{
    return Memory::Read(m_PC++);
}

Word CPU6502::FetchWord()
{
    Word data = Memory::Read(m_PC) | (Memory::Read(m_PC + 1) << 8);
    m_PC += 2;
    return data;
}

Byte CPU6502::ReadByte(const Word address)
{
    return Memory::Read(address);
}

void CPU6502::WriteByte(const Word address, const Byte value)
{
    Memory::Write(address, value);
}

void CPU6502::Step()
{
    Byte opcode = FetchByte();
    DecodeAndExecute(opcode);
}

void CPU6502::DecodeAndExecute(const Byte opcode)
{
    switch (opcode)
    {
    case 0xA9:
        LDAImmediate();
        break;

    case 0xA5:
        LDAZeroPage();
        break;

    case 0xB5:
        LDAZeroPageX();
        break;

    case 0xAD:
        LDAAbsoulute();
        break;

    case 0xBD:
        LDAAbsouluteX();
        break;

    case 0xB9:
        LDAAbsouluteY();
        break;

    case 0xA1:
        LDAIndirectX();
        break;

    case 0xB1:
        LDAIndirectY();
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

void CPU6502::LDAImmediate()
{
    m_A = FetchByte();

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAZeroPage()
{
    Byte ZeroPageAddr = FetchByte();

    m_A = ReadByte(ZeroPageAddr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAZeroPageX()
{
    Byte ZeroPageAddr = FetchByte();

    ZeroPageAddr += m_X;

    m_A = ReadByte(ZeroPageAddr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAAbsoulute() 
{
    Word address = FetchWord();
    
    m_A = ReadByte(address);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAAbsouluteX() 
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    m_A = ReadByte(addr);
    
    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAAbsouluteY()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_Y;

    m_A = ReadByte(addr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAIndirectX()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte((zeroPageAddr + m_X) & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + m_X + 1) & 0xFF);

    Word addr = (addrHighByte << 8) | addrLowByte;

    m_A = ReadByte(addr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAIndirectY()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte(zeroPageAddr & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = ((addrHighByte << 8) | addrLowByte) + m_Y;

    m_A = ReadByte(addr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ExecuteSTA()
{
    Word storeAddr = FetchWord();
    WriteByte(storeAddr, m_A);
}

void CPU6502::PrintRegisterState()
{
    EMULATOR_6502_DEBUG(TEXT("Registers: A=%02X X=%02X Y=%02X SP=%02X PC=%04X"), m_A, m_X, m_Y, m_SP, m_PC);
}

std::string CPU6502::ToString() const
{
    std::stringstream ss;

    ss << "Accumulator (A): " << std::hex << std::uppercase << (int32_t)m_A << "\r\n";
    ss << "X Register (X): " << std::hex << (int32_t)m_X << "\r\n";
    ss << "Y Register (Y): " << std::hex << (int32_t)m_Y << "\r\n";
    ss << "Stack Pointer (SP): " << std::hex << (int32_t)m_SP << "\r\n";
    ss << "Program Counter (PC): " << std::hex << (int32_t)m_PC << "\r\n";

    return ss.str();
}

} // namespace emulator6502
