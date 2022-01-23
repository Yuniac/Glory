#include <VertexHelpers.h>
#include <FileLoaderModule.h>
#include <ios>
#include <Material.h>
#include <Engine.h>
#include "EntitySceneScenesModule.h"
#include "Entity.h"
#include "Systems.h"
#include "ModelLoaderModule.h"
#include "ImageLoaderModule.h"
#include "EntitySceneObject.h"
#include <Engine.h>
#include <MaterialInstanceData.h>

namespace Glory
{
	EntitySceneScenesModule::EntitySceneScenesModule()
	{
	}

	EntitySceneScenesModule::~EntitySceneScenesModule()
	{
	}

	GScene* EntitySceneScenesModule::CreateScene(const std::string& sceneName)
	{
		return new EntityScene(sceneName);
	}

	GScene* EntitySceneScenesModule::CreateScene(const std::string& sceneName, UUID uuid)
	{
		return new EntityScene(sceneName, uuid);
	}

	void EntitySceneScenesModule::Initialize()
	{
	}

	void EntitySceneScenesModule::PostInitialize()
	{
		// dis is a test pls ignore
		EntityScene* pScene = (EntityScene*)CreateEmptyScene();

		FileImportSettings importSettings;
		importSettings.Flags = (int)(std::ios::ate | std::ios::binary);
		
		ModelImportSettings modelImportSettings;
		modelImportSettings.m_Extension = "fbx";
		
		FileData* pFile = (FileData*)m_pEngine->GetLoaderModule<FileData>()->Load("./Models/Sphere.fbx", importSettings);
		ModelData* pModel = (ModelData*)m_pEngine->GetModule<ModelLoaderModule>()->Load(pFile->Data(), pFile->Size(), modelImportSettings);
		delete pFile;

		pFile = (FileData*)m_pEngine->GetLoaderModule<FileData>()->Load("./Models/BigPlane.fbx", importSettings);
		ModelData* pPlaneModel = (ModelData*)m_pEngine->GetModule<ModelLoaderModule>()->Load(pFile->Data(), pFile->Size(), modelImportSettings);
		delete pFile;
		
		ImageImportSettings imageImportSettings;
		imageImportSettings.m_Extension = "png";
		
		pFile = (FileData*)m_pEngine->GetLoaderModule<FileData>()->Load("./Resources/viking_room_1.png", importSettings);
		ImageData* pTexture = (ImageData*)m_pEngine->GetModule<ImageLoaderModule>()->Load(pFile->Data(), pFile->Size());
		delete pFile;
		
		importSettings.AddNullTerminateAtEnd = true;
		FileData* pVert = (FileData*)m_pEngine->GetModule<FileLoaderModule>()->Load("./Shaders/texturetest.vert", importSettings);
		FileData* pFrag = (FileData*)m_pEngine->GetModule<FileLoaderModule>()->Load("./Shaders/texturetest.frag", importSettings);
		
		std::vector<FileData*> pShaderFiles = { pVert, pFrag };
		std::vector<ShaderType> shaderTypes = { ShaderType::ST_Vertex, ShaderType::ST_Fragment };
		
		m_pMaterialData = new MaterialData(pShaderFiles, shaderTypes);

		m_pMaterialData->AddProperty(MaterialPropertyData("_u_fragScalar", 1.0f));
		m_pMaterialData->AddProperty(MaterialPropertyData("texSampler", pTexture));
		
		EntitySceneObject* pPlaneObject = (EntitySceneObject*)pScene->CreateEmptyObject();
		Entity& planeEntity = pPlaneObject->GetEntityHandle();
		planeEntity.AddComponent<MeshFilter>(pPlaneModel);
		planeEntity.AddComponent<MeshRenderer>(m_pMaterialData);
		Transform& transform = planeEntity.GetComponent<Transform>();
		transform.Rotation = glm::quat(glm::vec3(glm::radians(-90.0f), 0.0f, 0.0f));

		EntitySceneObject* pObject1 = (EntitySceneObject*)pScene->CreateEmptyObject();
		Entity& entity = pObject1->GetEntityHandle();
		entity.AddComponent<LookAt>(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		entity.AddComponent<CameraComponent>(45.0f, 0.1f, 10.0f, 0, -5);
		
		//entity = ((EntitySceneObject*)pScene->CreateEmptyObject())->GetEntityHandle();
		//entity.AddComponent<LookAt>(glm::vec3(-2.0f, -2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//entity.AddComponent<CameraComponent>(45.0f, 0.1f, 10.0f, 0, -5);

		//EntitySceneObject* pObject = (EntitySceneObject*)pScene->CreateEmptyObject();
		//Entity& entity1 = pObject->GetEntityHandle();
		//entity1.GetComponent<Transform>().Position = glm::vec3(5.0f, 0.0f, 0.0f);
		//entity1.AddComponent<LayerComponent>();
		//entity1.AddComponent<MeshFilter>(pModel);
		////MaterialInstanceData* pMaterial = new MaterialInstanceData(m_pMaterialData);
		//entity1.AddComponent<MeshRenderer>(m_pMaterialData);
		////entity1.AddComponent<Spin>(0.1f);

		for (int i = -4; i < 4; i++)
		{
			for (int j = -4; j < 4; j++)
			{
				EntitySceneObject* pObject = (EntitySceneObject*)pScene->CreateEmptyObject();
				Entity& entity1 = pObject->GetEntityHandle();
				entity1.GetComponent<Transform>().Position = glm::vec3(i * 5.0f, 0.5f, j * 5.0f);
				entity1.AddComponent<LayerComponent>();
				entity1.AddComponent<MeshFilter>(pModel);
		
				MaterialInstanceData* pMaterial = new MaterialInstanceData(m_pMaterialData);
				entity1.AddComponent<MeshRenderer>(pMaterial);
				entity1.AddComponent<Spin>(0.1f);
			}
		}
	}

	void EntitySceneScenesModule::OnCleanup()
	{
	}
}
