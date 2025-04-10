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

    case 0x85:
        STAZeroPage();
        break;

    case 0x95:
        STAZeroPageX();
        break;

    case 0x8D:
        STAAbsolute();
        break;
        
    case 0x9D:
        STAAbsoluteX();
        break;
                
    case 0x99:
        STAAbsoluteY();
        break;
                        
    case 0x81:
        STAIndirectX();
        break;
                                
    case 0x91:
        STAIndirectY();
        break;

    case 0x18:
        CLC();
        break;

    case 0xD8:
        CLD();
        break;

    case 0x58:
        CLI();
        break;

    case 0xB8:
        CLV();
        break;

    case 0xCA:
        DEX();
        break;

    case 0x88:
        DEY();
        break;

    case 0xA2:
        LDXImmediate();
        break;

    case 0xA6:
        LDXZeroPage();
        break;

    case 0xB6:
        LDXZeroPageY();
        break;

    case 0xAE:
        LDXAbsoulute();
        break;

    case 0xBE:
        LDAAbsouluteY();
        break;

    case 0xA0:
        LDYImmediate();
        break;

    case 0xA4:
        LDYZeroPage();
        break;

    case 0xB4:
        LDYZeroPageX();
        break;

    case 0xAC:
        LDYAbsoulute();
        break;

    case 0xBC:
        LDYAbsouluteX();
        break;

    case 0xC6:
        DECZeroPage();
        break;

    case 0xD6:
        DECZeroPageX();
        break;

    case 0xCE:
        DECAbsoulute();
        break;

    case 0xDE:
        DECAbsouluteX();
        break;

    case 0x86:
        STXZeroPage();
        break;

    case 0x9E:
        STAZeroPageX();
        break;

    case 0x8E:
        STAAbsolute();
        break;

    case 0x84:
        STYZeroPage();
        break;

    case 0x94:
        STYZeroPageX();
        break;

    case 0x8C:
        STYAbsolute();
        break;

    case 0x29:
        ANDImmediate();
        break;

    case 0x25:
        ANDZeroPage();
        break;
        
    case 0x35:
        ANDZeroPageX();
        break;

    case 0x2D:
        ANDAbsolute();
        break;

    case 0x3D:
        ANDAbsoluteX();
        break;

    case 0x39:
        ANDAbsoluteY();
        break;
        
    case 0x20:
        ORAImmediate();
        break;

    case 0x05:
        ORAZeroPage();
        break;
        
    case 0x15:
        ORAZeroPageX();
        break;

    case 0x0D:
        ORAAbsolute();
        break;

    case 0x1D:
        ORAAbsoluteX();
        break;

    case 0x19:
        ORAAbsoluteY();
        break;
        
    case 0x01:
        ORAIndirectX();
        break;
        
    case 0x11:
        ORAIndirectY();
        break;

    case 0x16:
        ASLZeroPageX();
        break;

    case 0x0E:
        ASLAbsolute();
        break;

    case 0x1E:
        ASLAbsoluteX();
        break;
               
    case 0x4A:
        LSRAccumulator();
        break;
        
    case 0x46:
        LSRZeroPage();
        break;

    case 0x56:
        LSRZeroPageX();
        break;

    case 0x4E:
        LSRAbsolute();
        break;

    case 0x5E:
        LSRAbsoluteX();
        break;

    case 0xEA:
        NOP();
        break;

    case 0xB:
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

void CPU6502::LDXImmediate()
{
    m_X = FetchByte();

    Z = (m_X == 0);
    N = (m_X & 0b10000000) > 0;
}

void CPU6502::LDXZeroPage()
{
    Byte zeroPageAddr = FetchByte();

    m_X = ReadByte(zeroPageAddr);

    Z = (m_X == 0);
    N = (m_X & 0b10000000) > 0;
}

void CPU6502::LDXZeroPageY()
{
    Byte zeroPageAddr = FetchByte();

    zeroPageAddr += m_Y;

    m_X = ReadByte(zeroPageAddr);

    Z = (m_X == 0);
    N = (m_X & 0b10000000) > 0;
}

