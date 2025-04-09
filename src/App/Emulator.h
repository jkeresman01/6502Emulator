#pragma once

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include "../Core/Assembler.h"
#include "../Core/CPU6502.h"
#include "../Core/Memory.h"

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
    void LoadProgramIntoMemory(const std::string &asmCode);

  private:
    void RenderUI();

    void RenderMemoryLayout();
    void RenderAsmEditor();
    void RenderPixelDisplay();
    void RenderButtons();
    void RenderProcessRegisterStatus();

  private:
    GLFWwindow *m_Window;
    CPU6502 m_CPU;
    std::unique_ptr<Assembler> m_Assembler = std::make_unique<Assembler>();
};
} // namespace emulator6502
