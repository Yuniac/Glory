project "EntityScenesEditorExtension"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	targetdir ("%{engineoutdir}/Extensions")
	objdir ("%{cfg.buildcfg}/%{cfg.platform}")

	files
	{
		"**.h",
		"**.cpp"
	}

	vpaths
	{
		["Extension"] = { "EntityScenesEditorExtension.h", "EntityScenesEditorExtension.cpp", "EntityComponentObject.h", "EntityComponentObject.cpp" },
		["Editors"] = { "EntitySceneObjectEditor.h", "EntitySceneObjectEditor.cpp", "DefaultComponentEditor.h", "DefaultComponentEditor.cpp", "EntityComponentEditor.h", "TransformComponentEditor.h", "TransformComponentEditor.cpp" },
	}

	includedirs
	{
		"%{vulkan_sdk}/third-party/include",

		"%{IncludeDir.ImGui}",
		"%{IncludeDir.yaml_cpp}",

		"%{GloryIncludeDir.core}",
		"%{GloryIncludeDir.editor}",
		"%{GloryIncludeDir.entityscenes}",
		"%{GloryIncludeDir.ImGui}"
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