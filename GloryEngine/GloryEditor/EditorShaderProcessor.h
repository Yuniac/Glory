#pragma once
#include "EditorShaderData.h"
#include <ShaderSourceData.h>
#include <ThreadManager.h>
#include <map>
#include <filesystem>
#include <shaderc.hpp>
#include <ThreadedVar.h>
#include <ResourceMeta.h>

namespace Glory::Editor
{
	class EditorShaderProcessor
	{
	public:
		static EditorShaderData* GetShaderSource(ShaderSourceData* pShaderSource);

	private:
		EditorShaderProcessor();
		virtual ~EditorShaderProcessor();

		void Start();
		void Stop();
		void ThreadLoop();

		EditorShaderData* CompileAndCache(ShaderSourceData* pShaderSource, std::filesystem::path path);
		EditorShaderData* LoadCache(ShaderSourceData* pShaderSource, std::filesystem::path path);

	private:
		void CompileForCurrentPlatform(EditorShaderData* pEditorShader, const std::string& path);
		void ProcessReflection(EditorShaderData* pEditorShader, ShaderSourceData* pShaderSource);

		static void AssetRegisteredCallback(UUID uuid, const ResourceMeta& meta, Resource* pResource);

	private:
		friend class EditorApplication;
		static std::map<UUID, EditorShaderData*> m_pLoadedShaderData;
		static std::queue<ShaderSourceData*> m_ProcessShadersQueue;
		static std::condition_variable m_QueueCondition;
		static std::mutex m_QueueLock;
		static ThreadedUMap<UUID, std::function<void(FileData*)>> m_WaitingCallbacks;
		static ThreadedVector<std::function<void(FileData*)>> m_Callbacks;
		bool m_Exit = false;
		Thread* m_pThread;

		std::map<ShaderType, shaderc_shader_kind> m_ShaderTypeToKind;
	};
}
