#pragma once

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "../Core/CPU6502.h"
#include "../Core/Memory.h"

#include "imgui_memory_editor.h"

namespace emulator6502
{
class Emulator6502
{
  public:
    Emulator6502() = default;

    void Init();
    void Run();
    void Shutdown();

  private:
    void RenderUI();

  private:
    GLFWwindow *m_Window;
    MemoryEditor m_MemoryEditor;
    CPU6502 m_CPU;
};
} // namespace emulator6502
