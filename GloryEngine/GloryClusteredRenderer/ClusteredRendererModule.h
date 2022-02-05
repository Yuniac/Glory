#pragma once
#include <RendererModule.h>
#include <Material.h>
#include <MaterialData.h>
#include <FileData.h>
#include <glm/glm.hpp>


















#include <GL/glew.h>
#include <OpenGLGraphicsModule.h>
#include <OGLMaterial.h>
#include <GLTexture.h>

namespace Glory
{
	struct VolumeTileAABB
	{
		glm::vec4 MinPoint;
		glm::vec4 MaxPoint;
	};

	struct ScreenToView
	{
		glm::mat4 ProjectionInverse;
		glm::mat4 ViewInverse;
		glm::uvec4 TileSizes;
		glm::uvec2 ScreenDimensions;
		float Scale;
		float Bias;
	};

	struct LightGrid
	{
		uint32_t Offset;
		uint32_t Count;
	};

	class ClusteredRendererModule : public RendererModule
	{
	public:
		ClusteredRendererModule();
		virtual ~ClusteredRendererModule();

		virtual RenderTexture* CreateCameraRenderTexture(size_t width, size_t height) override;
		virtual void OnCameraResize(CameraRef camera) override;

	private:
		virtual void Initialize() override;
		virtual void Cleanup() override;
		virtual void PostInitialize() override;

		virtual void OnThreadedInitialize() override;
		virtual void OnThreadedCleanup() override;

		virtual void OnRender(CameraRef camera, const RenderData& renderData, const std::vector<PointLight>& lights = std::vector<PointLight>()) override;
		virtual void OnDoScreenRender(CameraRef camera, const std::vector<PointLight>& lights, size_t width, size_t height, RenderTexture* pRenderTexture) override;

		virtual void OnStartCameraRender(CameraRef camera, const std::vector<PointLight>& lights) override;
		virtual void OnEndCameraRender(CameraRef camera, const std::vector<PointLight>& lights) override;

	private:
		void CreateMesh();
		size_t GetGCD(size_t a, size_t b); // TODO: Move this to somewhere it can be used from anywhere and make it take templates

		void GenerateClusterSSBO(Buffer* pBuffer, CameraRef camera, const glm::uvec3& gridSize, const glm::uvec2& resolution);

	private:
		// Compute shaders
		FileData* m_pClusterShaderFile;
		MaterialData* m_pClusterShaderMaterialData;
		Material* m_pClusterShaderMaterial;
		
		FileData* m_pMarkActiveClustersShaderFile;
		MaterialData* m_pMarkActiveClustersMaterialData;
		Material* m_pMarkActiveClustersMaterial;

		FileData* m_pCompactClustersShaderFile;
		MaterialData* m_pCompactClustersMaterialData;
		Material* m_pCompactClustersMaterial;

		FileData* m_pClusterCullLightShaderFile;
		MaterialData* m_pClusterCullLightMaterialData;
		Material* m_pClusterCullLightMaterial;

		// Data for clustering
		Buffer* m_pScreenToViewSSBO;
		Buffer* m_pLightsSSBO;

		static const size_t m_GridSizeX = 16;
		static const size_t m_GridSizeY = 9;
		static const size_t NUM_DEPTH_SLICES = 24;
		static const size_t NUM_CLUSTERS = m_GridSizeX * m_GridSizeY * NUM_DEPTH_SLICES;
		static const size_t MAX_LIGHTS_PER_TILE = 50;

		// Screen rendering
		MaterialData* m_pScreenMaterial;

		GLuint m_ScreenQuadVertexArrayID;
		GLuint m_ScreenQuadVertexbufferID;

		bool m_HasMesh = false;
	};
}
