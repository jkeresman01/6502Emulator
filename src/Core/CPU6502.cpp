#include "CPU6502.h"

#include "Memory.h"

namespace emulator6502
{

void CPU6502::Init()
{
    InitDispatchTable();
    Reset();
}

void CPU6502::InitDispatchTable()
{
    m_InstructionSetDispatchTable.fill(&CPU6502::InvalidOpcode);

    m_InstructionSetDispatchTable[0xA9] = &CPU6502::LDAImmediate;
    m_InstructionSetDispatchTable[0xA5] = &CPU6502::LDAZeroPage;
    m_InstructionSetDispatchTable[0xB5] = &CPU6502::LDAZeroPageX;
    m_InstructionSetDispatchTable[0xAD] = &CPU6502::LDAAbsolute;
    m_InstructionSetDispatchTable[0xBD] = &CPU6502::LDAAbsoluteX;
    m_InstructionSetDispatchTable[0xB9] = &CPU6502::LDAAbsoluteY;
    m_InstructionSetDispatchTable[0xA1] = &CPU6502::LDAIndirectX;
    m_InstructionSetDispatchTable[0xB1] = &CPU6502::LDAIndirectY;

    m_InstructionSetDispatchTable[0x85] = &CPU6502::STAZeroPage;
    m_InstructionSetDispatchTable[0x95] = &CPU6502::STAZeroPageX;
    m_InstructionSetDispatchTable[0x8D] = &CPU6502::STAAbsolute;
    m_InstructionSetDispatchTable[0x9D] = &CPU6502::STAAbsoluteX;
    m_InstructionSetDispatchTable[0x99] = &CPU6502::STAAbsoluteY;
    m_InstructionSetDispatchTable[0x81] = &CPU6502::STAIndirectX;
    m_InstructionSetDispatchTable[0x91] = &CPU6502::STAIndirectY;

    m_InstructionSetDispatchTable[0xA2] = &CPU6502::LDXImmediate;
    m_InstructionSetDispatchTable[0xA6] = &CPU6502::LDXZeroPage;
    m_InstructionSetDispatchTable[0xB6] = &CPU6502::LDXZeroPageY;
    m_InstructionSetDispatchTable[0xAE] = &CPU6502::LDXAbsolute;
    m_InstructionSetDispatchTable[0xBE] = &CPU6502::LDXAbsoluteY;

    m_InstructionSetDispatchTable[0xA0] = &CPU6502::LDYImmediate;
    m_InstructionSetDispatchTable[0xA4] = &CPU6502::LDYZeroPage;
    m_InstructionSetDispatchTable[0xB4] = &CPU6502::LDYZeroPageX;
    m_InstructionSetDispatchTable[0xAC] = &CPU6502::LDYAbsolute;
    m_InstructionSetDispatchTable[0xBC] = &CPU6502::LDYAbsoluteX;

    m_InstructionSetDispatchTable[0x69] = &CPU6502::ADCImmediate;
    m_InstructionSetDispatchTable[0x65] = &CPU6502::ADCZeroPage;
    m_InstructionSetDispatchTable[0x75] = &CPU6502::ADCZeroPageX;
    m_InstructionSetDispatchTable[0x6D] = &CPU6502::ADCAbsolute;
    m_InstructionSetDispatchTable[0x7D] = &CPU6502::ADCAbsoluteX;
    m_InstructionSetDispatchTable[0x79] = &CPU6502::ADCAbsoluteY;
    m_InstructionSetDispatchTable[0x61] = &CPU6502::ADCIndirectX;
    m_InstructionSetDispatchTable[0x71] = &CPU6502::ADCIndirectY;

    m_InstructionSetDispatchTable[0xE9] = &CPU6502::SBCImmediate;
    m_InstructionSetDispatchTable[0xE5] = &CPU6502::SBCZeroPage;
    m_InstructionSetDispatchTable[0xF5] = &CPU6502::SBCZeroPageX;
    m_InstructionSetDispatchTable[0xED] = &CPU6502::SBCAbsolute;
    m_InstructionSetDispatchTable[0xFD] = &CPU6502::SBCAbsoluteX;
    m_InstructionSetDispatchTable[0xF9] = &CPU6502::SBCAbsoluteY;
    m_InstructionSetDispatchTable[0xE1] = &CPU6502::SBCIndirectX;
    m_InstructionSetDispatchTable[0xF1] = &CPU6502::SBCIndirectY;

    m_InstructionSetDispatchTable[0x29] = &CPU6502::ANDImmediate;
    m_InstructionSetDispatchTable[0x25] = &CPU6502::ANDZeroPage;
    m_InstructionSetDispatchTable[0x35] = &CPU6502::ANDZeroPageX;
    m_InstructionSetDispatchTable[0x2D] = &CPU6502::ANDAbsolute;
    m_InstructionSetDispatchTable[0x3D] = &CPU6502::ANDAbsoluteX;
    m_InstructionSetDispatchTable[0x39] = &CPU6502::ANDAbsoluteY;
    m_InstructionSetDispatchTable[0x21] = &CPU6502::ANDIndirectX;
    m_InstructionSetDispatchTable[0x31] = &CPU6502::ANDIndirectY;

    m_InstructionSetDispatchTable[0x09] = &CPU6502::ORAImmediate;
    m_InstructionSetDispatchTable[0x05] = &CPU6502::ORAZeroPage;
    m_InstructionSetDispatchTable[0x15] = &CPU6502::ORAZeroPageX;
    m_InstructionSetDispatchTable[0x0D] = &CPU6502::ORAAbsolute;
    m_InstructionSetDispatchTable[0x1D] = &CPU6502::ORAAbsoluteX;
    m_InstructionSetDispatchTable[0x19] = &CPU6502::ORAAbsoluteY;
    m_InstructionSetDispatchTable[0x01] = &CPU6502::ORAIndirectX;
    m_InstructionSetDispatchTable[0x11] = &CPU6502::ORAIndirectY;

    m_InstructionSetDispatchTable[0xAA] = &CPU6502::TAX;
    m_InstructionSetDispatchTable[0xA8] = &CPU6502::TAY;
    m_InstructionSetDispatchTable[0x8A] = &CPU6502::TXA;
    m_InstructionSetDispatchTable[0x98] = &CPU6502::TYA;

    m_InstructionSetDispatchTable[0x49] = &CPU6502::EORImmediate;
    m_InstructionSetDispatchTable[0x45] = &CPU6502::EORZeroPage;
    m_InstructionSetDispatchTable[0x55] = &CPU6502::EORZeroPageX;
    m_InstructionSetDispatchTable[0x4D] = &CPU6502::EORAbsolute;
    m_InstructionSetDispatchTable[0x5D] = &CPU6502::EORAbsoluteX;
    m_InstructionSetDispatchTable[0x59] = &CPU6502::EORAbsoluteY;
    m_InstructionSetDispatchTable[0x41] = &CPU6502::EORIndirectX;
    m_InstructionSetDispatchTable[0x51] = &CPU6502::EORIndirectY;

    m_InstructionSetDispatchTable[0xC9] = &CPU6502::CMPImmediate;
    m_InstructionSetDispatchTable[0xC5] = &CPU6502::CMPZeroPage;
    m_InstructionSetDispatchTable[0xD5] = &CPU6502::CMPZeroPageX;
    m_InstructionSetDispatchTable[0xCD] = &CPU6502::CMPAbsolute;
    m_InstructionSetDispatchTable[0xDD] = &CPU6502::CMPAbsoluteX;
    m_InstructionSetDispatchTable[0xD9] = &CPU6502::CMPAbsoluteY;
    m_InstructionSetDispatchTable[0xC1] = &CPU6502::CMPIndirectX;
    m_InstructionSetDispatchTable[0xD1] = &CPU6502::CMPIndirectY;

    m_InstructionSetDispatchTable[0xE6] = &CPU6502::INCZeroPage;
    m_InstructionSetDispatchTable[0xF6] = &CPU6502::INCZeroPageX;
    m_InstructionSetDispatchTable[0xEE] = &CPU6502::INCAbsolute;
    m_InstructionSetDispatchTable[0xFE] = &CPU6502::INCAbsoluteX;

    m_InstructionSetDispatchTable[0xC6] = &CPU6502::DECZeroPage;
    m_InstructionSetDispatchTable[0xD6] = &CPU6502::DECZeroPageX;
    m_InstructionSetDispatchTable[0xCE] = &CPU6502::DECAbsolute;
    m_InstructionSetDispatchTable[0xDE] = &CPU6502::DECAbsoluteX;

    m_InstructionSetDispatchTable[0xD0] = &CPU6502::BNE;
    m_InstructionSetDispatchTable[0xF0] = &CPU6502::BEQ;
    m_InstructionSetDispatchTable[0x10] = &CPU6502::BPL;
    m_InstructionSetDispatchTable[0x30] = &CPU6502::BMI;
    m_InstructionSetDispatchTable[0x50] = &CPU6502::BVC;
    m_InstructionSetDispatchTable[0x70] = &CPU6502::BVS;
    m_InstructionSetDispatchTable[0x90] = &CPU6502::BCC;
    m_InstructionSetDispatchTable[0xB0] = &CPU6502::BCS;

    m_InstructionSetDispatchTable[0xEA] = &CPU6502::NOP;
    m_InstructionSetDispatchTable[0x40] = &CPU6502::RTI;
    m_InstructionSetDispatchTable[0x60] = &CPU6502::RTS;
    m_InstructionSetDispatchTable[0x20] = &CPU6502::JSR;
    m_InstructionSetDispatchTable[0x00] = &CPU6502::BRK;
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

    StatusFlags.C = 0;
    StatusFlags.Z = 0;
    StatusFlags._ = 0;
    StatusFlags.I = 0;
    StatusFlags.D = 0;
    StatusFlags.B = 0;
    StatusFlags.V = 0;
    StatusFlags.N = 0;
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

    Instruction instuction = m_InstructionSetDispatchTable[opcode];

    (this->*instuction)();
}

void CPU6502::LDAImmediate()
{
    m_A = FetchByte();

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAZeroPage()
{
    Byte ZeroPageAddr = FetchByte();

    m_A = ReadByte(ZeroPageAddr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAZeroPageX()
{
    Byte ZeroPageAddr = FetchByte();

    ZeroPageAddr += m_X;

    m_A = ReadByte(ZeroPageAddr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAAbsolute()
{
    Word address = FetchWord();

    m_A = ReadByte(address);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    m_A = ReadByte(addr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAAbsoluteY()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_Y;

    m_A = ReadByte(addr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAIndirectX()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte((zeroPageAddr + m_X) & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + m_X + 1) & 0xFF);

    Word addr = (addrHighByte << 8) | addrLowByte;

    m_A = ReadByte(addr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDAIndirectY()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte(zeroPageAddr & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = ((addrHighByte << 8) | addrLowByte) + m_Y;

    m_A = ReadByte(addr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::LDXImmediate()
{
    m_X = FetchByte();

    StatusFlags.Z = (m_X == 0);
    StatusFlags.N = (m_X & 0b10000000) > 0;
}

void CPU6502::LDXZeroPage()
{
    Byte zeroPageAddr = FetchByte();

    m_X = ReadByte(zeroPageAddr);

    StatusFlags.Z = (m_X == 0);
    StatusFlags.N = (m_X & 0b10000000) > 0;
}

void CPU6502::LDXZeroPageY()
{
    Byte zeroPageAddr = FetchByte();

    zeroPageAddr += m_Y;

    m_X = ReadByte(zeroPageAddr);

    StatusFlags.Z = (m_X == 0);
    StatusFlags.N = (m_X & 0b10000000) > 0;
}

void CPU6502::LDXAbsolute()
{
    Word address = FetchWord();

    m_X = ReadByte(address);

    StatusFlags.Z = (m_X == 0);
    StatusFlags.N = (m_X & 0b10000000) > 0;
}

void CPU6502::LDXAbsoluteY()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_Y;

    m_X = ReadByte(addr);

    StatusFlags.Z = (m_X == 0);
    StatusFlags.N = (m_X & 0b10000000) > 0;
}

void CPU6502::LDYImmediate()
{
    m_Y = FetchByte();

    StatusFlags.Z = (m_Y == 0);
    StatusFlags.N = (m_Y & 0b10000000) > 0;
}

void CPU6502::LDYZeroPage()
{
    Byte zeroPageAddr = FetchByte();

    m_Y = ReadByte(zeroPageAddr);

    StatusFlags.Z = (m_Y == 0);
    StatusFlags.N = (m_Y & 0b10000000) > 0;
}

void CPU6502::LDYZeroPageX()
{
    Byte zeroPageAddr = FetchByte();

    zeroPageAddr += m_X;

    m_Y = ReadByte(zeroPageAddr);

    StatusFlags.Z = (m_Y == 0);
    StatusFlags.N = (m_Y & 0b10000000) > 0;
}

void CPU6502::LDYAbsolute()
{
    Word address = FetchWord();

    m_Y = ReadByte(address);

    StatusFlags.Z = (m_Y == 0);
    StatusFlags.N = (m_Y & 0b10000000) > 0;
}

void CPU6502::LDYAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    m_Y = ReadByte(addr);

    StatusFlags.Z = (m_Y == 0);
    StatusFlags.N = (m_Y & 0b10000000) > 0;
}

void CPU6502::CLC()
{
    StatusFlags.C = 0;
}

void CPU6502::CLD()
{
    StatusFlags.D = 0;
}

void CPU6502::CLI()
{
    StatusFlags.I = 0;
}

void CPU6502::CLV()
{
    StatusFlags.V = 0;
}

void CPU6502::DEX()
{
    m_X--;

    StatusFlags.Z = (m_X == 0);
    StatusFlags.N = (m_X & 0b10000000) > 0;
}

void CPU6502::DEY()
{
    m_Y--;

    StatusFlags.Z = (m_Y == 0);
    StatusFlags.N = (m_Y & 0b10000000) > 0;
}

void CPU6502::DECZeroPage()
{
    Byte zeroPageAddr = FetchByte();

    Byte value = ReadByte(zeroPageAddr);
    value--;

    WriteByte(zeroPageAddr, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::DECZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    Byte value = ReadByte(zeroPageAddr);
    value--;

    WriteByte(zeroPageAddr, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::DECAbsolute()
{
    Word address = FetchWord();

    Byte value = ReadByte(address);
    value--;

    WriteByte(address, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::DECAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    Byte value = ReadByte(addr);
    value--;

    WriteByte(addr, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::BNE()
{
    int8_t offset = static_cast<int8_t>(FetchByte());

    if (!StatusFlags.Z)
    {
        m_PC += offset;
    }
}

void CPU6502::BEQ()
{
    int8_t offset = static_cast<int8_t>(FetchByte());

    if (StatusFlags.Z)
    {
        m_PC += offset;
    }
}

void CPU6502::BPL()
{
    int8_t offset = static_cast<int8_t>(FetchByte());

    if (!StatusFlags.N)
    {
        m_PC += offset;
    }
}

void CPU6502::BMI()
{
    int8_t offset = static_cast<int8_t>(FetchByte());

    if (StatusFlags.N)
    {
        m_PC += offset;
    }
}

void CPU6502::BVC()
{
    int8_t offset = static_cast<int8_t>(FetchByte());

    if (!StatusFlags.V)
    {
        m_PC += offset;
    }
}

void CPU6502::BVS()
{
    int8_t offset = static_cast<int8_t>(FetchByte());

    if (StatusFlags.V)
    {
        m_PC += offset;
    }
}

void CPU6502::BCC()
{
    int8_t offset = static_cast<int8_t>(FetchByte());

    if (!StatusFlags.C)
    {
        m_PC += offset;
    }
}

void CPU6502::BCS()
{
    int8_t offset = static_cast<int8_t>(FetchByte());

    if (StatusFlags.C)
    {
        m_PC += offset;
    }
}

void CPU6502::NOP()
{
    // Do nothing
}

void CPU6502::RTI() {}

void CPU6502::RTS() {}

void CPU6502::JSR() {}

void CPU6502::BRK() {}

void CPU6502::STAZeroPage()
{
    Byte zeroPageAddr = FetchByte();
    WriteByte(zeroPageAddr, m_A);
}

void CPU6502::STAZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;
    WriteByte(zeroPageAddr, m_A);
}

void CPU6502::STAAbsolute()
{
    Word storeAddr = FetchWord();
    WriteByte(storeAddr, m_A);
}

void CPU6502::STAAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;
    WriteByte(addr, m_A);
}

void CPU6502::STAAbsoluteY()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_Y;
    WriteByte(addr, m_A);
}

void CPU6502::STAIndirectX()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte((zeroPageAddr + m_X) & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + m_X + 1) & 0xFF);

    Word addr = (addrHighByte << 8) | addrLowByte;

    WriteByte(addr, m_A);
}

void CPU6502::STAIndirectY()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte(zeroPageAddr & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = ((addrHighByte << 8) | addrLowByte) + m_Y;

    WriteByte(addr, m_A);
}

void CPU6502::STXZeroPage()
{
    Byte zeroPageAddr = FetchByte();
    WriteByte(zeroPageAddr, m_X);
}

void CPU6502::STXZeroPageY()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_Y;
    WriteByte(zeroPageAddr, m_X);
}

void CPU6502::STXAbsolute()
{
    Word storeAddr = FetchWord();
    WriteByte(storeAddr, m_X);
}

void CPU6502::STYZeroPage()
{
    Byte zeroPageAddr = FetchByte();
    WriteByte(zeroPageAddr, m_Y);
}

void CPU6502::STYZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;
    WriteByte(zeroPageAddr, m_Y);
}

void CPU6502::STYAbsolute()
{
    Word storeAddr = FetchWord();
    WriteByte(storeAddr, m_Y);
}

void CPU6502::ANDImmediate()
{
    m_A &= FetchByte();

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDZeroPage()
{
    Byte zeroPageAddr = FetchByte();

    m_A &= ReadByte(zeroPageAddr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    m_A &= ReadByte(zeroPageAddr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDAbsolute()
{
    Word address = FetchWord();
    m_A &= ReadByte(address);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    m_A &= ReadByte(addr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDAbsoluteY()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_Y;

    m_A &= ReadByte(addr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDIndirectX()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte((zeroPageAddr + m_X) & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + m_X + 1) & 0xFF);

    Word addr = (addrHighByte << 8) | addrLowByte;

    m_A &= ReadByte(addr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDIndirectY()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte(zeroPageAddr & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = ((addrHighByte << 8) | addrLowByte) + m_Y;

    m_A &= ReadByte(addr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAImmediate()
{
    m_A |= FetchByte();

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAZeroPage()
{
    Byte zeroPageAddr = FetchByte();

    m_A |= ReadByte(zeroPageAddr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    m_A |= ReadByte(zeroPageAddr);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAAbsolute()
{
    Word address = FetchWord();

    m_A |= ReadByte(address);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word address = baseAddr + m_X;

    m_A |= ReadByte(address);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAAbsoluteY()
{
    Word baseAddr = FetchWord();
    Word address = baseAddr + m_Y;

    m_A |= ReadByte(address);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAIndirectX()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte((zeroPageAddr + m_X) & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + m_X + 1) & 0xFF);

    Word address = (addrHighByte << 8) | addrLowByte;

    m_A |= ReadByte(address);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAIndirectY()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte(zeroPageAddr & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word address = ((addrHighByte << 8) | addrLowByte) + m_Y;

    m_A |= ReadByte(address);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ASLAccumulator()
{
    StatusFlags.C = (m_A & 0b10000000) > 0;

    m_A <<= 1;

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::ASLZeroPage()
{
    Byte zeroPageAddr = FetchByte();
    Byte value = ReadByte(zeroPageAddr);

    StatusFlags.C = (value & 0b10000000) > 0;

    value <<= 1;

    WriteByte(zeroPageAddr, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::ASLZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    Byte value = ReadByte(zeroPageAddr);

    StatusFlags.C = (value & 0b10000000) > 0;

    value <<= 1;

    WriteByte(zeroPageAddr, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::ASLAbsolute()
{
    Word address = FetchWord();
    Byte value = ReadByte(address);

    StatusFlags.C = (value & 0b10000000) > 0;

    value <<= 1;

    WriteByte(address, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::ASLAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word address = baseAddr + m_X;

    Byte value = ReadByte(address);

    StatusFlags.C = (value & 0b10000000) > 0;

    value <<= 1;

    WriteByte(address, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::LSRAccumulator()
{
    StatusFlags.C = (m_A & 0b00000001) > 0;

    m_A >>= 1;

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = 0;
}

void CPU6502::LSRZeroPage()
{
    Byte zeroPageAddr = FetchByte();
    Byte value = ReadByte(zeroPageAddr);

    StatusFlags.C = (value & 0b00000001) > 0;

    value >>= 1;

    WriteByte(zeroPageAddr, value);

    StatusFlags.Z = (value = 0);
    StatusFlags.N = 0;
}

void CPU6502::LSRZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    Byte value = ReadByte(zeroPageAddr);

    StatusFlags.C = (value & 0b00000001) > 0;

    value >>= 1;

    WriteByte(zeroPageAddr, value);

    StatusFlags.Z = (value = 0);
    StatusFlags.N = 0;
}

void CPU6502::LSRAbsolute()
{
    Byte addr = FetchByte();
    Byte value = ReadByte(addr);

    StatusFlags.C = (value & 0b00000001) > 0;

    value >>= 1;

    WriteByte(addr, value);

    StatusFlags.Z = (value = 0);
    StatusFlags.N = 0;
}

void CPU6502::LSRAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    Byte value = ReadByte(addr);

    StatusFlags.C = (value & 0b00000001) > 0;

    value >>= 1;

    WriteByte(addr, value);

    StatusFlags.Z = (value = 0);
    StatusFlags.N = 0;
}

void CPU6502::ADCImmediate()
{
    Byte value = FetchByte();
    AddWithCarry(value);
}

void CPU6502::ADCZeroPage()
{
    Byte zeroPageAddr = FetchByte();

    Byte value = ReadByte(zeroPageAddr);
    AddWithCarry(value);
}

void CPU6502::ADCZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    Byte value = ReadByte(zeroPageAddr);
    AddWithCarry(value);
}

void CPU6502::ADCAbsolute()
{
    Word addr = FetchWord();

    Byte value = ReadByte(addr);
    AddWithCarry(value);
}

void CPU6502::ADCAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    Byte value = ReadByte(addr);
    AddWithCarry(value);
}

void CPU6502::ADCAbsoluteY()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_Y;

    Byte value = ReadByte(addr);
    AddWithCarry(value);
}

void CPU6502::ADCIndirectX()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte((zeroPageAddr + m_X) & 0XFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + m_X + 1) & 0XFF);

    Word addr = (addrHighByte << 8) | addrLowByte;

    Byte value = ReadByte(addr);
    AddWithCarry(value);
}

void CPU6502::ADCIndirectY()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte(zeroPageAddr & 0XFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + 1) & 0XFF);

    Word addr = ((addrHighByte << 8) | addrLowByte) + m_Y;

    Byte value = ReadByte(addr);
    AddWithCarry(value);
}

void CPU6502::AddWithCarry(const Byte value)
{
    Word sum = m_A + value + StatusFlags.C;

    StatusFlags.C = (sum > 0xFF);
    StatusFlags.V = (~(m_A ^ value) & (m_A ^ sum) & 0x80) != 0;

    m_A = static_cast<Byte>(sum);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::SBCImmediate()
{
    Byte value = FetchByte();
    SubtractWithBorrow(value);
}

void CPU6502::SBCZeroPage()
{
    Byte addr = FetchByte();

    Byte value = ReadByte(addr);
    SubtractWithBorrow(value);
}

void CPU6502::SBCZeroPageX()
{
    Byte addr = (FetchByte() + m_X) & 0xFF;

    Byte value = ReadByte(addr);
    SubtractWithBorrow(value);
}

void CPU6502::SBCAbsolute()
{
    Word addr = FetchWord();
    Byte value = ReadByte(addr);

    SubtractWithBorrow(value);
}

void CPU6502::SBCAbsoluteX()
{
    Word addr = FetchWord() + m_X;

    Byte value = ReadByte(addr);
    SubtractWithBorrow(value);
}

void CPU6502::SBCAbsoluteY()
{
    Word addr = FetchWord() + m_Y;

    Byte value = ReadByte(addr);
    SubtractWithBorrow(value);
}

void CPU6502::SBCIndirectX()
{
    Byte zeroPageAddr = (FetchByte() + m_X) & 0xFF;

    Byte lowByteAddr = ReadByte(zeroPageAddr);
    Byte hightByteAddr = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = (hightByteAddr << 8) | lowByteAddr;

    Byte value = ReadByte(addr);
    SubtractWithBorrow(value);
}

void CPU6502::SBCIndirectY()
{
    Byte zeroPageAddr = FetchByte();

    Byte lowByteAddr = ReadByte(zeroPageAddr);
    Byte highByteAddr = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = ((highByteAddr << 8) | lowByteAddr) + m_Y;

    Byte value = ReadByte(addr);
    SubtractWithBorrow(value);
}

void CPU6502::SubtractWithBorrow(const Byte value)
{
    Word result = m_A + (~value) + StatusFlags.C;

    StatusFlags.C = (result > 0xFF);
    StatusFlags.V = ((m_A ^ value) & (m_A ^ result) & 0x80) != 0;

    m_A = static_cast<Byte>(result);

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0x80) != 0;
}

void CPU6502::TAX()
{
    m_X = m_A;

    StatusFlags.Z = (m_X == 0);
    StatusFlags.N = (m_X & 0b10000000) > 0;
}

void CPU6502::TAY()
{
    m_Y = m_A;

    StatusFlags.Z = (m_Y == 0);
    StatusFlags.N = (m_Y & 0b10000000) > 0;
}

void CPU6502::TXA()
{
    m_A = m_X;

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::TYA()
{
    m_A = m_Y;

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0b10000000) > 0;
}

void CPU6502::EORImmediate()
{
    Byte value = FetchByte();
    ExclusiveOR(value);
}

void CPU6502::EORZeroPage()
{
    Byte addr = FetchByte();

    Byte value = ReadByte(addr);
    ExclusiveOR(value);
}

void CPU6502::EORZeroPageX()
{
    Byte addr = (FetchByte() + m_X) & 0xFF;

    Byte value = ReadByte(addr);
    ExclusiveOR(value);
}

void CPU6502::EORAbsolute()
{
    Word addr = FetchWord();

    Byte value = ReadByte(addr);
    ExclusiveOR(value);
}

void CPU6502::EORAbsoluteX()
{
    Word addr = FetchWord() + m_X;

    Byte value = ReadByte(addr);
    ExclusiveOR(value);
}

void CPU6502::EORAbsoluteY()
{
    Word addr = FetchWord() + m_Y;

    Byte value = ReadByte(addr);
    ExclusiveOR(value);
}

void CPU6502::EORIndirectX()
{
    Byte zeroPageAddr = (FetchByte() + m_X) & 0xFF;

    Byte lowByteAddr = ReadByte(zeroPageAddr);
    Byte highByteAddr = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = (highByteAddr << 8) | lowByteAddr;

    Byte value = ReadByte(addr);
    ExclusiveOR(value);
}

void CPU6502::EORIndirectY()
{
    Byte zeroPageAddr = FetchByte();

    Byte lowByteAddr = ReadByte(zeroPageAddr);
    Byte highByteAddr = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = ((highByteAddr << 8) | lowByteAddr) + m_Y;

    Byte value = ReadByte(addr);
    ExclusiveOR(value);
}

void CPU6502::ExclusiveOR(const Byte value)
{
    m_A ^= value;

    StatusFlags.Z = (m_A == 0);
    StatusFlags.N = (m_A & 0x80) != 0;
}

void CPU6502::CMPImmediate()
{
    Byte value = FetchByte();
    Compare(m_A, value);
}

void CPU6502::CMPZeroPage()
{
    Byte addr = FetchByte();

    Byte value = ReadByte(addr);
    Compare(m_A, value);
}

void CPU6502::CMPZeroPageX()
{
    Byte addr = (FetchByte() + m_X) & 0xFF;

    Byte value = ReadByte(addr);
    Compare(m_A, value);
}

void CPU6502::CMPAbsolute()
{
    Word addr = FetchWord();

    Byte value = ReadByte(addr);
    Compare(m_A, value);
}

void CPU6502::CMPAbsoluteX()
{
    Word addr = FetchWord() + m_X;

    Byte value = ReadByte(addr);
    Compare(m_A, value);
}

void CPU6502::CMPAbsoluteY()
{
    Word addr = FetchWord() + m_Y;

    Byte value = ReadByte(addr);
    Compare(m_A, value);
}

void CPU6502::CMPIndirectX()
{
    Byte zeroPageAddr = (FetchByte() + m_X) & 0xFF;

    Byte lowByteAddr = ReadByte(zeroPageAddr);
    Byte highByteAddr = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = (highByteAddr << 8) | lowByteAddr;

    Byte value = ReadByte(addr);
    Compare(m_A, value);
}

void CPU6502::CMPIndirectY()
{
    Byte zeroPageAddr = FetchByte();

    Byte lowByteAddr = ReadByte(zeroPageAddr);
    Byte highByteAddr = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = ((highByteAddr << 8) | lowByteAddr) + m_Y;

    Byte value = ReadByte(addr);
    Compare(m_A, value);
}

void CPU6502::Compare(const Byte registerValue, const Byte value)
{
    Byte result = registerValue - value;

    StatusFlags.C = (registerValue >= value);
    StatusFlags.Z = (result == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::INCZeroPage()
{
    Byte addr = FetchByte();
    Byte value = ReadByte(addr);
    value++;

    WriteByte(addr, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::INCZeroPageX()
{
    Byte addr = (FetchByte() + m_X) & 0xFF;
    Byte value = ReadByte(addr);
    value++;

    WriteByte(addr, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::INCAbsolute()
{
    Word addr = FetchWord();
    Byte value = ReadByte(addr);
    value++;

    WriteByte(addr, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::INCAbsoluteX()
{
    Word addr = FetchWord() + m_X;
    Byte value = ReadByte(addr);
    value++;

    WriteByte(addr, value);

    StatusFlags.Z = (value == 0);
    StatusFlags.N = (value & 0b10000000) > 0;
}

void CPU6502::InvalidOpcode()
{
    EMULATOR_6502_ERROR(TEXT("Invalid opcode: 0x{:02X} at PC: 0x{:04X}", ReadByte(m_PC), m_PC));
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
