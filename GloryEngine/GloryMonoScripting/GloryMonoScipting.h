#pragma once
#include <ScriptingModule.h>
#include <mono/jit/jit.h>
#include "MonoScript.h"
#include "AssemblyBinding.h"
#include "MonoScriptLoader.h"

#define BIND(x, y) bindings.push_back(ScriptBinding("C#", x, &y))

namespace Glory
{
	class GloryMonoScipting : public ScriptingModuleTemplate<MonoScript, MonoScriptLoader>
	{
    public:
        GloryMonoScipting();
        virtual ~GloryMonoScipting();

        void SetMonoDirs(const std::string& assemblyDir, const std::string& configDir);
        void InitializeDomainAndMainAssembly();

    private:
        virtual void Initialize() override;
        virtual void PostInitialize() override;
        virtual void Cleanup() override;

        void GetScriptBindings(std::vector<ScriptBinding>& bindings) override;
        void Bind(const ScriptBinding& binding) override;

    private:
        MonoDomain* m_pDomain;
        std::vector<AssemblyBinding> m_Assemblies;
	};
}
