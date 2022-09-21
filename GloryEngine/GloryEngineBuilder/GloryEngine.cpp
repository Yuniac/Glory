#include "GloryEngine.h"
#include <yaml-cpp/yaml.h>
#include <Debug.h>
#include <BuiltInModules.h>
#include <Console.h>
#include <WindowsDebugConsole.h>
#include <GloryContext.h>

namespace Glory
{
	typedef Module*(__cdecl* LoadModuleProc)(GloryContext*);

	EngineLoader::EngineLoader(const std::filesystem::path& cfgPath) : m_CFGPath(cfgPath)
	{
		
	}

	EngineLoader::~EngineLoader()
	{
	}

	Engine* EngineLoader::LoadEngine(const Glory::WindowCreateInfo& defaultWindow)
	{
		if (!std::filesystem::exists(m_CFGPath))
		{
			Debug::LogError("Missing Engine.yaml file in project directory!");
			return nullptr;
		}

		GloryContext::CreateContext();

		YAML::Node node = YAML::LoadFile(m_CFGPath.string());
		YAML::Node modules = node["Modules"];
		LoadModules(modules);
		YAML::Node engineInfo = node["Engine"];
		EngineCreateInfo engineCreateInfo{};
		PopulateEngineInfo(engineInfo, engineCreateInfo, defaultWindow);
		return Engine::CreateEngine(engineCreateInfo);
	}

	void EngineLoader::Unload()
	{
		m_pModules.clear();
		for (size_t i = 0; i < m_Libs.size(); i++)
		{
			FreeLibrary(m_Libs[i]);
		}
		m_Libs.clear();

		Console::Cleanup();
	}

	const std::string& EngineLoader::GetSetModule(const std::string& key)
	{
		if (m_SetModules.find(key) == m_SetModules.end()) return "";
		size_t index = m_SetModules[key];
		return m_LoadedModuleNames[index];
	}

	const size_t EngineLoader::ModuleCount() const
	{
		return m_pModules.size();
	}

	const Module* EngineLoader::GetModule(size_t index) const
	{
		return m_pModules[index];
	}

	void EngineLoader::LoadModules(YAML::Node& modules)
	{
		for (size_t i = 0; i < modules.size(); i++)
		{
			YAML::Node moduleNode = modules[i];
			std::string moduleName = moduleNode.as<std::string>();
			LoadModule(moduleName);
		}
	}

	void EngineLoader::LoadModule(const std::string& moduleName)
	{
		m_LoadedModuleNames.push_back(moduleName);

		std::filesystem::path modulePath = "./Modules";
		std::filesystem::path dllPath = modulePath.append(moduleName);
		dllPath = dllPath.append(moduleName).replace_extension(".dll");

		Debug::LogInfo("Loading module metadata: " + moduleName + "...");
		std::filesystem::path metaPath = modulePath;
		metaPath = metaPath.append("Module.yaml");
		ModuleMetaData metaData(metaPath);
		metaData.Read();

		const std::vector<std::string>& dependencies = metaData.Dependencies();
		size_t dependencyCount = dependencies.size();
		if (dependencyCount > 0)
		{
			Debug::LogInfo("Loading dependencies for module: " + moduleName + "...");
			for (size_t i = 0; i < dependencyCount; i++)
			{
				std::string dependency = dependencies[i];
				Debug::LogInfo("Loading dependency: " + dependency + "...");
				std::filesystem::path dependencyPath = modulePath;
				dependencyPath = dependencyPath.append("Dependencies").append(dependency).replace_extension(".dll");
				HMODULE dependencyLib = LoadLibrary(dependencyPath.c_str());
				if (dependencyLib == NULL)
				{
					Debug::LogFatalError("Failed to load dependency: " + dependency + ": The dll was not found!");
					m_pModules.push_back(nullptr);
					return;
				}
				m_Libs.push_back(dependencyLib);
			}
		}

		Debug::LogInfo("Loading module: " + moduleName + "...");
		HMODULE lib = LoadLibrary(dllPath.wstring().c_str());
		if (lib == NULL)
		{
			Debug::LogError("Failed to load module: " + moduleName + ": The module was not found!");
			m_pModules.push_back(nullptr);
			return;
		}

		LoadModuleProc loadProc = (LoadModuleProc)GetProcAddress(lib, "LoadModule");
		if (loadProc == NULL)
		{
			FreeLibrary(lib);
			Debug::LogError("Failed to load module: " + moduleName + ": Missing LoadModule function!");
			m_pModules.push_back(nullptr);
			return;
		}

		GloryContext* pContext = GloryContext::GetContext();
		Module* pModule = (loadProc)(pContext);
		if (pModule == nullptr)
		{
			FreeLibrary(lib);
			Debug::LogError("Failed to load module: " + moduleName + ": LoadModule returned nullptr!");
			m_pModules.push_back(nullptr);
			return;
		}

		m_pModules.push_back(pModule);
		m_Libs.push_back(lib);

		pModule->SetMetaData(metaData);
	}

	void EngineLoader::PopulateEngineInfo(YAML::Node& engineInfo, EngineCreateInfo& engineCreateInfo, const Glory::WindowCreateInfo& defaultWindow)
	{
		LoadRequiredModule<WindowModule>(engineInfo, "Window", &engineCreateInfo.pWindowModule)->SetMainWindowCreateInfo(defaultWindow);
		LoadRequiredModule<ScenesModule>(engineInfo, "SceneManagement", &engineCreateInfo.pScenesModule);
		LoadRequiredModule<RendererModule>(engineInfo, "Renderer", &engineCreateInfo.pRenderModule);
		LoadRequiredModule<GraphicsModule>(engineInfo, "Graphics", &engineCreateInfo.pGraphicsModule);

		YAML::Node optionalModulesNode = engineInfo["Optional"];
		for (size_t i = 0; i < optionalModulesNode.size(); i++)
		{
			YAML::Node indexNode = optionalModulesNode[i];
			int index = indexNode.as<int>();
			Module* pModule = m_pModules[index];
			m_pOptionalModules.push_back(pModule);
		}

		m_pOptionalModules.push_back(new Glory::FileLoaderModule());
		m_pOptionalModules.push_back(new Glory::MaterialLoaderModule());
		m_pOptionalModules.push_back(new Glory::MaterialInstanceLoaderModule());
		m_pOptionalModules.push_back(new Glory::ShaderSourceLoaderModule());

		engineCreateInfo.OptionalModuleCount = static_cast<uint32_t>(m_pOptionalModules.size());
		engineCreateInfo.pOptionalModules = m_pOptionalModules.data();
	}
}