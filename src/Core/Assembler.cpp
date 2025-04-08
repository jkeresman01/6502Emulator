#include "Assembler.h"

#include <string>
#include <sstream>

namespace emulator6502
{
	std::vector<uint8_t> Assembler::Assemble(const std::string& asmCode)
	{
        std::vector<uint8_t> machineCode;

        std::stringstream ss(asmCode);
        std::string line;

        while (std::getline(ss, line))
        {
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);

            if (line.substr(0, 3) == "LDA")
            {
                if (line[4] == '#')
                {
                    uint8_t value = std::stoi(line.substr(5), nullptr, 16);
                    machineCode.push_back(0xA9);
                    machineCode.push_back(value);
                }
            }
            else if (line.substr(0, 3) == "STA")
            {
                if (line[4] == '$')
                {
                    uint16_t address = std::stoi(line.substr(5), nullptr, 16);
                    machineCode.push_back(0x8D);
                    machineCode.push_back(address & 0xFF);
                    machineCode.push_back((address >> 8) & 0xFF);
                }
            }
        }

        return machineCode;
	}
}