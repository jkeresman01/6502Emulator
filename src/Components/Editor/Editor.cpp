#include "Editor.h"

#include <cstdint>

#include "imgui.h"

namespace emulator6502
{

constexpr int64_t BUFFER_SIZE = 8192;
static char asmCode[BUFFER_SIZE] = "";

void Editor::Init() noexcept
{
    // Do nothing
}

void Editor::Render() noexcept
{
    ImGui::Begin("Assembly Editor");
    ImGui::InputTextMultiline("##Editor", asmCode, sizeof(asmCode), ImVec2(-FLT_MIN, 800));
    ImGui::End();
}

void Editor::Destroy() noexcept
{
    // Do nothing
}

std::string Editor::GetText() const
{
    return asmCode;
}

} // namespace emulator6502