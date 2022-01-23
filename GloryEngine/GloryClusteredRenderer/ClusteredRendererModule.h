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
		glm::vec4 minPoint;
		glm::vec4 maxPoint;
	};

	struct ScreenToView
	{
		glm::mat4 inverseProjection;
		glm::uvec4 tileSizes;
		glm::uvec2 screenDimensions;
	};

	class ClusteredRendererModule : public RendererModule
	{
	public:
		ClusteredRendererModule();
		virtual ~ClusteredRendererModule();

		virtual RenderTexture* CreateCameraRenderTexture(size_t width, size_t height) override;

	private:
		virtual void Initialize() override;
		virtual void Cleanup() override;
		virtual void PostInitialize() override;

		virtual void OnThreadedInitialize() override;
		virtual void OnThreadedCleanup() override;

		virtual void OnRender(CameraRef camera, const RenderData& renderData) override;
		virtual void OnDoScreenRender(size_t width, size_t height, RenderTexture* pRenderTexture) override;

		virtual void OnStartCameraRender(CameraRef camera) override;
		virtual void OnEndCameraRender(CameraRef camera) override;

	private:
		void CreateMesh();

		void CalculateActiveClusters();

	private:
		FileData* m_pClusterShaderFile;
		MaterialData* m_pClusterShaderMaterialData;
		Material* m_pClusterShaderMaterial;
		
		FileData* m_pMarkActiveClustersShaderFile;
		MaterialData* m_pMarkActiveClustersMaterialData;
		Material* m_pMarkActiveClustersMaterial;

		FileData* m_pCompactClustersShaderFile;
		MaterialData* m_pCompactClustersMaterialData;
		Material* m_pCompactClustersMaterial;

		Buffer* m_pClusterSSBO;
		Buffer* m_pScreenToViewSSBO;
		Buffer* m_pActiveClustersSSBO;
		Buffer* m_pActiveUniqueClustersSSBO;
		bool m_ClusterGenerated;

		static const size_t m_GridSizeX = 16;
		static const size_t m_GridSizeY = 9;
		static const size_t m_GridSizeZ = 24;
		static const size_t NUMCLUSTERS = m_GridSizeX * m_GridSizeY * m_GridSizeZ;
		size_t m_SizeX = 24;

		GLuint m_DepthBuffer;






		MaterialData* m_pScreenMaterial;

		GLuint m_ScreenQuadVertexArrayID;
		GLuint m_ScreenQuadVertexbufferID;

		bool m_HasMesh = false;
	};
}
