#include "MemoryLayout.h"

#include "imgui.h"

#include "../../Core/Memory.h"

namespace emulator6502
{

void MemoryLayout::Init() noexcept
{
    // Do nothing
}

void MemoryLayout::Render() noexcept
{
    ImGui::Begin("Memory Viewer");

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
    ImGui::End();
}

void MemoryLayout::Destroy() noexcept
{
    // Do nothing
}

} // namespace emulator6502