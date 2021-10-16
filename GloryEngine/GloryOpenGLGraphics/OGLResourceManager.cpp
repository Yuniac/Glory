#include "OGLResourceManager.h"
#include "GLBuffer.h"
#include "GLMesh.h"
#include <GL/glew.h>
#include "GLShader.h"
#include "OGLMaterial.h"
#include "GLTexture.h"

namespace Glory
{
	OGLResourceManager::OGLResourceManager()
	{
	}

	OGLResourceManager::~OGLResourceManager()
	{
	}

	Mesh* OGLResourceManager::CreateMesh_Internal(MeshData* pMeshData)
	{
		const AttributeType* attributeTypes = pMeshData->AttributeTypes();
		std::vector<AttributeType> attributes = std::vector<AttributeType>(pMeshData->AttributeCount());
		for (size_t i = 0; i < attributes.size(); i++)
			attributes[i] = attributeTypes[i];

		return new GLMesh(pMeshData->VertexCount(), pMeshData->IndexCount(), InputRate::Vertex, 0, pMeshData->VertexSize(), attributes);
	}

	Buffer* OGLResourceManager::CreateVertexBuffer(uint32_t bufferSize)
	{
		return CreateBuffer(bufferSize, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	}

	Buffer* OGLResourceManager::CreateIndexBuffer(uint32_t bufferSize)
	{
		return CreateBuffer(bufferSize, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
	}

	Buffer* OGLResourceManager::CreateBuffer_Internal(uint32_t bufferSize, uint32_t usageFlag, uint32_t memoryFlags)
	{
		return new GLBuffer(bufferSize, usageFlag, memoryFlags);
	}

	Shader* OGLResourceManager::CreateShader_Internal(FileData* pShaderFile, const ShaderType& shaderType, const std::string& function)
	{
		return new GLShader(pShaderFile, shaderType, function);
	}

	Material* OGLResourceManager::CreateMaterial_Internal(MaterialData* pMaterialData)
	{
		return new OGLMaterial(pMaterialData);
	}

	Texture* OGLResourceManager::CreateTexture_Internal(ImageData* pImageData)
	{
		return new GLTexture(pImageData->GetWidth(), pImageData->GetHeight(), pImageData->GetFormat(), ImageType::IT_2D, 0, 0, ImageAspect::IA_Color);
	}
}