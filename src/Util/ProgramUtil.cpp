#include "ProgramUtil.h"

namespace emulator6502
{

std::vector<Byte> ProgramUtil::ReadProgramFromMemory()
{
    std::vector<Byte> machineCode;

    size_t programCounter = 0x8000;
    const uint8_t lookaheadWindow = 3;
    bool isEndOfProgramReached = false;

    while (programCounter < MEMORY_64KB && !isEndOfProgramReached)
    {
        bool isThirdConsecutiveZero = true;

        if (programCounter + lookaheadWindow <= MEMORY_64KB)
        {
            for (size_t i = 0; i < lookaheadWindow; ++i)
            {
                if (Memory::Read(programCounter + i) != 0x00)
                {
                    isThirdConsecutiveZero = false;
                    break;
                }
            }

            if (isThirdConsecutiveZero)
            {
                isEndOfProgramReached = true;
                break;
            }
        }

        Byte byte = Memory::Read(programCounter);

        machineCode.push_back(byte);
        programCounter++;
    }

    return machineCode;
}

} // namespace emulator6502
