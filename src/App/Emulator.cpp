#include "Emulator.h"

namespace emulator6502
{
void Emulator6502::Init()
{
    Memory::Init();
    m_CPU.Reset();

    glfwInit();
    m_Window = glfwCreateWindow(800, 600, "6502 Emulator", NULL, NULL);
    glfwMakeContextCurrent(window);
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void Emulator6502::Run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        RenderUI();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_Window);
    }
}

void Emulator6502::Shutdown()
{
    m_CPU.Reset();
    Memory::Reset();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Emulator6502::RenderUI()
{
    ImGui::Begin("6502 Emulator");
    ImGui::Text(m_CPU.ToString());
    mem_edit.DrawWindow("Memory Editor", Memory::RAM, 65536);

    static char asm_code[1024] = "";
    ImGui::InputTextMultiline("Code", asm_code, sizeof(asm_code));

    if (ImGui::Button("Assemble"))
    {
        // TODO: Implement assembler
    }

    if (ImGui::Button("Disasemble"))
    {
        // TODO: Implement disasemble
    }

    if (ImGui::Button("Run"))
    {
        // TODO: Implement execution
    }
}

} // namespace emulator6502
