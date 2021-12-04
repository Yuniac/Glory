#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ModelData.h>
#include <MaterialData.h>
#include <Camera.h>
#include <glm/gtx/quaternion.hpp>

namespace Glory
{
	struct Transform
	{
		Transform();
		Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

		glm::vec3 Position;
		glm::quat Rotation;
		glm::vec3 Scale;

		glm::mat4 MatTransform;
	};

	struct MeshFilter
	{
		MeshFilter(ModelData* pModelData) : m_pModelData(pModelData) {}
		ModelData* m_pModelData;
	};

	struct MeshRenderer
	{
		MeshRenderer(MaterialData* pMaterial) : m_pMaterials({ pMaterial }) {}
		MeshRenderer() : m_pMaterials(std::vector<MaterialData*>()) {}
		std::vector<MaterialData*> m_pMaterials;
	};

	//enum CameraPerspective
	//{
	//	Orthographic,
	//	Perspective,
	//};

	struct Camera
	{
		Camera() : m_HalfFOV(45.0f), m_Near(0.1f), m_Far(10.0f) {}
		Camera(float halfFOV, float near, float far) : m_HalfFOV(halfFOV), m_Near(near), m_Far(far) {}
		
		float m_HalfFOV;
		float m_Near;
		float m_Far;

		CoreCamera m_Camera;

		//CameraPerspective m_Perspective;
	};

	struct LookAt
	{
		LookAt() {}
		LookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up) : m_Eye(eye), m_Center(center), m_Up(up) {}

		glm::vec3 m_Eye;
		glm::vec3 m_Center;
		glm::vec3 m_Up;
	};

	struct Spin
	{
		Spin() : m_Speed(10.0f) {}
		Spin(float speed) : m_Speed(speed) {}

		float m_Speed;
	};

	//ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//
	//int width, height;
	//pWindow->GetDrawableSize(&width, &height);

	//ubo.proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 10.0f);
	//ubo.proj[1][1] *= -1; // In OpenGL the Y coordinate of the clip coordinates is inverted, so we must flip it for use in Vulkan
}
