#pragma once

#include <vector>
#include <string>

namespace emulator6502
{
	class Dissasembler
	{
		using Byte = uint8_t;
		using Word = uint16_t;

      public:
        Dissasembler() = default;

        std::vector<std::string> Disassmble(const std::vector<Byte> &machineCode);
	};
}
