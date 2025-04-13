#include "Dissasembler.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>

namespace emulator6502
{

static const std::unordered_map<Byte, DisassembledInstruction> disassemblyTable = {
    {0xA9, {"LDA #", 1}}, {0xAD, {"LDA $", 2}}, {0x8D, {"STA $", 2}}, {0xA2, {"LDX #", 1}},
    {0xAE, {"LDX $", 2}}, {0x8E, {"STX $", 2}}, {0xA0, {"LDY #", 1}}, {0xAC, {"LDY $", 2}},
    {0x8C, {"STY $", 2}}, {0x69, {"ADC #", 1}}, {0x6D, {"ADC $", 2}}, {0xE9, {"SBC #", 1}},
    {0xED, {"SBC $", 2}}, {0xE8, {"INX", 0}},   {0xC8, {"INY", 0}},   {0xCA, {"DEX", 0}},
    {0x88, {"DEY", 0}},   {0xEA, {"NOP", 0}},   {0x00, {"BRK", 0}}};

std::vector<std::string> Dissasembler::Disassmble(const std::vector<Byte> &machineCode)
{
    std::vector<std::string> assembly;
    size_t programCounter = 0;

    while (programCounter < machineCode.size())
    {
        Byte opcode = machineCode[programCounter];
        std::stringstream ss;

        ss << std::hex << std::setw(4) << std::setfill('0') << static_cast<int32_t>(programCounter) << ": ";

        if (auto it = disassemblyTable.find(opcode); it != disassemblyTable.end())
        {
            const DisassembledInstruction &instruction = it->second;
            ss << instruction.mnemonic;

            appendOperands(ss, machineCode, programCounter, instruction.operandSize);
        }
        else
        {
            ss << "??? (0x" << std::hex << std::setw(2);
            ss << std::setfill('0') << static_cast<int32_t>(opcode) << ")";

            programCounter += 1;
        }

        assembly.push_back(ss.str());
    }

    return assembly;
}
void Dissasembler::appendOperands(std::stringstream &ss, const std::vector<Byte> &machineCode,
                                  std::size_t &programCounter, Byte operandSize)
{
    if (operandSize == 1 && (programCounter + 1 < machineCode.size()))
    {
        Byte operand = machineCode[programCounter + 1];
        ss << "$" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int32_t>(operand);
        programCounter += 2;
    }
    else if (operandSize == 2 && (programCounter + 2 < machineCode.size()))
    {
        Word address = static_cast<Word>(machineCode[programCounter + 1]) |
                       (static_cast<Word>(machineCode[programCounter + 2]) << 8);
        ss << "$" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int32_t>(address);
        programCounter += 3;
    }
    else
    {
        programCounter += 1;
    }
}
} // namespace emulator6502
