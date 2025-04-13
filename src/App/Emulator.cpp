#include "Emulator.h"

#include <vector>

#include "../Util/ColorsUtil.h"
#include "../Util/ProgramUtil.h"
#include "../Util/RandomUtil.h"

namespace emulator6502
{

constexpr int64_t BUFFER_SIZE = 8192;
static char asmCode[BUFFER_SIZE] = "";

void Emulator6502::Init()
{
    Random::Init();
    Reset();

    glfwInit();
    m_Window = glfwCreateWindow(1180, 840, "6502 Emulator", NULL, NULL);
    glfwMakeContextCurrent(m_Window);
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init();

    m_CPU.Init();
    m_AsmEditor->Init();
    m_MemoryLayout->Init();
    m_PixelDisplay->Init();
}

void Emulator6502::Run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_Window);
    }
}

void Emulator6502::Render()
{
    ImGui::Begin("6502 Emulator");

    int width, height;
    glfwGetWindowSize(m_Window, &width, &height);

    ImGui::SetWindowSize(ImVec2((float)width, (float)height));

    ImGui::Columns(2, "MainColumns", true);

    m_AsmEditor->Render();
    RenderButtons();

    m_PixelDisplay->Render();
    RenderProcessorsRegisterStatus();

    ImGui::NextColumn();
    m_MemoryLayout->Render();
    ImGui::Columns(1);

    ImGui::End();

    RenderDissasemblyPopup();
}

void Emulator6502::RenderProcessorsRegisterStatus()
{
    ImGui::Text("CPU Registers:");

    ImGui::Text("A  = 0x%02X", m_CPU.GetAccumulator());
    ImGui::Text("X  = 0x%02X", m_CPU.GetRegisterX());
    ImGui::Text("Y  = 0x%02X", m_CPU.GetRegisterY());
    ImGui::Text("SP = 0x%02X", m_CPU.GetStackPointer());
    ImGui::Text("PC = 0x%04X", m_CPU.GetProgramCounter());

    // TODO status flags
}

void Emulator6502::RenderDissasemblyPopup()
{
    if (m_ShowDisassemblyPopup)
    {
        ImGui::OpenPopup("Disassembly");
        m_ShowDisassemblyPopup = false;
    }

    if (ImGui::BeginPopupModal("Disassembly", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        for (const auto &line : m_Dissasembly)
        {
            ImGui::Text("%s", line.c_str());
        }

        if (ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void Emulator6502::RenderButtons()
{
    if (ImGui::Button("Assemble"))
    {
        Reset();
        LoadProgramIntoMemory();
    }

    ImGui::SameLine();
    if (ImGui::Button("Disassemble"))
    {
        //OpenDissasemblyPopup();
    }

    ImGui::SameLine();
    if (ImGui::Button("Run"))
    {
        // TODO: Implement execution
    }

    ImGui::SameLine();
    if (ImGui::Button("Reset"))
    {
        Reset();
    }

    ImGui::SameLine();
    if (ImGui::Button("Step"))
    {
        m_CPU.Step();
    }
}

void Emulator6502::OpenDissasemblyPopup()
{
    const std::vector<Byte> &machineCode = ProgramUtil::ReadProgramFromMemory();
    m_Dissasembly = m_Disssembler->Disassmble(machineCode);
    m_ShowDisassemblyPopup = true;

    RenderDissasemblyPopup();
}

void Emulator6502::LoadProgramIntoMemory()
{
    const std::string &asmCode = m_AsmEditor->GetText();
    ProgramUtil::LoadProgramIntoMemory(asmCode, m_Assembler);
}

void Emulator6502::Shutdown()
{
    m_AsmEditor->Destroy();
    m_PixelDisplay->Destroy();
    m_MemoryLayout->Destroy();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Emulator6502::Reset()
{
    Memory::Reset();
    m_CPU.Reset();
}

} // namespace emulator6502
