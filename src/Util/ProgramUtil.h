#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <vector>
#include <string>
#include <memory>

#include "../Core/Memory.h"
#include "../Assembler/Assembler.h"

namespace emulator6502
{
	class ProgramUtil
	{
      public:
        //////////////////////////////////////////////////////////////
        ///
        /// @brief Deleted default constructor to prevent instantiation.
        ///        Utility class.
        ///
        //////////////////////////////////////////////////////////////
        ProgramUtil() = delete;

        static void LoadProgramIntoMemory(const std::string &asmCode, const std::unique_ptr<Assembler> &assembler);
        static std::vector<Byte> ReadProgramFromMemory();
	};
}