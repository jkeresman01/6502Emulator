#include "Assembler.h"

#include <string>
#include <sstream>
#include <iostream>
#include <unordered_map>

namespace emulator6502
{

static const std::unordered_map<std::string, Instruction> instructionSetLookupTable = {
    {"LDA #", {0xA9, 1}}, 
    {"LDA $", {0xAD, 2}}, 
    {"STA $", {0x8D, 2}}, 
    {"LDX #", {0xA2, 1}}, 
    {"LDX $", {0xAE, 2}}, 
    {"STX $", {0x8E, 2}},
    {"LDY #", {0xA0, 1}}, 
    {"LDY $", {0xAC, 2}}, 
    {"STY $", {0x8C, 2}},
    {"ADC #", {0x69, 1}}, 
    {"ADC $", {0x6D, 2}},
    {"SBC #", {0xE9, 1}},
    {"SBC $", {0xED, 2}}, 
    {"INX", {0xE8, 0}},  
    {"INY", {0xC8, 0}}, 
    {"DEX", {0xCA, 0}},  
    {"DEY", {0x88, 0}},   
    {"NOP", {0xEA, 0}}
};

std::vector<uint8_t> Assembler::Assemble(const std::string &asmCode)
{
    std::vector<uint8_t> machineCode;
    std::stringstream ss(asmCode);
    std::string line;

    while (std::getline(ss, line))
    {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        size_t commentPosition = line.find(';');
        if (commentPosition != std::string::npos)
        {
            line = line.substr(0, commentPosition);
            line.erase(line.find_last_not_of(" \t") + 1);
        }

        if (line.empty())
        {
            continue;
        }

        size_t spacePos = line.find(' ');

        std::string mnemonic = (spacePos == std::string::npos) ? line : line.substr(0, spacePos + 2);
        std::string operand = (spacePos == std::string::npos) ? "" : line.substr(spacePos + 2);


        if (auto it = instructionSetLookupTable.find(mnemonic); it != instructionSetLookupTable.end())
        {
            const auto &instruction = it->second;
            machineCode.push_back(instruction.opcode);
            appendOperands(machineCode, operand, instruction.operandSize);
        }
    }
    return machineCode;
}

void Assembler::appendOperands(std::vector<uint8_t> &machineCode, const std::string &operand,
                            uint8_t operandSize)
{
    if (operandSize == 1)
    {
        machineCode.push_back(static_cast<uint8_t>(std::stoi(operand, nullptr, 16)));
    }

    if (operandSize == 2)
    {
        uint16_t address = static_cast<uint16_t>(std::stoi(operand, nullptr, 16));

        uint8_t lowByte = address & 0xFF;
        uint8_t highByte = (address >> 8) & 0xFF;

        machineCode.push_back(lowByte);
        machineCode.push_back(highByte);
    }
}
}