void CPU6502::LDXAbsoulute()
{
    Word address = FetchWord();

    m_X = ReadByte(address);

    Z = (m_X == 0);
    N = (m_X & 0b10000000) > 0;
}

void CPU6502::LDXAbsouluteY()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_Y;

    m_X = ReadByte(addr);

    Z = (m_X == 0);
    N = (m_X & 0b10000000) > 0;
}

void CPU6502::LDYImmediate()
{
    m_Y = FetchByte();

    Z = (m_Y == 0);
    N = (m_Y & 0b10000000) > 0;
}

void CPU6502::LDYZeroPage()
{
    Byte zeroPageAddr = FetchByte();

    m_Y = ReadByte(zeroPageAddr);

    Z = (m_Y == 0);
    N = (m_Y & 0b10000000) > 0;
}

void CPU6502::LDYZeroPageX()
{
    Byte zeroPageAddr = FetchByte();

    zeroPageAddr += m_X;

    m_Y = ReadByte(zeroPageAddr);

    Z = (m_Y == 0);
    N = (m_Y & 0b10000000) > 0;
}

void CPU6502::LDYAbsoulute()
{
    Word address = FetchWord();

    m_Y = ReadByte(address);

    Z = (m_Y == 0);
    N = (m_Y & 0b10000000) > 0;
}

void CPU6502::LDYAbsouluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    m_Y = ReadByte(addr);

    Z = (m_Y == 0);
    N = (m_Y & 0b10000000) > 0;
}

void CPU6502::CLC()
{
    C = 0;
}

void CPU6502::CLD()
{
    D = 0;
}

void CPU6502::CLI()
{
    I = 0;
}

void CPU6502::CLV()
{
    V = 0;
}

void CPU6502::DEX()
{
    m_X--;

    Z = (m_X == 0);
    N = (m_X & 0b10000000) > 0;
}

void CPU6502::DEY()
{
    m_Y--;

    Z = (m_Y == 0);
    N = (m_Y & 0b10000000) > 0;
}

void CPU6502::DECZeroPage()
{
    Byte zeroPageAddr = FetchByte();

    Byte value = ReadByte(zeroPageAddr);
    value--;

    WriteByte(zeroPageAddr, value);

    Z = (value == 0);
    N = (value & 0b10000000) > 0;
}

void CPU6502::DECZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    Byte value = ReadByte(zeroPageAddr);
    value--;

    WriteByte(zeroPageAddr, value);

    Z = (value == 0);
    N = (value & 0b10000000) > 0;
}

void CPU6502::DECAbsoulute()
{
    Word address = FetchWord();

    Byte value = ReadByte(address);
    value--;

    WriteByte(address, value);

    Z = (value == 0);
    N = (value & 0b10000000) > 0;
}

void CPU6502::DECAbsouluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    Byte value = ReadByte(addr);
    value--;

    WriteByte(addr, value);

    Z = (value == 0);
    N = (value & 0b10000000) > 0;
}

