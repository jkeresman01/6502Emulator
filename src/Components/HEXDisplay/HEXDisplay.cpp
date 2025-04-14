#include "HEXDisplay.h"

#include "../../Core/Memory.h"

namespace emulator6502
{

static constexpr bool SEGMENTS[16][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}, // 9
    {1, 1, 1, 0, 1, 1, 1}, // A
    {0, 0, 1, 1, 1, 1, 1}, // B
    {1, 0, 0, 1, 1, 1, 0}, // C
    {0, 1, 1, 1, 1, 0, 1}, // D
    {1, 0, 0, 1, 1, 1, 1}, // E
    {1, 0, 0, 0, 1, 1, 1}  // F
};

void HEXDisplay::Init() noexcept
{
    // Do nothing for now
}

void HEXDisplay::Render() noexcept
{
    ImGui::Begin("HEX Display");

    ImDrawList *draw = ImGui::GetWindowDrawList();
    ImVec2 start = ImGui::GetCursorScreenPos();

    const float size = 80.0f;
    const float spacing = 20.0f;

    for (int i = 0; i < NUM_DIGITS; ++i)
    {
        Byte value = Memory::Read(BASE_ADDR + i);
        ImVec2 pos = ImVec2(start.x + i * (size + spacing), start.y);
        DrawSevenSegmentDigit(draw, pos, size, value);
    }

    ImGui::Dummy(ImVec2(NUM_DIGITS * (size + spacing), size + 30));
    ImGui::End();
}

void HEXDisplay::DrawSevenSegmentDigit(ImDrawList *drawList, const ImVec2 &pos, const float size,
                                       const uint8_t value)
{
    const float segmentLength = size;
    const float segmentThickness = size * 0.2f;

    constexpr ImU32 onColor = IM_COL32(255, 0, 0, 255);
    constexpr ImU32 offColor = IM_COL32(255, 255, 255, 50);

    const bool *segs = SEGMENTS[value & 0x0F];

    ImVec2 a[] = {ImVec2(pos.x + segmentThickness, pos.y),
                  ImVec2(pos.x + segmentLength - segmentThickness, pos.y),
                  ImVec2(pos.x + segmentLength - segmentThickness * 2, pos.y + segmentThickness),
                  ImVec2(pos.x + segmentThickness * 2, pos.y + segmentThickness)};

    ImVec2 b[] = {
        ImVec2(pos.x + segmentLength, pos.y + segmentThickness),
        ImVec2(pos.x + segmentLength, pos.y + segmentLength / 2 - segmentThickness),
        ImVec2(pos.x + segmentLength - segmentThickness, pos.y + segmentLength / 2 - segmentThickness * 2),
        ImVec2(pos.x + segmentLength - segmentThickness, pos.y + segmentThickness * 2)};

    ImVec2 c[] = {
        ImVec2(pos.x + segmentLength, pos.y + segmentLength / 2 + segmentThickness),
        ImVec2(pos.x + segmentLength, pos.y + segmentLength - segmentThickness),
        ImVec2(pos.x + segmentLength - segmentThickness, pos.y + segmentLength - segmentThickness * 2),
        ImVec2(pos.x + segmentLength - segmentThickness, pos.y + segmentLength / 2 + segmentThickness * 2)};

    ImVec2 d[] = {
        ImVec2(pos.x + segmentThickness, pos.y + segmentLength),
        ImVec2(pos.x + segmentLength - segmentThickness, pos.y + segmentLength),
        ImVec2(pos.x + segmentLength - segmentThickness * 2, pos.y + segmentLength - segmentThickness),
        ImVec2(pos.x + segmentThickness * 2, pos.y + segmentLength - segmentThickness)};

    ImVec2 e[] = {ImVec2(pos.x, pos.y + segmentLength / 2 + segmentThickness),
                  ImVec2(pos.x, pos.y + segmentLength - segmentThickness),
                  ImVec2(pos.x + segmentThickness, pos.y + segmentLength - segmentThickness * 2),
                  ImVec2(pos.x + segmentThickness, pos.y + segmentLength / 2 + segmentThickness * 2)};

    ImVec2 f[] = {ImVec2(pos.x, pos.y + segmentThickness),
                  ImVec2(pos.x, pos.y + segmentLength / 2 - segmentThickness),
                  ImVec2(pos.x + segmentThickness, pos.y + segmentLength / 2 - segmentThickness * 2),
                  ImVec2(pos.x + segmentThickness, pos.y + segmentThickness * 2)};

    ImVec2 g[] = {
        ImVec2(pos.x + segmentThickness, pos.y + segmentLength / 2),
        ImVec2(pos.x + segmentLength - segmentThickness, pos.y + segmentLength / 2),
        ImVec2(pos.x + segmentLength - segmentThickness * 2, pos.y + segmentLength / 2 + segmentThickness),
        ImVec2(pos.x + segmentThickness * 2, pos.y + segmentLength / 2 + segmentThickness)};

    ImVec2 *segments[7] = {a, b, c, d, e, f, g};

    for (int i = 0; i < 7; ++i)
    {
        drawList->AddConvexPolyFilled(segments[i], 4, segs[i] ? onColor : offColor);
    }
}

void HEXDisplay::Destroy() noexcept
{
    // Do nothing for now
}

} // namespace emulator6502