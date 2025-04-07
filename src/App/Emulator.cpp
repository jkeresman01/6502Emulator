#include "Emulator.h"

#include <vector>


namespace emulator6502
{

constexpr int64_t BUFFER_SIZE = 8192;
static char asmCode[BUFFER_SIZE] = "";

void Emulator6502::Init()
{
    Reset();
    glfwInit();
    m_Window = glfwCreateWindow(1180, 820, "6502 Emulator", NULL, NULL);
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

    ImGui::Text("Assembly Editor:");
    ImGui::Separator();
    ImGui::InputTextMultiline("##Editor", asmCode, sizeof(asmCode), ImVec2(-FLT_MIN, 300));

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

    const uint32_t gridSize = 32;
    const float pixelSize = 6.0f;

    static const ImVec4 colors[] = {
        ImVec4(0, 0, 0, 1),       ImVec4(1, 1, 1, 1),
        ImVec4(1, 0, 0, 1),       ImVec4(0, 1, 0, 1),
        ImVec4(0, 0, 1, 1),       ImVec4(1, 1, 0, 1),
        ImVec4(1, 0, 1, 1),          ImVec4(0, 1, 1, 1),
        ImVec4(0.5, 0.5, 0.5, 1), ImVec4(0.75, 0.75, 0.75, 1),
        ImVec4(0.5, 0, 0, 1),     ImVec4(0, 0.5, 0, 1),
        ImVec4(0, 0, 0.5, 1),     ImVec4(0.5, 0.5, 0, 1),
        ImVec4(0.5, 0, 0.5, 1),   ImVec4(0, 0.5, 0.5, 1)
    };

    ImGui::Text("Pixel Display:");
    for (uint32_t y = 0; y < gridSize; ++y)
    {
        for (uint32_t x = 0; x < gridSize; ++x)
        {
            uint16_t address = 0x0200 + (y * gridSize + x);
            uint8_t colorIndex = Memory::Read(address) & 0x0F;

            ImGui::PushStyleColor(ImGuiCol_Button, colors[colorIndex]);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors[colorIndex]);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors[colorIndex]);
            ImGui::Button("##", ImVec2(pixelSize, pixelSize));
            ImGui::PopStyleColor(3);

            if (x < gridSize - 1)
                ImGui::SameLine();
        }
    }

    ImGui::NextColumn();

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
    ImGui::Columns(1);

    ImGui::End();
}

void Emulator6502::LoadProgramIntoMemory(const std::string &asmCode)
{
    std::vector<uint8_t> machineCode;

    std::stringstream ss(asmCode);
    std::string line;

    while (std::getline(ss, line))
    {
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.substr(0, 3) == "LDA")
        {
            if (line[4] == '#')
            {
                uint8_t value = std::stoi(line.substr(5), nullptr, 16);
                machineCode.push_back(0xA9);
                machineCode.push_back(value);
            }
        }
        else if (line.substr(0, 3) == "STA")
        {
            if (line[4] == '$')
            {
                uint16_t address = std::stoi(line.substr(5), nullptr, 16);
                machineCode.push_back(0x8D);
                machineCode.push_back(address & 0xFF);
                machineCode.push_back((address >> 8) & 0xFF);
            }
        }

        for (size_t i = 0; i < machineCode.size(); ++i)
        {
            Memory::s_RAM[0x0800 + i] = machineCode[i];
        }

        std::cout << asmCode;
    }
}
} // namespace emulator6502
