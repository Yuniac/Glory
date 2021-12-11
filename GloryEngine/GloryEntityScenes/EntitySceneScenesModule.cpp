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
#include "MeshRenderSystem.h"
#include "CameraSystem.h"
#include "LookAtSystem.h"
#include "SpinSystem.h"
#include <Engine.h>

namespace Glory
{
	EntitySceneScenesModule::EntitySceneScenesModule() : m_Scene("Test")
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
		// Register engine systems
		m_Scene.m_Registry.RegisterSystem<TransformSystem>();
		m_Scene.m_Registry.RegisterSystem<MeshRenderSystem>();
		m_Scene.m_Registry.RegisterSystem<CameraSystem>();
		m_Scene.m_Registry.RegisterSystem<LookAtSystem>();
		m_Scene.m_Registry.RegisterSystem<SpinSystem>();
	}

	void EntitySceneScenesModule::PostInitialize()
	{
		// dis is a test pls ignore
		EntityScene* pScene = (EntityScene*)CreateEmptyScene();
		EntitySceneObject* pObject = (EntitySceneObject*)pScene->CreateEmptyObject();

		FileImportSettings importSettings;
		importSettings.Flags = (int)(std::ios::ate | std::ios::binary);
		
		ModelImportSettings modelImportSettings;
		modelImportSettings.m_Extension = "obj";
		
		FileData* pFile = (FileData*)m_pEngine->GetLoaderModule<FileData>()->Load("./Models/viking_room.obj", importSettings);
		ModelData* pModel = (ModelData*)m_pEngine->GetModule<ModelLoaderModule>()->Load(pFile->Data(), pFile->Size(), modelImportSettings);
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
		
		MaterialData* pMaterialData = new MaterialData(pShaderFiles, shaderTypes);
		pMaterialData->SetTexture(pTexture);
		
		Entity& entity = m_Scene.CreateEntity();
		entity.AddComponent<LookAt>(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		entity.AddComponent<CameraComponent>();

		m_Entity = m_Scene.CreateEntity();
		m_Entity.GetComponent<Transform>().Position = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Entity.AddComponent<MeshFilter>(pModel);
		m_Entity.AddComponent<Spin>(1.0f);
		m_Entity.AddComponent<MeshRenderer>(pMaterialData);

		modelImportSettings.m_Extension = "obj";
		pFile = (FileData*)m_pEngine->GetLoaderModule<FileData>()->Load("./Models/viking_room.obj", importSettings);
		pModel = (ModelData*)m_pEngine->GetModule<ModelLoaderModule>()->Load(pFile->Data(), pFile->Size(), modelImportSettings);
		delete pFile;

		Entity& entity2 = m_Scene.CreateEntity();
		entity2.AddComponent<MeshFilter>(pModel);
		entity2.AddComponent<Spin>(10.0f);
		entity2.AddComponent<MeshRenderer>(pMaterialData);
	}

	void EntitySceneScenesModule::OnCleanup()
	{
	}

	//void EntitySceneScenesModule::Tick()
	//{
	//	m_Scene.m_Registry.Update();
	//	//while (m_Scene.m_Registry.IsUpdating()) {}
	//}
}
