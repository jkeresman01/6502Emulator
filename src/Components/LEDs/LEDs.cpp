#include "LEDs.h"

#include <cstdint>

#include "imgui.h"

#include "../../Core/Memory.h"

namespace emulator6502
{

void LEDs::Init() noexcept {}
void LEDs::Render() noexcept
{
    ImGui::Begin("LED Display");

    uint16_t ledBits = Memory::Read(0x0600) | (Memory::Read(0x0601) << 8);

    ImDrawList *draw_list = ImGui::GetWindowDrawList();
    ImVec2 startPos = ImGui::GetCursorScreenPos();

    for (size_t i = 0; i < 16; ++i)
    {
        bool isOn = (ledBits >> (15 - i)) & 1;

        ImVec2 center = ImVec2(startPos.x + i * (2 * RADIUS + SPACING) + RADIUS, startPos.y + RADIUS);

        ImU32 color = isOn ? IM_COL32(255, 0, 0, 255) : IM_COL32(60, 60, 60, 255);
        draw_list->AddCircleFilled(center, RADIUS, color);
    }

    ImGui::Dummy(ImVec2(16 * (2 * RADIUS + SPACING), 2 * RADIUS + SPACING));
    ImGui::End();
}

void LEDs::Destroy() noexcept {}

} // namespace emulator6502