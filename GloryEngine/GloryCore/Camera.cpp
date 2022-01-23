#include "Camera.h"
#include <glm/ext/matrix_common.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Glory
{
	Camera::Camera(size_t width, size_t height)
		: m_DisplayIndex(0), m_Resolution(width, height), m_TextureIsDirty(true),
		m_IsInUse(true), m_View(1.0f), m_Projection(1.0f), m_pRenderTexture(nullptr),
		m_ClearColor(glm::vec4(0.0f)), m_Priority(0), m_LayerMask(0), m_Near(0.0f), m_Far(0.0f),
		m_pOutputTexture(nullptr), m_OutputEnabled(false)
	{

	}

	void Camera::SetResolution(size_t width, size_t height)
	{
		if (m_Resolution.x == width && m_Resolution.y == height) return;
		m_Resolution = glm::ivec2(width, height);
		m_TextureIsDirty = true;
	}

	void Camera::SetPerspectiveProjection(size_t width, size_t height, float halfFOV, float near, float far)
	{
		m_Near = near;
		m_Far = far;

		m_Projection = glm::perspective(glm::radians(halfFOV), (float)width / (float)height, near, far);
	}

	void Camera::SetView(const glm::mat4& view)
	{
		m_View = view;
	}

	void Camera::SetDisplayIndex(int index)
	{
		m_DisplayIndex = index;
	}

	void Camera::SetPriority(int priority)
	{
		m_Priority = priority;
	}

	void Camera::SetLayerMask(const LayerMask& layerMask)
	{
		m_LayerMask = layerMask;
	}

	void Camera::SetClearColor(const glm::vec4& clearColor)
	{
		m_ClearColor = clearColor;
	}

	void Camera::SetOutputTexture(RenderTexture* pTexture)
	{
		m_pOutputTexture = pTexture;
	}

	void Camera::EnableOutput(bool enable)
	{
		m_OutputEnabled = enable;
	}

	const glm::uvec2& Camera::GetResolution() const
	{
		return m_Resolution;
	}

	const glm::mat4& Camera::GetView() const
	{
		return m_View;
	}

	const glm::mat4& Camera::GetProjection() const
	{
		return m_Projection;
	}

	int Camera::GetDisplayIndex() const
	{
		return m_DisplayIndex;
	}

	int Camera::GetPriority() const
	{
		return m_Priority;
	}

	const glm::vec4& Camera::GetClearColor() const
	{
		return m_ClearColor;
	}

	const LayerMask& Camera::GetLayerMask() const
	{
		return m_LayerMask;
	}

	RenderTexture* Camera::GetRenderTexture() const
	{
		return m_pRenderTexture;
	}

	RenderTexture* Camera::GetOutputTexture() const
	{
		return m_pOutputTexture;
	}

	bool Camera::HasOutput() const
	{
		return m_OutputEnabled;
	}

	float Camera::GetNear() const
	{
		return m_Near;
	}

	float Camera::GetFar() const
	{
		return m_Far;
	}
}
