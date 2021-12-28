#include "CameraRef.h"
#include "CameraManager.h"

namespace Glory
{
	CameraRef::CameraRef() : m_CameraID()
	{
	}

	CameraRef::CameraRef(UUID uuid) : m_CameraID(uuid)
	{
	}

	bool CameraRef::operator<(const CameraRef& other) const
	{
		return GetPriority() < other.GetPriority();
	}

	void CameraRef::SetResolution(int width, int height)
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return;
		pCamera->SetResolution(width, height);
	}

	void CameraRef::SetPerspectiveProjection(int width, int height, float halfFOV, float near, float far)
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return;
		pCamera->SetPerspectiveProjection(width, height, halfFOV, near, far);
	}

	void CameraRef::SetView(const glm::mat4& view)
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return;
		pCamera->SetView(view);
	}

	void CameraRef::SetDisplayIndex(int index)
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return;
		pCamera->SetDisplayIndex(index);
	}

	void CameraRef::SetPriority(int priority)
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return;
		pCamera->SetPriority(priority);
	}

	void CameraRef::SetLayerMask(const LayerMask& layerMask)
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return;
		pCamera->SetLayerMask(layerMask);
	}

	void CameraRef::SetClearColor(const glm::vec4& clearColor)
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return;
		pCamera->SetClearColor(clearColor);
	}

	const glm::mat4& CameraRef::GetView() const
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return glm::mat4();
		return pCamera->GetView();
	}

	const glm::mat4& CameraRef::GetProjection() const
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return glm::mat4();
		return pCamera->GetProjection();
	}

	int CameraRef::GetDisplayIndex() const
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return -1;
		return pCamera->GetDisplayIndex();
	}

	int CameraRef::GetPriority() const
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return -1;
		return pCamera->GetPriority();
	}

	const glm::vec4& CameraRef::GetClearColor() const
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return glm::vec4(0.0f);
		return pCamera->GetClearColor();
	}

	const LayerMask& CameraRef::GetLayerMask() const
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return 0;
		return pCamera->GetLayerMask();
	}

	RenderTexture* CameraRef::GetRenderTexture() const
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return nullptr;
		return pCamera->GetRenderTexture();
	}

	void CameraRef::Free()
	{
		Camera* pCamera = CameraManager::GetCamera(m_CameraID);
		if (pCamera == nullptr) return;
		CameraManager::SetUnused(pCamera);
	}
}