project "GloryMain"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("Build/%{cfg.buildcfg}/%{cfg.platform}")
	objdir ("%{cfg.buildcfg}/%{cfg.platform}")

	pchheader "stdafx.h"
	pchsource "stdafx.cpp"

	files
	{
		"**.h",
		"**.cpp"
	}

	vpaths
	{
		["Header Files"] = { "stdafx.h" }
		["Source Files"] = { "GloryMain.cpp", "stdafx.cpp" }
	}

	includedirs
	{
		"%{vulkan_sdk}\include",
		"%{vulkan_sdk}\third-party\include",

		"%{IncludeDir.assimp}",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.SDL_Image}",
		"%{IncludeDir.shaderc}",
		"%{IncludeDir.spirv_cross}",
		"%{IncludeDir.yaml_cpp}",

		"%{GloryIncludeDir.assimp}",
		"%{GloryIncludeDir.entityscenes}",
		"%{GloryIncludeDir.basicrenderer}",
		"%{GloryIncludeDir.glslloader}",
		"%{GloryIncludeDir.opengl}",
		"%{GloryIncludeDir.sdlimage}",
		"%{GloryIncludeDir.sdlwindow}",
		"%{GloryIncludeDir.vulkan}",
		"%{GloryIncludeDir.ImGui}",
		"%{GloryIncludeDir.core}",
		"%{GloryIncludeDir.editor}"
	}

	filter "system:windows"
		systemversion "latest"
		toolset "v142"

		defines
		{
			"_CONSOLE"
		}

	filter "platforms:x86"
		architecture "x86"
		defines "WIN32"

	filter "platforms:x64"
		architecture "x64"

	filter "configurations:Debug"
		defines "_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NDEBUG"
		optimize "On"

