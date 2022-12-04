#include "ArrayPropertyDrawer.h"
#include "ListView.h"
#include <SerializedArrayProperty.h>
#include <imgui.h>
#include <Reflection.h>
#include <FontAwesome/IconsFontAwesome6.h>

namespace Glory::Editor
{
	bool ArrayPropertyDrawer::Draw(const SerializedProperty* serializedProperty, const std::string& label, void* data, size_t typeHash, uint32_t flags) const
	{
		if (serializedProperty == nullptr)
		{
			ImGui::Text("Error");
			return false;
		}

		bool change = false;

		BaseSerializedArrayProperty* serializedArrayProperty = (BaseSerializedArrayProperty*)serializedProperty;

		float width = ImGui::GetContentRegionAvail().x;
		float inputWidth = 10.0f;
		width -= inputWidth;

		ImGui::SetNextItemWidth(width);

		std::string nodeLabel = "##" + label;
		bool node = ImGui::TreeNodeEx(nodeLabel.c_str(), 0);
		ImGui::SameLine(0, 0);
		ImGui::TextUnformatted(label.c_str());
		ImGui::SameLine(width);

		size_t size = serializedArrayProperty->ArraySize();
		int newSize = (int)size;
		std::string sizeInputLabel = nodeLabel + "_Size";
		if (ImGui::InputInt(sizeInputLabel.c_str(), &newSize, 0, 0, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue) && size != (size_t)newSize)
		{
			if (newSize <= 0) newSize = 0;
			serializedArrayProperty->Resize(newSize);
			change = true;
		}

		if (node)
		{
			for (size_t i = 0; i < serializedArrayProperty->ArraySize(); i++)
			{
				SerializedProperty* pChildProperty = serializedArrayProperty->GetArrayElementAt(i);
				change |= PropertyDrawer::DrawProperty(pChildProperty);
			}

			ImGui::TreePop();
		}

		return change;
	}

	bool ArrayPropertyDrawer::Draw(const SerializedProperty* serializedProperty, const std::string& label, std::any& data, uint32_t flags) const
	{
		// TODO
		return false;
	}

	bool ArrayPropertyDrawer::Draw(const std::string& label, void* data, size_t typeHash, uint32_t flags) const
	{
		if (data == nullptr)
		{
			ImGui::Text("Error");
			return false;
		}

		bool change = false;

		float width = ImGui::GetContentRegionAvail().x;
		float inputWidth = 10.0f;
		width -= inputWidth;

		ImGui::SetNextItemWidth(width);

		ListView listView{ label.data() };

		size_t size = GloryReflect::Reflect::ArraySize(data, typeHash);
		const GloryReflect::TypeData* pElementTypeData = GloryReflect::Reflect::GetTyeData(typeHash);
		PropertyDrawer* pPropertyDrawer = PropertyDrawer::GetPropertyDrawer(typeHash);

		listView.OnDrawElement = [&](size_t index) {
			void* pAddress = GloryReflect::Reflect::ElementAddress(data, typeHash, index);
			if (pPropertyDrawer)
			{
				change |= pPropertyDrawer->Draw(ICON_FA_CIRCLE " Element " + std::to_string(index), pAddress, typeHash, flags);
				return;
			}
			
			change |= PropertyDrawer::DrawProperty(ICON_FA_CIRCLE " Element " + std::to_string(index), pElementTypeData, pAddress, flags);
		};

		listView.OnAdd = [&]() {
			GloryReflect::Reflect::ResizeArray(data, typeHash, size + 1);
		};

		listView.OnRemove = [&](int index) {
			// Do nothing for now because GloryReflect is missing a feature for this
			// TODO: Implement
		};

		listView.OnResize = [&](size_t newSize) {
			GloryReflect::Reflect::ResizeArray(data, typeHash, newSize);
		};

		return listView.Draw(size);

		//ImGui::PushID(label.c_str());
		//std::string nodeLabel = "##" + label;
		//bool node = ImGui::TreeNodeEx(nodeLabel.c_str(), 0);
		//ImGui::SameLine(0, 0);
		//ImGui::TextUnformatted(label.c_str());
		//ImGui::SameLine(width);
		//
		//size_t size = GloryReflect::Reflect::ArraySize(data, typeHash);
		//int newSize = (int)size;
		//if (ImGui::InputInt("##size", &newSize, 0, 0, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue) && size != (size_t)newSize)
		//{
		//	if (newSize <= 0) newSize = 0;
		//	GloryReflect::Reflect::ResizeArray(data, typeHash, newSize);
		//	change = true;
		//}
		//
		//const GloryReflect::TypeData* pElementTypeData = GloryReflect::Reflect::GetTyeData(typeHash);
		//
		//PropertyDrawer* pPropertyDrawer = PropertyDrawer::GetPropertyDrawer(typeHash);
		//
		//if (node)
		//{
		//	for (size_t i = 0; i < newSize; i++)
		//	{
		//		void* pAddress = GloryReflect::Reflect::ElementAddress(data, typeHash, i);
		//		std::string elementLabel = "Element_" + std::to_string(i);
		//		ImGui::PushID(elementLabel.c_str());
		//		if (pPropertyDrawer)
		//		{
		//			change |= pPropertyDrawer->Draw(elementLabel, pAddress, typeHash, flags);
		//			ImGui::PopID();
		//			continue;
		//		}
		//
		//		change |= PropertyDrawer::DrawProperty(elementLabel, pElementTypeData, pAddress, flags);
		//		ImGui::PopID();
		//	}
		//
		//	ImGui::TreePop();
		//}
		//ImGui::PopID();
		return change;
	}
}