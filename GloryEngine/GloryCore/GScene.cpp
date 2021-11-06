#include "GScene.h"
#include <algorithm>

namespace Glory
{
	GScene::GScene() : m_SceneName("New Scene")
	{
	}

	GScene::GScene(const std::string& sceneName) : m_SceneName(sceneName)
	{
	}

	GScene::GScene(const std::string& sceneName, UUID uuid) : Resource(uuid), m_SceneName(sceneName)
	{
	}

	GScene::~GScene()
	{
		std::for_each(m_pSceneObjects.begin(), m_pSceneObjects.end(), [](SceneObject* pObject) { delete pObject; });
	}

	SceneObject* GScene::CreateEmptyObject()
	{
		SceneObject* pObject = CreateObject("Empty Object");
		pObject->Initialize();
		m_pSceneObjects.push_back(pObject);
		return pObject;
	}

	size_t GScene::SceneObjectsCount()
	{
		return m_pSceneObjects.size();
	}

	SceneObject* GScene::GetSceneObject(size_t index)
	{
		if (index >= m_pSceneObjects.size()) return nullptr;
		return m_pSceneObjects[index];
	}
}