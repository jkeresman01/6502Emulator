////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <emulator/components/PixelDisplay.h>

#include <emulator/core/Memory.h>
#include <emulator/components/Pixel.h>
#include <emulator/utilities/ColorsUtil.h>

#include <string>
#include "imgui.h"

namespace emulator6502
{


////////////////////////////////////////////////////////////
void PixelDisplay::Init() noexcept
{
    // No-op
}


////////////////////////////////////////////////////////////
void PixelDisplay::Render() noexcept
{
    ImGui::Begin("Pixel Display");
    ImGui::Text("$0200 - $05FF");

    RenderPaletteButton();
    ImGui::NewLine();

    RenderPixelGrid();

    ImGui::End();
}


////////////////////////////////////////////////////////////
void PixelDisplay::Destroy() noexcept
{
    // No-op
}


////////////////////////////////////////////////////////////
void PixelDisplay::RenderPaletteCell(uint32_t idx) const
{
    const ImVec4& color = ColorsUtil::GetPixelColor(idx);
    ImGui::ColorButton(("##color" + std::to_string(idx)).c_str(),
                       color,
                       ImGuiColorEditFlags_NoTooltip,
                       ImVec2(32, 32));
    ImGui::SameLine();
    ImGui::Text("0x%X", idx);
}


////////////////////////////////////////////////////////////
void PixelDisplay::RenderPalettePopup() const
{
    if (!ImGui::BeginPopupModal("Color Palette", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        return;

    ImGui::Text("Each value ($0-$F) maps to one of these colors:");
    ImGui::NewLine();

    for (uint32_t i = 0; i < COLORS_COUNT; ++i)
    {
        RenderPaletteCell(i);
        ( (i + 1) % COLORS_PER_ROW == 0 ) ? ImGui::NewLine() : ImGui::SameLine();
    }

    ImGui::NewLine();

    if (ImGui::Button("Close"))
    {
        ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
}


////////////////////////////////////////////////////////////
void PixelDisplay::RenderPaletteButton() const
{
    ImGui::SameLine(150);
    if (ImGui::Button("Show Color Palette"))
        ImGui::OpenPopup("Color Palette");

    RenderPalettePopup();
}


////////////////////////////////////////////////////////////
void PixelDisplay::RenderPixelAt(uint32_t x, uint32_t y) const
{
    const Word address   = START_ADDR + (y * GRID_SIZE + x);
    const Byte colorIdx  = Memory::Read(address) & 0x0F;
    const ImVec4& color  = ColorsUtil::GetPixelColor(colorIdx);

    Pixel p;
    p.SetColor(color);
    p.Render();
}


////////////////////////////////////////////////////////////
void PixelDisplay::RenderPixelGrid() const
{
    for (uint32_t y = 0; y < GRID_SIZE; ++y)
    {
        for (uint32_t x = 0; x < GRID_SIZE; ++x)
        {
            RenderPixelAt(x, y);
            if (x + 1 < GRID_SIZE) ImGui::SameLine();
        }
    }
}

} // namespace emulator6502

