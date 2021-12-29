#include "SceneObject.h"
#include "GScene.h"

namespace Glory
{
	SceneObject::SceneObject() : m_Name("Empty Object"), m_pScene(nullptr)
	{
		APPEND_TYPE(SceneObject);
	}

	SceneObject::SceneObject(const std::string& name) : m_Name(name), m_pScene(nullptr)
	{
		APPEND_TYPE(SceneObject);
	}

	SceneObject::SceneObject(const std::string& name, UUID uuid) : m_Name(name), Object(uuid), m_pScene(nullptr)
	{
		APPEND_TYPE(SceneObject);
	}

	SceneObject::~SceneObject()
	{
	}

	size_t SceneObject::ChildCount()
	{
		return m_pChildren.size();
	}

	SceneObject* SceneObject::GetChild(size_t index)
	{
		return m_pChildren[index];
	}

	void SceneObject::SetSiblingIndex(size_t index)
	{
		SceneObject* pParent = GetParent();

		std::vector<SceneObject*>* targetVector = &m_pChildren;
		if (pParent == nullptr)
			targetVector = &m_pScene->m_pSceneObjects;

		auto it = std::find(targetVector->begin(), targetVector->end(), this);
		if (it == targetVector->end()) return;
		targetVector->erase(it);
		targetVector->insert(targetVector->begin() + index, this);
	}

	void SceneObject::SetBeforeObject(SceneObject* pObject)
	{
		SceneObject* pParent = GetParent();

		std::vector<SceneObject*>* targetVector = &m_pScene->m_pSceneObjects;
		if (pParent != nullptr)
			targetVector = &pParent->m_pChildren;

		auto it = std::find(targetVector->begin(), targetVector->end(), this);
		if (it == targetVector->end()) return;
		targetVector->erase(it);

		auto targetIterator = std::find(targetVector->begin(), targetVector->end(), pObject);
		if (targetIterator == targetVector->end())
		{
			targetVector->push_back(this);
			return;
		}
		targetVector->insert(targetIterator, this);
	}

	void SceneObject::SetAfterObject(SceneObject* pObject)
	{
		SceneObject* pParent = GetParent();

		std::vector<SceneObject*>* targetVector = &m_pScene->m_pSceneObjects;
		if (pParent != nullptr)
			targetVector = &pParent->m_pChildren;

		auto it = std::find(targetVector->begin(), targetVector->end(), this);
		if (it == targetVector->end()) return;
		targetVector->erase(it);

		auto targetIterator = std::find(targetVector->begin(), targetVector->end(), pObject);

		if (targetIterator == targetVector->end() || targetIterator + 1 == targetVector->end())
		{
			targetVector->push_back(this);
			return;
		}
		targetVector->insert(targetIterator + 1, this);
	}

	size_t SceneObject::GetSiblingIndex()
	{
		SceneObject* pParent = GetParent();
		std::vector<SceneObject*> targetVector = m_pChildren;
		if (pParent == nullptr)
			targetVector = m_pScene->m_pSceneObjects;

		auto it = std::find(targetVector.begin(), targetVector.end(), this);
		return it - targetVector.begin();
	}

	void SceneObject::SetScene(GScene* pScene)
	{
		m_pScene = pScene;
		m_pScene->m_pSceneObjects.push_back(this);
	}

	const std::string& SceneObject::Name()
	{
		return m_Name;
	}

	void SceneObject::SetName(const std::string& name)
	{
		m_Name = name;
	}

	void SceneObject::SetParent(SceneObject* pParent)
	{
		SceneObject* pCurrentParent = GetParent();
		if (pCurrentParent != nullptr)
		{
			auto it = std::find(pCurrentParent->m_pChildren.begin(), pCurrentParent->m_pChildren.end(), this);
			if (it != pCurrentParent->m_pChildren.end())
				pCurrentParent->m_pChildren.erase(it);
		}

		if (pParent != nullptr) pParent->m_pChildren.push_back(this);
		OnSetParent(pParent);
	}
}
