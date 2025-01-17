#include "Mesh.h"

namespace Glory
{
	Mesh::Mesh(size_t vertexCount, size_t indexCount, InputRate inputRate, size_t binding, size_t stride, const std::vector<AttributeType>& attributeTypes) :
		m_InputRate(inputRate), m_Binding(binding), m_Stride(stride), m_VertexCount(vertexCount), m_IndexCount(indexCount), m_AttributeTypes(attributeTypes)
	{
	}

	Mesh::~Mesh()
	{
	}

    uint32_t Mesh::GetVertexCount() const
    {
        return m_VertexCount;
    }

    uint32_t Mesh::GetIndexCount() const
    {
        return m_IndexCount;
    }

    void Mesh::SetBuffers(Buffer* pVertexBuffer, Buffer* pIndexBuffer)
    {
        m_pVertexBuffer = pVertexBuffer;
        m_pIndexBuffer = pIndexBuffer;
    }

    void Mesh::GetNextOffset(const AttributeType& atributeType, uint32_t& offest)
    {
        switch (atributeType)
        {
        case AttributeType::Float:
            offest += sizeof(float);
            break;
        case AttributeType::Float2:
            offest += (sizeof(float) * 2);
            break;
        case AttributeType::Float3:
            offest += (sizeof(float) * 3);
            break;
        case AttributeType::Float4:
            offest += (sizeof(float) * 4);
            break;
        case AttributeType::UINT:
            offest += (sizeof(uint32_t));
            break;
        case AttributeType::UINT2:
            offest += (sizeof(uint32_t) * 2);
            break;
        case AttributeType::UINT3:
            offest += (sizeof(uint32_t) * 3);
            break;
        case AttributeType::UINT4:
            offest += (sizeof(uint32_t) * 4);
            break;
        case AttributeType::SINT:
            offest += (sizeof(int32_t));
            break;
        case AttributeType::SINT2:
            offest += (sizeof(int32_t) * 2);
            break;
        case AttributeType::SINT3:
            offest += (sizeof(int32_t) * 3);
            break;
        case AttributeType::SINT4:
            offest += (sizeof(int32_t) * 4);
            break;
        }
    }
}
