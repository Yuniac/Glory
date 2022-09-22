project "GloryCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	targetdir ("%{engineoutdir}")
	objdir ("%{cfg.buildcfg}/%{cfg.platform}")

	files
	{
		"**.h",
		"**.cpp"
	}

	vpaths
	{
		["Asset Management"] = { "AssetDatabase.*", "AssetGroup.*", "AssetLocation.*", "AssetManager.*", "ResourceMeta.*", "ResourceType.*", "ShaderManager.*", "AssetCallbacks.*" },
		["Console"] = { "Commands.*", "Console.*", "Debug.*", "DebugConsoleInput.*", "IConsole.*", "WindowsDebugConsole.*" },
		["Core"] = { "CoreExceptions.*", "Engine.*", "Game.*", "GameSettings.*", "GameState.*", "GloryCore.*", "GraphicsThread.*", "Object.*", "UUID.*", "Glory.*" },
		["Job System"] = { "Job.*", "JobManager.*", "JobPool.*", "JobQueue.*" },
		["Modules"] = { "Module.*" },
		["Modules/Time"] = { "TimerModule.*", "GameTime.*" },
		["Modules/Graphics"] = { "GraphicsModule.*" },
		["Modules/Graphics/Data"] = { "GraphicsEnums.*", "GraphicsMemoryManager.*" },
		["Modules/Graphics/Geometry"] = { "VertexDefinitions.*", "VertexHelpers.*" },
		["Modules/Graphics/Rendering"] = { "FrameState.*", "RenderFrame.*", "RenderQueue.*" },
		["Modules/Graphics/Resources"] = { "Buffer.*", "GPUResource.*", "GPUResourceManager.*", "Material.*", "Mesh.*", "Shader.*", "Texture.*", "RenderTexture.*" },
		["Modules/Renderer"] = { "RenderData.*", "RendererModule.*", "FrameStates.*" },
		["Modules/Renderer/Camera"] = { "Camera.*", "CameraManager.*", "DisplayManager.*", "CameraRef.*" },
		["Modules/Renderer/Layers"] = { "Layer.*", "LayerManager.*", "LayerMask.*" },
		["Modules/Renderer/Lighting"] = { "LightData.*" },
		["Modules/ResourceLoading"] = {  },
		["Modules/ResourceLoading/Base"] = { "ImportSettings.*", "Resource.*", "ResourceLoaderModule.*" },
		["Modules/ResourceLoading/File"] = { "FileData.*", "FileLoaderModule.*" },
		["Modules/ResourceLoading/Material"] = { "MaterialData.*", "MaterialPropertyData.*", "MaterialInstanceData.*", "MaterialInstanceLoaderModule.*", "MaterialLoaderModule.*", "MaterialPropertyInfo.*" },
		["Modules/ResourceLoading/Models"] = { "MeshData.*", "ModelData.*", "ModelLoaderModule.*" },
		["Modules/ResourceLoading/Shaders"] = { "ShaderCrossCompiler.*", "ShaderData.*", "ShaderLoaderModule.*", "ShaderSourceData.*", "ShaderSourceLoaderModule.*" },
		["Modules/ResourceLoading/Textures"] = { "ImageData.*", "ImageLoaderModule.*" },
		["Modules/Scenes"] = { "ScenesModule.*", "SceneObject.*", "GScene.*" },
		["Modules/Window"] = { "Window.*", "WindowModule.*" },
		["Modules/Scripting"] = { "Script.*", "ScriptingModule.*", "ScriptLoaderModule.*", "ScriptBinding.*", "ScriptingBinder.*", "IScriptExtender.*" },
		["Threading"] = { "Thread.*", "ThreadManager.*", "ThreadedVar.*" },
		["Analysis"] = { "EngineProfiler.*", "ProfilerModule.*", "ProfilerSample.*", "ProfilerThreadSample.*" },
		["Helpers"] = { "GLORY_YAML.*", "YAML_GLM.*" },
		["Serialization"] = { "PropertyFlags.*", "PropertySerializer.*", "SerializedProperty.*", "Serializer.*", "AssetReferencePropertySerializer.*", "SerializedArrayProperty.*", "SerializedPropertyManager.*", "SerializedTypes.*", "ArrayPropertySerializers.*", "AnyConverter.*", "AssetReferencePropertyTemplate.*" },
	}

	includedirs
	{
		"%{mono_install}/include/mono-2.0",
		"%{vulkan_sdk}/third-party/include",
		"%{IncludeDir.shaderc}",
		"%{IncludeDir.spirv_cross}",
		"%{IncludeDir.yaml_cpp}",
	}

	defines
	{
		"GLORY_EXPORTS",
		"GLORY_CORE_EXPORTS",
	}

	filter "system:windows"
		systemversion "10.0.19041.0"
		toolset "v142"

		defines
		{
			"_LIB"
		}

	filter "platforms:Win32"
		architecture "x86"
		defines "WIN32"

	filter "platforms:x64"
		architecture "x64"

	filter "configurations:Debug"
		runtime "Debug"
		defines "_DEBUG"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		defines "NDEBUG"
		optimize "On"
