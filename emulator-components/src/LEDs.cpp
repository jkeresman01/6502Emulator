////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <emulator/components/LEDs.h>

#include <emulator/core/Memory.h>

#include <cstdint>
#include "imgui.h"


namespace emulator6502
{

static constexpr uint8_t LEDS_NO = 16;


////////////////////////////////////////////////////////////
void LEDs::Init() noexcept 
{
    //Do nothing
}


////////////////////////////////////////////////////////////
void LEDs::Render() noexcept
{
    ImGui::Begin("LEDs");

    ImGui::Text("$0600 - $0601");
    ImGui::NewLine();

    Word ledBits = Memory::Read(0x0600) | (Memory::Read(0x0601) << 8);

    ImDrawList *drawList = ImGui::GetWindowDrawList();
    ImVec2 startPos = ImGui::GetCursorScreenPos();

    for (size_t i = 0; i < LEDS_NO; ++i)
    {
        bool isLEDOn = (ledBits >> (LEDS_NO - 1 - i)) & 1;

        ImVec2 center = ImVec2(startPos.x + i * (2 * RADIUS + SPACING) + RADIUS, startPos.y + RADIUS);

        ImU32 color = isLEDOn ? IM_COL32(255, 0, 0, 255) : IM_COL32(60, 60, 60, 255);
        drawList->AddCircleFilled(center, RADIUS, color);
    }

    ImGui::Dummy(ImVec2(LEDS_NO * (2 * RADIUS + SPACING), 2 * RADIUS + SPACING));
    ImGui::End();
}


////////////////////////////////////////////////////////////
void LEDs::Destroy() noexcept 
{
    //Do nothing
}

} // namespace emulator6502
