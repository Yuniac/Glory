#pragma once
#include "Layer.h"
#include <vector>
#include <unordered_map>

namespace Glory
{
	class LayerManager
	{
	public:
		static void AddLayer(const std::string& name);
		static void Load();
		static void Save();

		static const Layer* GetLayerByName(const std::string& name);
		static std::string LayerMaskToString(const LayerMask& layerMask);

		static int GetLayerIndex(const Layer* pLayer);
		static void GetAllLayerNames(std::vector<std::string>& names);
		static const Layer* GetLayerAtIndex(int index);

	private:
		static void CreateDefaultLayers();

	private:
		LayerManager();
		virtual ~LayerManager();

	private:
		friend class Engine;
		static std::vector<Layer> m_Layers;
		static std::unordered_map<std::string, size_t> m_NameToLayer;
	};
}