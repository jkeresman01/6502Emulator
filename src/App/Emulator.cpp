#include "Emulator.h"

#include <string>
#include <vector>

#include "../Util/ColorsUtil.h"
#include "../Util/ProgramUtil.h"
#include "../Util/RandomUtil.h"

namespace emulator6502
{
Emulator6502::Emulator6502()
{
    m_Components.reserve(COMPONENTS_NO);

    m_Components.emplace_back(std::make_unique<PixelDisplay>());
    m_Components.emplace_back(std::make_unique<MemoryLayout>());
    m_Components.emplace_back(std::make_unique<HEXDisplay>());
    m_Components.emplace_back(std::make_unique<LEDs>());
    m_Components.emplace_back(std::make_unique<SwitchPanel>());
}

void Emulator6502::Init()
{
    InitComponents();
    Reset();
    glfwInit();
    InitWindow();
    glfwMakeContextCurrent(m_Window);
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init();
}

void Emulator6502::InitComponents()
{
    Random::Init();

    m_CPU->Init();
    m_AsmEditor->Init();

    for (const auto &component : m_Components)
    {
        component->Init();
    }
}

void Emulator6502::InitWindow()
{
    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *videoMode = glfwGetVideoMode(primaryMonitor);
    m_Window = glfwCreateWindow(videoMode->width, videoMode->height, "6502 Emulator", NULL, NULL);
}

void Emulator6502::Run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Render();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_Window);
    }
}

void Emulator6502::Render()
{
    RenderComponents();
    RenderCPUStatusWindow();
    RenderDissasemblyPopup();
    RenderControlButtonsWindow();
    RenderStackOverflowPopup();
}

void Emulator6502::RenderCPUStatusWindow()
{
    ImGui::Begin("CPU Registers");

    ImGui::Text("A  = 0x%02X", m_CPU->GetAccumulator());
    ImGui::Text("X  = 0x%02X", m_CPU->GetRegisterX());
    ImGui::Text("Y  = 0x%02X", m_CPU->GetRegisterY());
    ImGui::Text("SP = 0x%02X", m_CPU->GetStackPointer());
    ImGui::Text("PC = 0x%04X", m_CPU->GetProgramCounter());

    ImGui::Separator();
    ImGui::Text("Status Flags:");

    const auto &flags = m_CPU->GetStatusFlags();

    ImGui::TextColored(ColorsUtil::GetFlagColor(flags.N), "N");
    ImGui::SameLine();
    ImGui::TextColored(ColorsUtil::GetFlagColor(flags.V), "V");
    ImGui::SameLine();
    ImGui::TextColored(ColorsUtil::GetFlagColor(flags._), "_");
    ImGui::SameLine();
    ImGui::TextColored(ColorsUtil::GetFlagColor(flags.B), "B");
    ImGui::SameLine();
    ImGui::TextColored(ColorsUtil::GetFlagColor(flags.D), "D");
    ImGui::SameLine();
    ImGui::TextColored(ColorsUtil::GetFlagColor(flags.I), "I");
    ImGui::SameLine();
    ImGui::TextColored(ColorsUtil::GetFlagColor(flags.Z), "Z");
    ImGui::SameLine();
    ImGui::TextColored(ColorsUtil::GetFlagColor(flags.C), "C");

    ImGui::End();
}

void Emulator6502::RenderComponents()
{
    m_AsmEditor->Render();

    for (const auto &component : m_Components)
    {
        component->Render();
    }
}

void Emulator6502::RenderControlButtonsWindow()
{
    ImGui::Begin("Controls");

    if (ImGui::Button("Assemble"))
    {
        Reset();
        LoadProgramIntoMemory();
    }

    ImGui::SameLine();
    if (ImGui::Button("Disassemble"))
    {
        OpenDissasemblyPopup();
    }

    ImGui::SameLine();
    if (ImGui::Button("Run"))
    {
        // TODO: Execution
    }

    ImGui::SameLine();
    if (ImGui::Button("Reset"))
    {
        Reset();
    }

    ImGui::SameLine();
    if (ImGui::Button("Step"))
    {
        m_CPU->Step();
    }

    ImGui::End();
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

void Emulator6502::RenderStackOverflowPopup()
{
    if (m_CPU->HasStackOverflowed())
    {
        ImGui::OpenPopup("Stack Overflow!");
    }

    if (ImGui::BeginPopupModal("Stack Overflow!", nullptr, ImGuiWindowFlags_AlwaysUseWindowPadding))
    {
        ImGui::Text("The 6502 stack has overflowed!\nThis may corrupt memory.\n\n");

        if (ImGui::Button("OK"))
        {
            ImGui::CloseCurrentPopup();
            m_CPU->ClearStackOverflowFlag();
        }

        ImGui::Separator();
        ImGui::Text("Stack (Top = $01FF):");

        for (size_t i = 0xFF; i > 0x00; --i)
        {
            Word addr = 0x0100 + i;
            Byte value = Memory::Read(addr);

            if (i == m_CPU->GetStackPointer())
            {
                ImGui::TextColored(ImVec4(1, 0.5f, 0.5f, 1), "-> $%04x : %02x", addr, value);
            }
            else
            {
                ImGui::Text("   $%04x : %02x", addr, value);
            }
        }

        ImGui::EndPopup();
    }
}

void Emulator6502::OpenDissasemblyPopup()
{
    const std::vector<Byte> &machineCode = ProgramUtil::ReadProgramFromMemory();
    m_Dissasembly = m_Disssembler->Disassmble(machineCode);
    m_ShowDisassemblyPopup = true;
}

void Emulator6502::LoadProgramIntoMemory()
{
    const std::string &asmCode = m_AsmEditor->GetText();
    const std::vector<Byte> &machineCode = m_Assembler->Assemble(asmCode);

    ProgramUtil::LoadProgramIntoMemory(machineCode);
}

void Emulator6502::Shutdown()
{
    DestroyComponents();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Emulator6502::DestroyComponents()
{
    m_AsmEditor->Destroy();

    for (const auto &component : m_Components)
    {
        component->Destroy();
    }
}

void Emulator6502::Reset()
{
    Memory::Reset();
    m_CPU->Reset();
}

} // namespace emulator6502
