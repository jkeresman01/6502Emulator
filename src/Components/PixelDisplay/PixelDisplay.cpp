#include "PixelDisplay.h"

#include "imgui.h"

#include "../../Core/Memory.h"
#include "../../Util/ColorsUtil.h"

#include "Pixel.h"

namespace emulator6502
{

void PixelDisplay::Init() noexcept
{
    // Do nothing
}

void PixelDisplay::Render() noexcept
{
    ImGui::Begin("Pixel Display");

    for (uint32_t y = 0; y < GRID_SIZE; ++y)
    {
        for (uint32_t x = 0; x < GRID_SIZE; ++x)
        {
            Word address = START_ADDR + (y * GRID_SIZE + x);
            Byte colorIndex = Memory::Read(address) & 0x0F;

            const ImVec4 &color = ColorsUtil::GetColor(colorIndex);

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