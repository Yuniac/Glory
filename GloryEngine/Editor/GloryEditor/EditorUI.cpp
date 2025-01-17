#include "EditorUI.h"
#include <LayerManager.h>
#include <LayerRef.h>

namespace Glory::Editor
{
	size_t Glory::Editor::EditorUI::m_BufferWriteIndex = 0;
	char Glory::Editor::EditorUI::m_CleanNameBuffer[BUFFERLENGTH] = "\0";

	bool Glory::Editor::EditorUI::InputFloat(std::string_view label, float* value, const float min, const float max, const float steps)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width);
		const bool change = ImGui::DragFloat("##value", value, steps, min, max, "%.3f");
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputFloat2(std::string_view label, glm::vec2* value, const float min, const float max, const float steps)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width);
		const bool change = ImGui::DragFloat2("##value", (float*)value, steps, min, max, "%.3f");
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputFloat3(std::string_view label, glm::vec3* value, const float min, const float max, const float steps)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width);
		const bool change = ImGui::DragFloat3("##value", (float*)value, steps, min, max, "%.3f");
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputFloat4(std::string_view label, glm::vec4* value, const float min, const float max, const float steps)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width);
		const bool change = ImGui::DragFloat4("##value", (float*)value, steps, min, max, "%.3f");
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputInt(std::string_view label, int* value, const int min, const int max, const int steps)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width);
		const bool change = ImGui::DragInt("##value", value, steps, min, max);
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputInt2(std::string_view label, glm::ivec2* value, const int min, const int max, const int steps)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width);
		const bool change = ImGui::DragInt2("##value", (int*)value, steps, min, max);
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputInt3(std::string_view label, glm::ivec3* value, const int min, const int max, const int steps)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width);
		const bool change = ImGui::DragInt3("##value", (int*)value, steps, min, max);
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputInt4(std::string_view label, glm::ivec4* value, const int min, const int max, const int steps)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width);
		const bool change = ImGui::DragInt4("##value", (int*)value, steps, min, max);
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputDouble(std::string_view label, double* value, const double slowSteps, const double fastSteps)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width);
		const bool change = ImGui::InputDouble("##value", value, slowSteps, fastSteps);
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::CheckBox(std::string_view label, bool* value)
	{
		const ImVec2 textSize = ImGui::CalcTextSize(label.data());
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;
		const float size = 24.0f;
		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - size, cursorPos.y });
		const bool change = ImGui::Checkbox("##value", value);
		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputColor(std::string_view label, glm::vec4* value, const bool hdr)
	{
		ImGui::PushID(label.data());

		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);

		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;
		const float colorIconWidth = ImGui::CalcTextSize("F").y * 1.38f;
		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width - colorIconWidth - 7.8f);
		glm::vec4 tempValue = *value;
		tempValue *= 255.0f;
		bool change = ImGui::DragFloat4("##value", (float*)&tempValue, 1.0f, 0, 255, "%.0f");
		if (change)
		{
			*value = tempValue / 255.0f;
		}
		ImGui::PopItemWidth();

		ImVec4 color = ImVec4(value->x, value->y, value->z, value->w);

		ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0); //| /**(drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop)*/ | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);
		static ImVec4 backup_color;
		ImGui::SameLine();
		const bool open_popup = ImGui::ColorButton(label.data(), color, misc_flags, { colorIconWidth, colorIconWidth });

		if (open_popup)
		{
			ImGui::OpenPopup("ColorPickerPopup");
			backup_color = color;
		}

		if (ImGui::BeginPopup("ColorPickerPopup"))
		{
			ImGui::Text(label.data());
			ImGui::Separator();
			change |= ImGui::ColorPicker4("ColorPicker", (float*)&color, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
			ImGui::SameLine();

			ImGui::BeginGroup(); // Lock X position
			ImGui::Text("Current");
			ImGui::ColorButton("##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40));
			ImGui::Text("Previous");
			if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40)))
				color = backup_color;
			ImGui::Separator();
			ImGui::Text("Palette");
			//for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
			//{
			//    ImGui::PushID(n);
			//    if ((n % 8) != 0)
			//        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);
			//
			//    ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip;
			//    if (ImGui::ColorButton("##palette", saved_palette[n], palette_button_flags, ImVec2(20, 20)))
			//        color = ImVec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, color.w); // Preserve alpha!
			//
			//    // Allow user to drop colors into each palette entry. Note that ColorButton() is already a
			//    // drag source by default, unless specifying the ImGuiColorEditFlags_NoDragDrop flag.
			//    if (ImGui::BeginDragDropTarget())
			//    {
			//        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
			//            memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 3);
			//        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
			//            memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 4);
			//        ImGui::EndDragDropTarget();
			//    }
			//
			//    ImGui::PopID();
			//}
			ImGui::EndGroup();
			ImGui::EndPopup();

			value->x = color.x;
			value->y = color.y;
			value->z = color.z;
			value->w = color.w;
		}

		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputText(std::string_view label, char* value, size_t bufferSize, ImGuiInputTextFlags flags)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		ImGui::PushItemWidth(width);
		const bool change = ImGui::InputText("##value", value, bufferSize, flags);
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputDropdown(std::string_view label, const std::vector<std::string_view>& options, size_t* index, std::string_view value)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		bool change = false;
		ImGui::PushItemWidth(width);
		if (ImGui::BeginCombo("##combo", value.data()))
		{
			for (size_t i = 0; i < options.size(); i++)
			{
				bool isSelected = *index == i;
				if (ImGui::Selectable(options[i].data(), isSelected))
				{
					*index = i;
					change = true;
				}
			}

			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputDropdown(std::string_view label, const std::vector<std::string_view>& options, const std::vector<bool>& selected, std::string_view value)
	{
		assert(options.size() == selected.size());

		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		bool change = false;
		ImGui::PushItemWidth(width);
		if(ImGui::BeginCombo("##combo", value.data()))
		{
			for (size_t i = 0; i < options.size(); i++)
			{
				bool isSelected = selected[i];
				if (ImGui::Selectable(options[i].data(), isSelected))
				{
					selected[i] != selected[i];
					change = true;
				}
			}

			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGui::PopID();
		return change;
	}

	bool EditorUI::InputEnum(std::string_view label, size_t typeHash, size_t* value, std::vector<size_t> excludeValues)
	{
		const GloryReflect::TypeData* pEnumTypeData = GloryReflect::Reflect::GetTyeData(typeHash);

		GloryReflect::EnumType* pEnumType = GloryReflect::Reflect::GetEnumType(typeHash);
		if (!pEnumType)
		{
			ImGui::TextColored({ 1,0,0,1 }, label.data());
			return false;
		}

		std::string valueString;
		if (!pEnumType->ToString(value, valueString)) valueString = "none";


		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		float maxWidth = ImGui::GetContentRegionAvail().x;
		ImGui::PushID(label.data());
		if (!label.empty())
		{
			ImGui::TextUnformatted(label.data());
			maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
			ImGui::SameLine();
		}
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		if (!label.empty())
		{
			ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });
			ImGui::PushItemWidth(width);
		}

		bool change = false;
		if (ImGui::BeginCombo("##combo", valueString.c_str()))
		{
			for (size_t i = 0; i < pEnumType->NumValues(); i++)
			{
				const std::string& name = pEnumType->GetName(i);
				size_t outValue = 0;

				pEnumType->FromString(name, (void*)&outValue);

				if (std::find(excludeValues.begin(), excludeValues.end(), outValue) != excludeValues.end()) continue;
				if (ImGui::Selectable(name.c_str(), outValue == *value))
				{
					*value = outValue;
					change = true;
				}
			}
			ImGui::EndCombo();
		}
		ImGui::SetItemAllowOverlap();
		ImGui::PopID();

		return change;
	}

	bool EditorUI::InputLayerMask(std::string_view label, LayerMask* data)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		std::vector<std::string_view> layerOptions;
		std::string layerText;

		LayerManager::GetAllLayerNames(layerOptions);
		layerText = LayerManager::LayerMaskToString(*data);

		LayerMask originalMask = *data;
		ImGui::PushItemWidth(width);
		if(ImGui::BeginCombo("##mask", layerText.data()))
		{
			for (size_t i = 0; i < layerOptions.size(); i++)
			{
				const Layer* pLayer = LayerManager::GetLayerAtIndex(i - 1);

				bool selected = pLayer == nullptr ? *data == 0 : (*data & pLayer->m_Mask) > 0;
				if (ImGui::Selectable(layerOptions[i].data(), selected))
				{
					if (pLayer == nullptr)
						*data = 0;
					else
						*data ^= pLayer->m_Mask;

					layerText = LayerManager::LayerMaskToString(*data);
				}
			}

			ImGui::EndCombo();
		}

		ImGui::PopItemWidth();
		ImGui::PopID();
		return originalMask != *data;
	}

	bool EditorUI::InputLeyerRef(std::string_view label, LayerRef* data)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::PushID(label.data());
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		const float width = std::max(maxWidth, 100.0f);

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos({ cursorPos.x + availableWidth - width, cursorPos.y });

		int index = data->m_LayerIndex;

		std::vector<std::string_view> options;
		LayerManager::GetAllLayerNames(options);

		bool change = false;
		ImGui::PushItemWidth(width);
		if (ImGui::BeginCombo("##layer", options[index].data()))
		{
			for (size_t i = 0; i < options.size(); i++)
			{
				bool selected = i == index;
				if (ImGui::Selectable(options[i].data(), selected))
				{
					data->m_LayerIndex = i;
					change = true;
				}

				if (selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		ImGui::PopID();
		return change;
	}

	bool EditorUI::Header(std::string_view label)
	{
		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_AllowItemOverlap;

		std::hash<std::string_view> hasher;
		size_t hash = hasher(label);

		ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.0f, 0.0f, 0.0f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
		const bool headerOpen = ImGui::TreeNodeEx("##header", node_flags, label.data());
		ImGui::PopStyleColor(3);
		return headerOpen;
	}

	void EditorUI::EmptyDropdown(std::string_view label, std::string_view value, std::function<void()> callback, float& start, float& width, const float borderPadding)
	{
		const float labelReservedWidth = std::max(ImGui::CalcTextSize(label.data()).x, 150.0f);
		ImGui::TextUnformatted(label.data());
		const float maxWidth = ImGui::GetContentRegionAvail().x - labelReservedWidth;
		ImGui::SameLine();
		const float availableWidth = ImGui::GetContentRegionAvail().x;

		width = std::max(maxWidth, 100.0f) - borderPadding;

		const ImVec2 cursorPos = ImGui::GetCursorPos();
		start = cursorPos.x + availableWidth - width;
		ImGui::SetCursorPos({ start, cursorPos.y });

		std::vector<std::string_view> options;
		LayerManager::GetAllLayerNames(options);

		ImGui::PushItemWidth(width);
		if (ImGui::BeginCombo("##dropdown", value.data()))
		{
			callback();
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
	}

	std::string_view EditorUI::MakeCleanName(std::string_view label)
	{
		m_CleanNameBuffer[0] = '\0';
		m_BufferWriteIndex = 0;

		size_t startIndex = 0;
		if (label._Starts_with("m_p"))
			startIndex = 3;
		else if (label._Starts_with("m_"))
			startIndex = 2;
		else if (label._Starts_with("_"))
			startIndex = 1;

		char lastChar = '\0';
		bool charWasEdited = false;
		for (size_t i = startIndex; i < label.size(); i++)
		{
			const bool editedCache = charWasEdited;
			charWasEdited = false;
			if (label[i] == '_')
			{
				lastChar = label[i];
				continue;
			}
			const bool isAlpha = std::isalpha(label[i]);
			const bool isDigit = std::isdigit(label[i]);

			if (!isAlpha && !isDigit) continue;
			if (lastChar == '\0')
			{
				lastChar = std::toupper(label[i]);
				m_CleanNameBuffer[m_BufferWriteIndex] = lastChar;
				++m_BufferWriteIndex;
				charWasEdited = true;
				continue;
			}

			if ((editedCache || std::islower(lastChar)) && (std::isupper(label[i]) || lastChar == '_'))
			{
				charWasEdited = true;
				lastChar = std::toupper(label[i]);
				m_CleanNameBuffer[m_BufferWriteIndex] = ' ';
				m_CleanNameBuffer[m_BufferWriteIndex + 1] = lastChar;
				m_BufferWriteIndex += 2;
				continue;
			}
			lastChar = label[i];
			m_CleanNameBuffer[m_BufferWriteIndex] = label[i];
			++m_BufferWriteIndex;
		}
		m_CleanNameBuffer[m_BufferWriteIndex] = '\0';
		++m_BufferWriteIndex;
		return m_CleanNameBuffer;
	}
}
