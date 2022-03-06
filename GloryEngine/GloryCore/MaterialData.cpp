#include "MaterialData.h"
#include <algorithm>

namespace Glory
{
	std::hash<std::string> MaterialData::m_Hasher = std::hash<std::string>();

	MaterialData::MaterialData()
	{
		APPEND_TYPE(MaterialData);
	}

	MaterialData::MaterialData(const std::vector<ShaderSourceData*>& shaderFiles)
		: m_pShaderFiles(shaderFiles)
	{
		APPEND_TYPE(MaterialData);
	}

	MaterialData::~MaterialData()
	{
		m_pShaderFiles.clear();
	}

	size_t MaterialData::ShaderCount() const
	{
		return m_pShaderFiles.size();
	}

	ShaderSourceData* MaterialData::GetShaderAt(size_t index) const
	{
		return m_pShaderFiles[index];
	}

	const ShaderType& MaterialData::GetShaderTypeAt(size_t index) const
	{
		return m_pShaderFiles[index]->GetShaderType();
	}

	void MaterialData::RemoveShaderAt(size_t index)
	{
		m_pShaderFiles.erase(m_pShaderFiles.begin() + index);
	}

	void MaterialData::AddShader(ShaderSourceData* pShaderSourceData)
	{
		auto it = std::find(m_pShaderFiles.begin(), m_pShaderFiles.end(), pShaderSourceData);
		if (it != m_pShaderFiles.end()) return;
		m_pShaderFiles.push_back(pShaderSourceData);
	}

	void MaterialData::AddProperty(const MaterialPropertyData& prop)
	{
		size_t hash = m_Hasher(prop.Name());
		size_t index = m_Properties.size();
		m_Properties.push_back(prop);
		m_HashToPropertyIndex[hash] = index;
	}

	size_t MaterialData::PropertyCount() const
	{
		return m_Properties.size();
	}

	MaterialPropertyData* MaterialData::GetPropertyAt(size_t index)
	{
		return &m_Properties[index];
	}

	MaterialPropertyData MaterialData::CopyPropertyAt(size_t index)
	{
		std::unique_lock lock(m_PropertiesAccessMutex);
		return MaterialPropertyData(m_Properties[index]);
	}

	void MaterialData::CopyProperties(std::vector<MaterialPropertyData>& destination)
	{
		std::unique_lock lock(m_PropertiesAccessMutex);
		destination.clear();
		std::for_each(m_Properties.begin(), m_Properties.end(), [&](const MaterialPropertyData& propertyData)
		{
			destination.push_back(MaterialPropertyData(propertyData));
		});
		lock.unlock();
	}

	void MaterialData::PasteProperties(const std::vector<MaterialPropertyData>& destination)
	{
		std::unique_lock lock(m_PropertiesAccessMutex);
		m_Properties.clear();
		std::for_each(destination.begin(), destination.end(), [&](const MaterialPropertyData& propertyData)
		{
			m_Properties.push_back(MaterialPropertyData(propertyData));
		});
		lock.unlock();
	}

	bool MaterialData::GetPropertyIndex(const std::string& name, size_t& index) const
	{
		size_t hash = m_Hasher(name);
		if (m_HashToPropertyIndex.find(hash) == m_HashToPropertyIndex.end()) return false;
		index = m_HashToPropertyIndex.at(hash);
		return true;
	}

	void MaterialData::ReloadResourcesFromShader()
	{
		for (size_t i = 0; i < m_pShaderFiles.size(); i++)
		{
			ShaderSourceData* pShaderSource = m_pShaderFiles[i];
			const spirv_cross::ShaderResources resources = pShaderSource->GetResources();
			for (size_t i = 0; i < resources.sampled_images.size(); i++)
			{
				spirv_cross::Resource sampler = resources.sampled_images[i];
				 sampler.name;
			}
		}
	}
}
