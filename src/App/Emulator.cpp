#include "Emulator.h"

#include <vector>

#include "../Util/ColorsUtil.h"

namespace emulator6502
{

constexpr int64_t BUFFER_SIZE = 8192;
static char asmCode[BUFFER_SIZE] = "";

void Emulator6502::Init()
{
    Reset();
    glfwInit();
    m_Window = glfwCreateWindow(1180, 840, "6502 Emulator", NULL, NULL);
    glfwMakeContextCurrent(m_Window);
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init();
}


void Emulator6502::Reset()
{
    Memory::Reset();
    m_CPU.Reset();
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
    Reset();
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

    RenderAsmEditor();
    RenderButtons();
    RenderPixelDisplay();
    RenderProcessRegisterStatus();
    
    ImGui::NextColumn();

    RenderMemoryLayout();
    
    ImGui::Columns(1);

    ImGui::End();
}


void Emulator6502::RenderAsmEditor()
{
    ImGui::Text("Assembly Editor:");
    ImGui::Separator();
    ImGui::InputTextMultiline("##Editor", asmCode, sizeof(asmCode), ImVec2(-FLT_MIN, 300));
}

void Emulator6502::RenderMemoryLayout()
{
    ImGui::Text("Memory Viewer:");
    ImGui::Separator();

    ImGui::BeginChild("Memory", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

    for (uint32_t i = 0; i < MEMORY_64KB; i += 16)
    {
        char address[16];
        sprintf(address, "%04X: ", i);
        ImGui::TextUnformatted(address);
        ImGui::SameLine();

        for (uint32_t j = 0; j < 16; ++j)
        {
            ImGui::SameLine();
            char byteText[4];
            sprintf(byteText, "%02X", Memory::s_RAM[i + j]);
            ImGui::TextUnformatted(byteText);
        }
    }

    ImGui::EndChild();
}

void Emulator6502::RenderPixelDisplay()
{
    const uint32_t gridSize = 32;
    const float pixelSize = 6.0f;
  
    ImGui::Text("Pixel Display:");

    for (uint32_t y = 0; y < gridSize; ++y)
    {
        for (uint32_t x = 0; x < gridSize; ++x)
        {
            uint16_t address = 0x0200 + (y * gridSize + x);
            uint8_t colorIndex = Memory::Read(address) & 0x0F;

            const ImVec4 &color = ColorsUtil::GetColor(colorIndex);

            ImGui::PushStyleColor(ImGuiCol_Button, color);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);

            ImGui::Button("##", ImVec2(pixelSize, pixelSize));
            ImGui::PopStyleColor(3);

            if (x < gridSize - 1)
            {
                ImGui::SameLine();
            }
        }
    }
}

void Emulator6502::RenderProcessRegisterStatus()
{
    ImGui::Text("CPU Registers:");

    ImGui::Text("A  = 0x%02X", m_CPU.GetAccumulator());
    ImGui::Text("X  = 0x%02X", m_CPU.GetRegisterX());
    ImGui::Text("Y  = 0x%02X", m_CPU.GetRegisterY());
    ImGui::Text("SP = 0x%02X", m_CPU.GetStackPointer());
    ImGui::Text("PC = 0x%04X", m_CPU.GetProgramCounter());
    ImGui::Text("Status = 0x%02X", m_CPU.GetStatusFlags());
}

void Emulator6502::RenderButtons()
{
    if (ImGui::Button("Assemble"))
    {
        LoadProgramIntoMemory(asmCode);
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

void Emulator6502::LoadProgramIntoMemory(const std::string &asmCode)
{
    std::vector<uint8_t> machineCode = m_Assembler->Assemble(asmCode);
    
    for (size_t i = 0; i < machineCode.size(); ++i)
    {
        Memory::s_RAM[0x0800 + i] = machineCode[i];
    }
}
} // namespace emulator6502
