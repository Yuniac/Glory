project "GlorySDLImage"
	kind "SharedLib"
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
		["Module"] = { "SDLImageLoaderModule.h", "SDLImageLoaderModule.cpp", "SDLTexture2D.h", "SDLTexture2D.cpp" }
	}

	includedirs
	{
		"%{vulkan_sdk}/third-party/include",
		"%{IncludeDir.SDL_image}",
		"%{IncludeDir.yaml_cpp}",
		"%{GloryIncludeDir.core}"
	}

	libdirs
	{
		"%{vulkan_sdk}/third-party/lib",
		"%{LibDirs.glory}",
		"%{LibDirs.SDL_image}",
		"%{LibDirs.yaml_cpp}",
	}

	links
	{
		"GloryCore",
		"SDL2",
		"SDL2_image",
		"yaml-cpp",
		"GloryEditor",
	}

	defines
	{
		"GLORY_EXPORTS"
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
