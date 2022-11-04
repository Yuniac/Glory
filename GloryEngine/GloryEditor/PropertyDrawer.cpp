#include "PropertyDrawer.h"
#include "AssetReferencePropertyDrawer.h"
#include <imgui.h>
#include <algorithm>

namespace Glory::Editor
{
	std::vector<PropertyDrawer*> PropertyDrawer::m_PropertyDrawers = std::vector<PropertyDrawer*>();

	GLORY_EDITOR_API PropertyDrawer::PropertyDrawer(size_t typeHash) : m_TypeHash(typeHash)
	{
	}

	GLORY_EDITOR_API PropertyDrawer::~PropertyDrawer()
	{
	}

	GLORY_EDITOR_API bool PropertyDrawer::Draw(const SerializedProperty* serializedProperty, const std::string& label, void* data, size_t typeHash, uint32_t flags) const
	{
		ImGui::Text(label.data());
		return false;
	}

	GLORY_EDITOR_API bool PropertyDrawer::Draw(const SerializedProperty* serializedProperty, const std::string& label, std::any& data, uint32_t flags) const
	{
		ImGui::Text(label.data());
		return false;
	}

	GLORY_EDITOR_API bool PropertyDrawer::Draw(const std::string& label, std::vector<char>& buffer, size_t typeHash, size_t offset, size_t size, uint32_t flags) const
	{
		ImGui::Text(label.data());
		return false;
	}

	bool PropertyDrawer::Draw(const std::string& label, void* data, size_t typeHash, uint32_t flags) const
	{
		ImGui::Text(label.data());
		return false;
	}

	GLORY_EDITOR_API bool PropertyDrawer::Draw(const SerializedProperty* serializedProperty) const
	{
		return Draw(serializedProperty, serializedProperty->Name(), serializedProperty->MemberPointer(), serializedProperty->ElementTypeHash(), serializedProperty->Flags());
	}

	GLORY_EDITOR_API void PropertyDrawer::RegisterPropertyDrawer(PropertyDrawer* pDrawer)
	{
		m_PropertyDrawers.push_back(pDrawer);
	}

	GLORY_EDITOR_API bool PropertyDrawer::DrawProperty(const SerializedProperty* serializedProperty, const std::string& label, void* data, size_t typeHash, size_t elementTypeHash, uint32_t flags)
	{
		auto it = std::find_if(m_PropertyDrawers.begin(), m_PropertyDrawers.end(), [&](PropertyDrawer* propertyDrawer)
			{
				return propertyDrawer->GetPropertyTypeHash() == typeHash;
			});

		if (it == m_PropertyDrawers.end())
		{
			//ImGui::Text(prop.m_Name.c_str());
			return false;
		}

		PropertyDrawer* drawer = *it;
		return drawer->Draw(serializedProperty, label, data, elementTypeHash, flags);
	}

	GLORY_EDITOR_API bool PropertyDrawer::DrawProperty(const std::string& label, std::any& data, uint32_t flags)
	{
		size_t typeHash = ResourceType::GetHash(data.type());

		auto it = std::find_if(m_PropertyDrawers.begin(), m_PropertyDrawers.end(), [&](PropertyDrawer* propertyDrawer)
		{
			return propertyDrawer->GetPropertyTypeHash() == typeHash;
		});

		if (it == m_PropertyDrawers.end())
		{
			//ImGui::Text(prop.m_Name.c_str());
			return false;
		}

		PropertyDrawer* drawer = *it;
		return drawer->Draw(nullptr, label, data, flags);
	}

	GLORY_EDITOR_API bool PropertyDrawer::DrawProperty(const SerializedProperty* serializedProperty)
	{
		return DrawProperty(serializedProperty, serializedProperty->Name(), serializedProperty->MemberPointer(), serializedProperty->TypeHash(), serializedProperty->ElementTypeHash(), serializedProperty->Flags());
	}

	GLORY_EDITOR_API bool PropertyDrawer::DrawProperty(const std::string& label, std::vector<char>& buffer, size_t typeHash, size_t offset, size_t size, uint32_t flags)
	{
		auto it = std::find_if(m_PropertyDrawers.begin(), m_PropertyDrawers.end(), [&](PropertyDrawer* propertyDrawer)
		{
			return propertyDrawer->GetPropertyTypeHash() == typeHash;
		});

		if (it == m_PropertyDrawers.end())
		{
			//ImGui::Text(prop.m_Name.c_str());
			return false;
		}

		PropertyDrawer* drawer = *it;
		return drawer->Draw(label, buffer, typeHash, offset, size, flags);
	}

	GLORY_EDITOR_API bool PropertyDrawer::DrawProperty(const std::string& label, void* data, size_t typeHash, uint32_t flags)
	{
		auto it = std::find_if(m_PropertyDrawers.begin(), m_PropertyDrawers.end(), [&](PropertyDrawer* propertyDrawer)
		{
			return propertyDrawer->GetPropertyTypeHash() == typeHash;
		});

		if (it == m_PropertyDrawers.end())
		{
			//ImGui::Text(prop.m_Name.c_str());
			return false;
		}

		PropertyDrawer* drawer = *it;
		return drawer->Draw(label, data, typeHash, flags);
	}

