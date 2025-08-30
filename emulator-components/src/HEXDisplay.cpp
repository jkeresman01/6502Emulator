#include "HEXDisplay.h"

#include "../../Core/Memory.h"

namespace emulator6502
{
static constexpr uint8_t SEGMENTS_NO = 7;
static constexpr uint8_t DIGITS_LETTERS_NO = 16;

static constexpr bool SEGMENTS[DIGITS_LETTERS_NO][SEGMENTS_NO] = {
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
    ImGui::Text("$0602 - $0605");
    ImGui::NewLine();

    ImDrawList *drawList = ImGui::GetWindowDrawList();
    ImVec2 start = ImGui::GetCursorScreenPos();

    for (size_t i = 0; i < DIGITS_NO; ++i)
    {
        Byte value = Memory::Read(BASE_ADDR + i);
        ImVec2 position = ImVec2(start.x + i * (SIZE + SPACING), start.y);
        DrawSevenSegmentDigit(drawList, position, SIZE, value);
    }

    ImGui::Dummy(ImVec2(DIGITS_NO * (SIZE + SPACING), SIZE + 30));
    ImGui::End();
}

void HEXDisplay::DrawSevenSegmentDigit(ImDrawList *drawList, const ImVec2 &position, const float size,
                                       const uint8_t value)
{
    const float segmentLength = size;
    const float segmentThickness = size * 0.2f;

    constexpr ImU32 onColor = IM_COL32(255, 0, 0, 255);
    constexpr ImU32 offColor = IM_COL32(255, 255, 255, 50);

    const bool *segs = SEGMENTS[value & 0x0F];

    ImVec2 a[] = {ImVec2(position.x + segmentThickness, position.y),
                  ImVec2(position.x + segmentLength - segmentThickness, position.y),
                  ImVec2(position.x + segmentLength - segmentThickness * 2, position.y + segmentThickness),
                  ImVec2(position.x + segmentThickness * 2, position.y + segmentThickness)};

    ImVec2 b[] = {ImVec2(position.x + segmentLength, position.y + segmentThickness),
                  ImVec2(position.x + segmentLength, position.y + segmentLength / 2 - segmentThickness),
                  ImVec2(position.x + segmentLength - segmentThickness,
                         position.y + segmentLength / 2 - segmentThickness * 2),
                  ImVec2(position.x + segmentLength - segmentThickness, position.y + segmentThickness * 2)};

    ImVec2 c[] = {ImVec2(position.x + segmentLength, position.y + segmentLength / 2 + segmentThickness),
                  ImVec2(position.x + segmentLength, position.y + segmentLength - segmentThickness),
                  ImVec2(position.x + segmentLength - segmentThickness,
                         position.y + segmentLength - segmentThickness * 2),
                  ImVec2(position.x + segmentLength - segmentThickness,
                         position.y + segmentLength / 2 + segmentThickness * 2)};

    ImVec2 d[] = {ImVec2(position.x + segmentThickness, position.y + segmentLength),
                  ImVec2(position.x + segmentLength - segmentThickness, position.y + segmentLength),
                  ImVec2(position.x + segmentLength - segmentThickness * 2,
                         position.y + segmentLength - segmentThickness),
                  ImVec2(position.x + segmentThickness * 2, position.y + segmentLength - segmentThickness)};

    ImVec2 e[] = {
        ImVec2(position.x, position.y + segmentLength / 2 + segmentThickness),
        ImVec2(position.x, position.y + segmentLength - segmentThickness),
        ImVec2(position.x + segmentThickness, position.y + segmentLength - segmentThickness * 2),
        ImVec2(position.x + segmentThickness, position.y + segmentLength / 2 + segmentThickness * 2)};

    ImVec2 f[] = {
        ImVec2(position.x, position.y + segmentThickness),
        ImVec2(position.x, position.y + segmentLength / 2 - segmentThickness),
        ImVec2(position.x + segmentThickness, position.y + segmentLength / 2 - segmentThickness * 2),
        ImVec2(position.x + segmentThickness, position.y + segmentThickness * 2)};

    ImVec2 g[] = {
        ImVec2(position.x + segmentThickness, position.y + segmentLength / 2),
        ImVec2(position.x + segmentLength - segmentThickness, position.y + segmentLength / 2),
        ImVec2(position.x + segmentLength - segmentThickness * 2,
               position.y + segmentLength / 2 + segmentThickness),
        ImVec2(position.x + segmentThickness * 2, position.y + segmentLength / 2 + segmentThickness)};

    ImVec2 *segments[SEGMENTS_NO] = {a, b, c, d, e, f, g};

    for (size_t i = 0; i < SEGMENTS_NO; ++i)
    {
        drawList->AddConvexPolyFilled(segments[i], 4, segs[i] ? onColor : offColor);
    }
}

void HEXDisplay::Destroy() noexcept
{
    // Do nothing for now
}

} // namespace emulator6502