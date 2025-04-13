#pragma once

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include "../Assembler/Assembler.h"
#include "../Components/Editor/Editor.h"
#include "../Components/MemoryLayout/MemoryLayout.h"
#include "../Components/PixelDisplay/PixelDisplay.h"
#include "../Core/CPU6502.h"
#include "../Core/Memory.h"
#include "../Disassembler/Dissasembler.h"

namespace emulator6502
{

using Byte = uint8_t;
using Word = uint16_t;

class Emulator6502
{
  public:
    Emulator6502() = default;

    void Init();
    void Run();
    void Shutdown();

  private:
    void Reset();

    void LoadProgramIntoMemory();
    std::vector<Byte> ReadProgramFromMemory();

  private:
    void Render();

    void RenderButtons();
    void RenderProcessorsRegisterStatus();

    void RenderDissasemblyPopup();

    void OpenDissasemblyPopup();

  private:
    GLFWwindow *m_Window;
    CPU6502 m_CPU;

    std::unique_ptr<Assembler> m_Assembler = std::make_unique<Assembler>();
    std::unique_ptr<Disassembler> m_Disssembler = std::make_unique<Disassembler>();

    std::unique_ptr<Editor> m_AsmEditor = std::make_unique<Editor>();
    std::unique_ptr<PixelDisplay> m_PixelDisplay = std::make_unique<PixelDisplay>();
    std::unique_ptr<MemoryLayout> m_MemoryLayout = std::make_unique<MemoryLayout>();

    std::vector<std::string> m_Dissasembly;
    bool m_ShowDisassemblyPopup = false;
};
} // namespace emulator6502