	GLORY_EDITOR_API bool PropertyDrawer::DrawProperty(const GloryReflect::FieldData* pFieldData, void* data, uint32_t flags, const std::string& labelID)
	{
		std::string newLabelSuffix = labelID;
		newLabelSuffix += "." + std::string(pFieldData->Name());

		size_t typeHash = pFieldData->Type();
		size_t elementTypeHash = pFieldData->ArrayElementType();

		auto it = std::find_if(m_PropertyDrawers.begin(), m_PropertyDrawers.end(), [&](PropertyDrawer* propertyDrawer)
		{
			return propertyDrawer->GetPropertyTypeHash() == typeHash;
		});

		if (it != m_PropertyDrawers.end())
		{
			PropertyDrawer* drawer = *it;
			std::string finalLabel = pFieldData->Name() + std::string("##") + newLabelSuffix;
			return drawer->Draw(finalLabel, data, elementTypeHash, flags);
		}

		const GloryReflect::TypeData* pTypeData = GloryReflect::Reflect::GetTyeData(typeHash);
		if (pTypeData)
		{
			return DrawProperty(pFieldData->Name(), pTypeData, data, flags, newLabelSuffix);
		}

		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), pFieldData->Name());
		return false;
	}

	GLORY_EDITOR_API bool PropertyDrawer::DrawProperty(const std::string& label, const GloryReflect::TypeData* pTypeData, void* data, uint32_t flags, const std::string& labelID)
	{
		if (pTypeData->FieldCount() == 1 && pTypeData->GetFieldData(0)->Type() == ST_Enum && std::string(pTypeData->GetFieldData(0)->Name()) == "m_value")
		{
			const GloryReflect::FieldData* pFieldData = pTypeData->GetFieldData(0);
			size_t offset = pFieldData->Offset();
			void* pAddress = (void*)((char*)(data)+offset);
			return PropertyDrawer::DrawProperty(label, pFieldData, pAddress, 0, labelID);
		}

		bool change = false;

		ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

		std::hash<std::string> hasher;
		size_t hash = hasher(labelID);

		bool nodeOpen = ImGui::TreeNodeEx((void*)hash, node_flags, label.data());

		if (!nodeOpen) return false;
		for (size_t i = 0; i < pTypeData->FieldCount(); i++)
		{
			const GloryReflect::FieldData* pFieldData = pTypeData->GetFieldData(i);
			size_t offset = pFieldData->Offset();
			void* pAddress = (void*)((char*)(data)+offset);
			change |= PropertyDrawer::DrawProperty(pFieldData, pAddress, 0, labelID);
		}

		ImGui::TreePop();
		return change;
	}

	GLORY_EDITOR_API bool PropertyDrawer::DrawProperty(const std::string& label, const GloryReflect::FieldData* pFieldData, void* data, uint32_t flags, const std::string& labelID)
	{
		std::string newLabelSuffix = labelID;
		newLabelSuffix += "." + label;

		size_t typeHash = pFieldData->Type();
		size_t elementTypeHash = pFieldData->ArrayElementType();

		auto it = std::find_if(m_PropertyDrawers.begin(), m_PropertyDrawers.end(), [&](PropertyDrawer* propertyDrawer)
		{
			return propertyDrawer->GetPropertyTypeHash() == typeHash;
		});

		if (it != m_PropertyDrawers.end())
		{
			PropertyDrawer* drawer = *it;
			std::string finalLabel = label + std::string("##") + newLabelSuffix;
			return drawer->Draw(finalLabel, data, elementTypeHash, flags);
		}

		const GloryReflect::TypeData* pTypeData = GloryReflect::Reflect::GetTyeData(typeHash);
		if (pTypeData)
		{
			return DrawProperty(label, pTypeData, data, flags, newLabelSuffix);
		}

		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), label.c_str());
		return false;
	}

	GLORY_EDITOR_API PropertyDrawer* PropertyDrawer::GetPropertyDrawer(size_t typeHash)
	{
		auto it = std::find_if(m_PropertyDrawers.begin(), m_PropertyDrawers.end(), [&](PropertyDrawer* propertyDrawer)
		{
			return propertyDrawer->GetPropertyTypeHash() == typeHash;
		});

		if (it == m_PropertyDrawers.end()) return nullptr;
		return *it;
	}

	GLORY_EDITOR_API size_t PropertyDrawer::GetPropertyTypeHash() const
	{
		return m_TypeHash;
	}

	void PropertyDrawer::Cleanup()
	{
		std::for_each(m_PropertyDrawers.begin(), m_PropertyDrawers.end(), [](PropertyDrawer* pDrawer) { delete pDrawer; });
		m_PropertyDrawers.clear();
	}
}
