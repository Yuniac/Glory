#include "GloryMonoScipting.h"
#include "CoreCSAPI.h"
#include "MathCSAPI.h"
#include "InputCSAPI.h"
#include "MonoLibManager.h"
#include "MonoManager.h"
#include "CoreLibManager.h"
#include <Game.h>

namespace Glory
{
	GLORY_MODULE_VERSION_CPP(GloryMonoScipting, 0, 1);

	GloryMonoScipting::GloryMonoScipting() : ScriptingModuleTemplate("csharp"), m_pCoreLibManager(new CoreLibManager())
	{
	}

	GloryMonoScipting::~GloryMonoScipting()
	{
		delete m_pCoreLibManager;
		m_pCoreLibManager = nullptr;
	}

	void GloryMonoScipting::Initialize()
	{
		m_pEngine->GetScriptingExtender()->RegisterExtender(this, this);
		MonoManager::Initialize("./Modules/GloryMonoScripting/Dependencies");
	}

	void GloryMonoScipting::SetMonoDirs(const std::string& assemblyDir, const std::string& configDir)
	{
		mono_set_dirs(assemblyDir.c_str(), configDir.c_str());
	}

	void GloryMonoScipting::PostInitialize()
	{
	}

	void GloryMonoScipting::InitializeScripting()
	{
		//AssemblyBinding* pAssembly = MonoLibManager::GetAssembly("GloryEngine.Core.dll");
		//MonoClass* pMainClass = mono_class_from_name(pAssembly->GetMonoImage(), "Glory", "GloryCSMain");
		//mono_bool result = mono_class_init(pMainClass);
		//MonoObject* pMonoObject1 = mono_object_new(mono_domain_get(), pMainClass);
		//
		//MonoMethodDesc* pMainFuncDesc = mono_method_desc_new(".GloryMain:main()", false);
		//MonoMethod* pMainFunc = mono_method_desc_search_in_class(pMainFuncDesc, pMainClass);
		//// Exception object
		//MonoObject* pExObject = nullptr;
		//MonoObject* pMonoObject = mono_runtime_invoke(pMainFunc, nullptr, nullptr, &pExObject);
		//uint32_t monoObjectGCHandle = mono_gchandle_new(pMonoObject, false);
		//mono_method_desc_free(pMainFuncDesc);
	}

	void GloryMonoScipting::Cleanup()
	{
		MonoManager::Cleanup();
	}

	void GloryMonoScipting::LoadLib(const ScriptingLib& library)
	{
		MonoManager::LoadLib(library);
	}

	void GloryMonoScipting::Bind(const InternalCall& internalCall)
	{
		const std::string& scriptMethod = internalCall.ScriptMethod();
		mono_add_internal_call(scriptMethod.c_str(), internalCall.RedirectMethod());
	}

	std::string GloryMonoScipting::Language()
	{
		return ScriptingLanguage();
	}

	void GloryMonoScipting::GetInternalCalls(std::vector<InternalCall>& internalCalls)
	{
		CoreCSAPI::AddInternalCalls(internalCalls);
		MathCSAPI::AddInternalCalls(internalCalls);
		InputCSAPI::AddInternalCalls(internalCalls);
	}

	void GloryMonoScipting::GetLibs(ScriptingExtender* pScriptingExtender)
	{
		pScriptingExtender->AddInternalLib("GloryEngine.Core.dll", m_pCoreLibManager);
	}
}
