#include "PixelDisplay.h"

#include <string>

#include "imgui.h"

#include "../../Core/Memory.h"
#include "../../Types/Pixel.h"
#include "../../Util/ColorsUtil.h"

namespace emulator6502
{

void PixelDisplay::Init() noexcept
{
    // Do nothing
}

void PixelDisplay::Render() noexcept
{
    ImGui::Begin("Pixel Display");

    ImGui::Text("$0200 - $05FF");

    ImGui::SameLine(150);
    if (ImGui::Button("Show Color Palette"))
    {
        ImGui::OpenPopup("Color Palette");
    }

    if (ImGui::BeginPopupModal("Color Palette", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Each value ($0-$F) maps to one of these colors: ");
        ImGui::NewLine();

        for (uint32_t i = 1; i <= COLORS_COUNT; ++i)
        {
            const ImVec4 &color = ColorsUtil::GetPixelColor(i - 1);
            ImGui::ColorButton(("##color" + std::to_string(i - 1)).c_str(), color,
                               ImGuiColorEditFlags_NoTooltip, ImVec2(32, 32));
            ImGui::SameLine();
            ImGui::Text("0x%X", i - 1);

            if (i % COLORS_PER_ROW == 0)
            {
                ImGui::NewLine();
            }
            else
            {
                ImGui::SameLine();
            }
        }

        ImGui::NewLine();
        if (ImGui::Button("Close"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    ImGui::NewLine();

    for (uint32_t y = 0; y < GRID_SIZE; ++y)
    {
        for (uint32_t x = 0; x < GRID_SIZE; ++x)
        {
            Word address = START_ADDR + (y * GRID_SIZE + x);
            Byte colorIndex = Memory::Read(address) & 0x0F;

            const ImVec4 &color = ColorsUtil::GetPixelColor(colorIndex);

            Pixel pixel;
            pixel.SetColor(color);
            pixel.Render();

            if (x < GRID_SIZE - 1)
            {
                ImGui::SameLine();
            }
        }
    }

    ImGui::End();
}

void PixelDisplay::Destroy() noexcept
{
    // Do nothing
}

} // namespace emulator6502