////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <emulator/components/Pixel.h>

namespace emulator6502
{

////////////////////////////////////////////////////////////
void Pixel::Render() const
{
    ImGui::PushStyleColor(ImGuiCol_Button, m_Color);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_Color);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_Color);

    ImGui::Button("##", ImVec2(PIXEL_SIZE, PIXEL_SIZE));
    ImGui::PopStyleColor(3);
}

} // namespace emulator6502
