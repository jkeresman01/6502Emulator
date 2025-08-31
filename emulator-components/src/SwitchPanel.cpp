////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <emulator/components/SwitchPanel.h>

#include "imgui.h"

#include <emulator/core/Memory.h>

#include <cstdio>
#include <string>

namespace emulator6502
{

////////////////////////////////////////////////////////////
void SwitchPanel::Init()
{
    // Do nothing for now
}


////////////////////////////////////////////////////////////
void SwitchPanel::Render()
{
    ImGui::Begin("Switches");

    ImGui::Text("$0606 - $0608");
    ImGui::NewLine();

    Word &switchBits = *(Word *)&Memory::s_RAM[0x0606];

    for (int32_t i = SWITCHES_COUNT; i >= 0; --i)
    {
        std::string label = "##bit" + std::to_string(i);

        bool switchState = (switchBits >> i) & 1;

        if (ImGui::Checkbox(label.c_str(), &switchState))
        {
            switchState ? switchBits |= (1 << i) : switchBits &= ~(1 << i);
        }

        if (i > 0)
        {
            ImGui::SameLine();
        }
    }

    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();

    bool areAllSwitchesPressed = (switchBits & 0x03FF) == 0x03FF;

    if (ImGui::Checkbox("All", &areAllSwitchesPressed))
    {
        areAllSwitchesPressed ? switchBits |= 0x03FF : switchBits &= ~0x03FF;
    }

    ImGui::End();
}


////////////////////////////////////////////////////////////
void SwitchPanel::Destroy()
{
    // Do nothing for now
}

} // namespace emulator6502
