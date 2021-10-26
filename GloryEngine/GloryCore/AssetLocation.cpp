#include "AssetLocation.h"

namespace Glory
{
	AssetLocation::AssetLocation()
		: m_Path(""), m_Index(0), m_IsSubAsset(false), m_pResourceMeta(nullptr)
	{
	}

	AssetLocation::AssetLocation(const std::string& path, size_t index, ResourceMeta* pMeta)
		: m_Path(path), m_Index(index), m_IsSubAsset(true), m_pResourceMeta(pMeta)
	{
	}

	AssetLocation::AssetLocation(const std::string& fullPath, ResourceMeta* pMeta) : m_pResourceMeta(pMeta)
	{
		int seperatorIndex = fullPath.find(':');
		if (seperatorIndex == std::string::npos)
		{
			m_Path = fullPath;
			m_Index = 0;
			m_IsSubAsset = false;
			return;
		}

		m_IsSubAsset = true;
		m_Path = fullPath.substr(0, seperatorIndex);
		std::string indexString = fullPath.substr(seperatorIndex + 1);
		std::istringstream reader(indexString);
		reader >> m_Index;
	}
}
