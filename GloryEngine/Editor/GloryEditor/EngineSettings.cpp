#include "ProjectSettings.h"
#include <imgui.h>
#include <Engine.h>
#include <EditorPlatform.h>

namespace Glory::Editor
{
	bool EngineSettings::OnGui()
	{
        DrawLeftPanel();
        DrawRightPanel();
        return false;
	}

    void EngineSettings::DrawLeftPanel()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::PushFont(EditorPlatform::LargeFont);
        ImGui::BeginChild("LeftPanel", ImVec2(250.0f, 0.0f), true);
        ImGui::BeginChild("LeftPanelHeader", ImVec2(0.0f, 50.0f), false);

        ImVec2 contentRegionAvail = ImGui::GetContentRegionAvail();
        float size = EditorPlatform::LargeFont->FontSize;
        float cursorPosY = ImGui::GetCursorPosY();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - (size / 2.0f) + (contentRegionAvail.y / 2.0f));
        ImGui::TextUnformatted("Glory Engine");
        ImGui::SetCursorPosY(cursorPosY);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + contentRegionAvail.x - contentRegionAvail.y);

        ImGui::EndChild();
        ImGui::Separator();
        ImGui::BeginChild("LeftPanelBody", ImVec2(0.0f, 0.0f), false);

        Engine* pEngine = Game::GetGame().GetEngine();

        for (size_t i = 0; i < pEngine->ModulesCount(); i++)
        {
            const std::string& moduleName = pEngine->GetModule(i)->GetMetaData().Name();
            if (moduleName.empty()) continue;
            bool selected = m_MenuIndex == i;
            ImGui::PushID(moduleName.data());
            if (ImGui::Selectable("##selectable", selected, 0, ImVec2(0.0f, 50.0f)))
            {
                m_MenuIndex = i;
            }

            const ImVec2 textSize = ImGui::CalcTextSize(moduleName.data());

            ImGui::SameLine();
            const ImVec2 cursorPos = ImGui::GetCursorPos();
            ImGui::SetCursorPos({ cursorPos.x + 5.0f, cursorPos.y + 25.0f - textSize.y / 2.0f });
            ImGui::TextUnformatted(moduleName.data());
            ImGui::PopID();
        }
        ImGui::PopFont();

        ImGui::EndChild();
        ImGui::EndChild();
    }

    void EngineSettings::DrawRightPanel()
    {
        ImGui::SameLine();
        ImGui::BeginChild("RightPanel", ImVec2(), true);

        Engine* pEngine = Game::GetGame().GetEngine();
        Module* pModule = pEngine->GetModule(m_MenuIndex);
        const ModuleMetaData& moduleMetaData = pModule->GetMetaData();
        const Glory::Version& version = pModule->ModuleVersion();
        const std::string versionString = version.GetVersionString();

        ImGui::PushFont(EditorPlatform::LargeFont);
        ImGui::TextUnformatted(moduleMetaData.Name().data());
        ImGui::PopFont();
        ImGui::SameLine();
        const float availableWidth = ImGui::GetContentRegionAvail().x;
        const float cursorPosX = ImGui::GetCursorPosX();

        const float textWidth = ImGui::CalcTextSize(versionString.data()).x + ImGui::CalcTextSize("Version ").x;

        ImGui::SetCursorPosX(cursorPosX + availableWidth - textWidth);
        ImGui::Text("Version %s", versionString.data());

        ImGui::Separator();

        ImGui::Spacing();
        ImGui::TextUnformatted("Module settings comming soon!");

        ImGui::EndChild();
    }
}