void CPU6502::NOP()
{
    // Do nothing
}

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
    
    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDZeroPage() 
{
    Byte zeroPageAddr = FetchByte();
    
    m_A &= ReadByte(zeroPageAddr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    m_A &= ReadByte(zeroPageAddr);
    
    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDAbsolute()
{
    Word address = FetchWord();
    m_A &= ReadByte(address);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    m_A &= ReadByte(addr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDAbsoluteY()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_Y;

    m_A &= ReadByte(addr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDIndirectX()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte((zeroPageAddr + m_X) & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + m_X + 1) & 0xFF);

    Word addr = (addrHighByte << 8) | addrLowByte;

    m_A &= ReadByte(addr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ANDIndirectY() 
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte(zeroPageAddr & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word addr = ((addrHighByte << 8) | addrLowByte) + m_Y;

    m_A &= ReadByte(addr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAImmediate() 
{
    m_A |= FetchByte();

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAZeroPage() 
{
    Byte zeroPageAddr = FetchByte();

    m_A |= ReadByte(zeroPageAddr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAZeroPageX() 
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    m_A |= ReadByte(zeroPageAddr);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAAbsolute() 
{
    Word address = FetchWord();

    m_A |= ReadByte(address);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAAbsoluteX() 
{
    Word baseAddr = FetchWord();
    Word address = baseAddr + m_X;

    m_A |= ReadByte(address);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAAbsoluteY() 
{
    Word baseAddr = FetchWord();
    Word address = baseAddr + m_Y;

    m_A |= ReadByte(address);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAIndirectX() 
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte((zeroPageAddr + m_X) & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + m_X + 1) & 0xFF);

    Word address = (addrHighByte << 8) | addrLowByte;

    m_A |= ReadByte(address);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ORAIndirectY()
{
    Byte zeroPageAddr = FetchByte();

    Byte addrLowByte = ReadByte(zeroPageAddr & 0xFF);
    Byte addrHighByte = ReadByte((zeroPageAddr + 1) & 0xFF);

    Word address = ((addrHighByte << 8) | addrLowByte) + m_Y;

    m_A |= ReadByte(address);

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ASLAccumulator() 
{
    C = (m_A & 0b10000000) > 0;

    m_A <<= 1;

    Z = (m_A == 0);
    N = (m_A & 0b10000000) > 0;
}

void CPU6502::ASLZeroPage()
{
    Byte zeroPageAddr = FetchByte();
    Byte value = ReadByte(zeroPageAddr);

    C = (value & 0b10000000) > 0;

    value <<= 1;

    WriteByte(zeroPageAddr, value);

    Z = (value == 0);
    N = (value & 0b10000000) > 0;
}

void CPU6502::ASLZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    Byte value = ReadByte(zeroPageAddr);

    C = (value & 0b10000000) > 0;
    
    value <<= 1;

    WriteByte(zeroPageAddr, value);
    
    Z = (value == 0);
    N = (value & 0b10000000) > 0;
}

void CPU6502::ASLAbsolute() 
{
    Word address = FetchWord();
    Byte value = ReadByte(address);

    C = (value & 0b10000000) > 0;

    value <<= 1;

    WriteByte(address, value);

    Z = (value == 0);
    N = (value & 0b10000000) > 0;
}

void CPU6502::ASLAbsoluteX() 
{
    Word baseAddr = FetchWord();
    Word address = baseAddr + m_X;

    Byte value = ReadByte(address);

    C = (value & 0b10000000) > 0;
    
    value <<= 1;

    WriteByte(address, value);
    
    Z = (value == 0);
    N = (value & 0b10000000) > 0;
}

void CPU6502::LSRAccumulator() 
{
    C = (m_A & 0b00000001) > 9;

    m_A >>= 1;

    Z = (m_A == 0);
    N = 0;
}

void CPU6502::LSRZeroPage() 
{
    Byte zeroPageAddr = FetchByte();
    Byte value = ReadByte(zeroPageAddr);

    C = (value & 0b00000001) > 0;

    value >>= 1;

    WriteByte(zeroPageAddr, value);

    Z = (value = 0);
    N = 0;
}

void CPU6502::LSRZeroPageX()
{
    Byte zeroPageAddr = FetchByte();
    zeroPageAddr += m_X;

    Byte value = ReadByte(zeroPageAddr);

    C = (value & 0b00000001) > 0;

    value >>= 1;

    WriteByte(zeroPageAddr, value);

    Z = (value = 0);
    N = 0;
}

void CPU6502::LSRAbsolute() 
{
    Byte addr = FetchByte();
    Byte value = ReadByte(addr);

    C = (value & 0b00000001) > 0;

    value >>= 1;

    WriteByte(addr, value);

    Z = (value = 0);
    N = 0;
}

void CPU6502::LSRAbsoluteX()
{
    Word baseAddr = FetchWord();
    Word addr = baseAddr + m_X;

    Byte value = ReadByte(addr);

    C = (value & 0b00000001) > 0;

    value >>= 1;

    WriteByte(addr, value);

    Z = (value = 0);
    N = 0;
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
