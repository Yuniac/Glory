project "GlorySDLWindow"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "Off"

	targetdir ("%{moduleOutDir}")
	objdir ("%{cfg.buildcfg}/%{cfg.platform}")

	files
	{
		"**.h",
		"**.cpp",
		"Module.yaml"
	}

	vpaths
	{
		["Core"] = { "SDLWindow.h", "SDLWindow.cpp", "SDLWindowExceptions.h" },
		["Module"] = { "SDLWindowModule.h", "SDLWindowModule.cpp" }
	}

	includedirs
	{
		"%{vulkan_sdk}/third-party/include",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.shaderc}",
		"%{IncludeDir.spirv_cross}",
		"%{GloryIncludeDir.core}"
	}

	libdirs
	{
		"%{LibDirs.glory}",
		"%{LibDirs.shaderc}",
		"%{LibDirs.spirv_cross}",
		"%{LibDirs.yaml_cpp}",
	}

	links
	{
		"GloryCore",
		"SDL2",
		"shaderc",
		"shaderc_combined",
		"shaderc_shared",
		"yaml-cpp",
	}

	defines
	{
		"GLORY_EXPORTS"
	}
	
	postbuildcommands
	{
		("{COPY} ./Module.yaml %{moduleOutDir}"),
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

		libdirs
		{
			"%{vulkan_sdk}/Third-Party/Bin32"
		}

		postbuildcommands
		{
			("{COPY} %{vulkan_sdk}/Third-Party/Bin32/*.dll ../Build/%{cfg.buildcfg}/%{cfg.platform}")
		}

	filter "platforms:x64"
		architecture "x64"

		libdirs
		{
			"%{vulkan_sdk}/Third-Party/Bin"
		}

		postbuildcommands
		{
			("{COPY} %{vulkan_sdk}/Third-Party/Bin/*.dll ../Build/%{cfg.buildcfg}/%{cfg.platform}")
		}

	filter "configurations:Debug"
		runtime "Debug"
		defines "_DEBUG"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		defines "NDEBUG"
		optimize "On"
