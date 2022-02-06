#include "AssetPickerPopup.h"
#include <imgui.h>
#include <algorithm>
#include <AssetDatabase.h>
#include <AssetManager.h>

namespace Glory::Editor
{
	bool AssetPickerPopup::m_Open = false;
	Resource** AssetPickerPopup::m_pResourcePointer = nullptr;
	size_t AssetPickerPopup::m_TypeHash = 0;

	void AssetPickerPopup::Open(size_t typeHash, Resource** pResource)
	{
		m_Open = true;
		m_TypeHash = typeHash;
		m_pResourcePointer = pResource;
	}

	void AssetPickerPopup::OnGUI()
	{
		if (m_Open)
			ImGui::OpenPopup("AssetPickerPopup");
		m_Open = false;

		if (m_TypeHash == 0) return;

		if (m_PossibleAssets.size() == 0)
			LoadAssets();

		if (ImGui::BeginPopup("AssetPickerPopup"))
		{
			ImGui::Text("Asset Picker");

			ImGui::InputText("", m_FilterBuffer, 200);

			if (m_Filter != std::string(m_FilterBuffer))
			{
				m_Filter = std::string(m_FilterBuffer);
				RefreshFilter();
			}

			if (m_Filter.length() > 0)
			{
				DrawItems(m_FilteredAssets);
			}
			else
			{
				DrawItems(m_PossibleAssets);
			}

			ImGui::EndPopup();
		}
	}

	AssetPickerPopup::AssetPickerPopup() : m_FilterBuffer("")
	{
	}

	AssetPickerPopup::~AssetPickerPopup()
	{
	}

	void AssetPickerPopup::RefreshFilter()
	{
		m_FilteredAssets.clear();
		if (m_Filter == "") return;
	
		size_t compCount = 0;
		for (size_t i = 0; i < m_PossibleAssets.size(); i++)
		{
			UUID uuid = m_PossibleAssets[i];
			std::string name = AssetDatabase::GetAssetName(uuid);
			if (name.find(m_Filter) == std::string::npos) continue;
			m_FilteredAssets.push_back(m_PossibleAssets[i]);
		}
	}

	void AssetPickerPopup::LoadAssets()
	{
		m_PossibleAssets.clear();
		m_PossibleAssets = AssetDatabase::GetAllAssetsOfType(m_TypeHash);
	}

	void AssetPickerPopup::DrawItems(const std::vector<UUID>& items)
	{
		if (ImGui::MenuItem("Noone"))
		{
			AssetSelected(nullptr);
		}

		std::for_each(items.begin(), items.end(), [&](UUID uuid)
		{
			std::string name = AssetDatabase::GetAssetName(uuid);
			if (ImGui::MenuItem(name.c_str()))
			{
				AssetManager::GetAsset(uuid, [&](Resource* pResource)
					{
						AssetSelected(pResource);
					});
			}
		});
	}

	void AssetPickerPopup::AssetSelected(Resource* pAsset)
	{
		*m_pResourcePointer = pAsset;
		m_PossibleAssets.clear();
		m_FilteredAssets.clear();
		m_pResourcePointer = nullptr;
		ImGui::CloseCurrentPopup();
	}
}