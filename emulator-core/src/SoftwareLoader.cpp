#include <emulator/core/SoftwareLoader.h>

namespace emulator6502
{

void SoftwareLoader::Load(const std::vector<Byte> &machineCode)
{
    for (size_t i = 0; i < machineCode.size(); ++i)
    {
        Memory::s_RAM[0x8000 + i] = machineCode[i];
    }
}

} // namespace emulator6502
