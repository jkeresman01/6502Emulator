#include "Emulator.h"

#include <vector>

namespace emulator6502
{

constexpr int64_t BUFFER_SIZE = 8192;
static char asmCode[BUFFER_SIZE] = "";

void Emulator6502::Init()
{
    Memory::Init();
    m_CPU.Reset();

    glfwInit();
    m_Window = glfwCreateWindow(1000, 700, "6502 Emulator", NULL, NULL);
    glfwMakeContextCurrent(m_Window);
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
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
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Emulator6502::RenderUI()
{
    ImGui::Begin("6502 Emulator");

    int width, height;
    glfwGetWindowSize(m_Window, &width, &height);

    ImGui::SetWindowSize(ImVec2((float)width, (float)height));

    ImGui::Columns(2, "MainColumns", true);

    ImGui::Text("Assembly Editor:");
    ImGui::Separator();
    ImGui::InputTextMultiline("##Editor", asmCode, sizeof(asmCode), ImVec2(-FLT_MIN, 300));

    if (ImGui::Button("Assemble"))
    {
        // TODO: Implement assembler
    }

    ImGui::SameLine();
    if (ImGui::Button("Disassemble"))
    {
        // TODO: Implement disassembler
    }

    ImGui::SameLine();
    if (ImGui::Button("Run"))
    {
        // TODO: Implement execution
    }

    ImGui::NextColumn();

    ImGui::Text("Memory Viewer:");
    ImGui::Separator();

    ImGui::BeginChild("Memory", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

    // Display RAM (Hex Viewer)
    for (int i = 0; i < MEMORY_64KB; i += 16)
    {
        char address[16];
        sprintf(address, "%04X: ", i);
        ImGui::TextUnformatted(address);
        ImGui::SameLine();

        for (int j = 0; j < 16; ++j)
        {
            ImGui::SameLine();
            char byteText[4];
            sprintf(byteText, "%02X", Memory::s_RAM[i + j]);
            ImGui::TextUnformatted(byteText);
        }
    }

    ImGui::EndChild();
    ImGui::Columns(1);

    ImGui::End();
}
} // namespace emulator6502
