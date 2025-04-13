#pragma once

namespace emulator6502
{
	class Dissasembler
	{
      public:
        Dissasembler() = default;

        std::vector<std::string> Dissasmble(const std::vector<Byte> &machineCode);
	};
}