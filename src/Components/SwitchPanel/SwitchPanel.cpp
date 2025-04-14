#include "SwitchPanel.h"

#include "imgui.h"

#include "../../Core/Memory.h"
#include <cstdio>

namespace emulator6502
{
void SwitchPanel::Init()
{
    // Do nothing for now
}

void SwitchPanel::Render()
{
    ImGui::Begin("Switches");

    Word &switchBits = *(Word *)&Memory::s_RAM[0x0606];

    for (int32_t i = 9; i >= 0; --i)
    {
        char label[8];
        sprintf(label, "##bit%d", i);

        bool state = (switchBits >> i) & 1;

        if (ImGui::Checkbox(label, &state))
        {
            state ? switchBits |= (1 << i) : switchBits &= ~(1 << i);
        }

        if (i > 0)
        {
            ImGui::SameLine();
        }
    }

    ImGui::SameLine();
    ImGui::Spacing();
    ImGui::SameLine();

    bool areAllLEDsOn = (switchBits & 0x03FF) == 0x03FF;

    if (ImGui::Checkbox("All", &areAllLEDsOn))
    {
        areAllLEDsOn ? switchBits |= 0x03FF : switchBits &= ~0x03FF;
    }

    ImGui::End();
}

void SwitchPanel::Destroy()
{
    // Do nothing for now
}

} // namespace emulator6502