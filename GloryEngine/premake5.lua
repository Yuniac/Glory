workspace "GloryEngine"
	platforms {
		"Win32",
		"x64"
	}

	startproject "GloryASSIMPModelLoader"
	startproject "GloryBasicRenderer"
	startproject "GloryCore"
	startproject "GloryEditor"
	startproject "GloryEntityScenes"
	startproject "GloryGLSLShaderLoader"
	startproject "GloryMain"
	startproject "GloryOpenGLGraphics"
	startproject "GlorySDLImage"
	startproject "GlorySDLWindow"
	startproject "GloryVulkanGraphics"
	
	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

vulkan_sdk = "C:/VulkanSDK/1.2.182.0"
leak_detector = "C:/Program Files (x86)/Visual Leak Detector/include"
outputdir = "%{cfg.buildcfg}/%{cfg.platform}"
engineoutdir = "../bin/Engine/%{cfg.buildcfg}/%{cfg.platform}"

GloryIncludeDir = {}
GloryIncludeDir["assimp"]			= "../GloryASSIMPModelLoader"
GloryIncludeDir["basicrenderer"]	= "../GloryBasicRenderer"
GloryIncludeDir["core"]				= "../GloryCore"
GloryIncludeDir["editor"]			= "../GloryEditor"
GloryIncludeDir["entityscenes"]		= "../GloryEntityScenes"
GloryIncludeDir["glslloader"]		= "../GloryGLSLShaderLoader"
GloryIncludeDir["main"]				= "../GloryMain"
GloryIncludeDir["opengl"]			= "../GloryOpenGLGraphics"
GloryIncludeDir["sdlimage"]			= "../GlorySDLImage"
GloryIncludeDir["sdlwindow"]		= "../GlorySDLWindow"
GloryIncludeDir["vulkan"]			= "../GloryVulkanGraphics"
GloryIncludeDir["ImGui"]			= "../ImGui"

SubmodoleDirs = {}
SubmodoleDirs["assimp"]				= "../submodules/assimp"
SubmodoleDirs["ImGui"]				= "../submodules/ImGui"
SubmodoleDirs["GLEW"]				= "../third-party/GLEW"
SubmodoleDirs["SDL_image"]			= "../third-party/SDL_Image"
SubmodoleDirs["shaderc"]			= "../third-party/shaderc"
SubmodoleDirs["spirv_cross"]		= "../third-party/spirv-cross"
SubmodoleDirs["yaml_cpp"]			= "../third-party/yaml-cpp"
SubmodoleDirs["glory"]				= "../bin/Engine"

IncludeDir = {}
IncludeDir["assimp"]				= "%{SubmodoleDirs.assimp}/include"
IncludeDir["glory"]					= "%{SubmodoleDirs.glory}/include"
IncludeDir["GLEW"]					= "%{SubmodoleDirs.GLEW}/include"
IncludeDir["ImGui"]					= "%{SubmodoleDirs.ImGui}"
IncludeDir["SDL_image"]				= "%{SubmodoleDirs.SDL_image}/include"
IncludeDir["shaderc"]				= "%{SubmodoleDirs.shaderc}/include"
IncludeDir["spirv_cross"]			= "%{SubmodoleDirs.spirv_cross}/include"
IncludeDir["yaml_cpp"]				= "%{SubmodoleDirs.yaml_cpp}/include"

LibDirs = {}
LibDirs["assimp"]					= "%{SubmodoleDirs.assimp}/lib/%{cfg.buildcfg}/%{cfg.platform}"
LibDirs["glory"]					= "%{SubmodoleDirs.glory}/lib/%{cfg.buildcfg}/%{cfg.platform}"
LibDirs["GLEW"]						= "%{SubmodoleDirs.GLEW}/lib/%{cfg.buildcfg}/%{cfg.platform}"
LibDirs["ImGui"]					= "%{SubmodoleDirs.ImGui}/lib/%{cfg.buildcfg}/%{cfg.platform}"
LibDirs["SDL_image"]				= "%{SubmodoleDirs.SDL_image}/lib/%{cfg.buildcfg}/%{cfg.platform}"
LibDirs["shaderc"]					= "%{SubmodoleDirs.shaderc}/lib/%{cfg.buildcfg}/%{cfg.platform}"
LibDirs["spirv_cross"]				= "%{SubmodoleDirs.spirv_cross}/lib/%{cfg.buildcfg}/%{cfg.platform}"
LibDirs["yaml_cpp"]					= "%{SubmodoleDirs.yaml_cpp}/lib/%{cfg.buildcfg}/%{cfg.platform}"

group "Dependencies"
	include "third-party/ImGui"
	include "third-party/assimp"
group ""

include "GloryASSIMPModelLoader"
include "GloryBasicRenderer"
include "GloryCore"
include "GloryEditor"
include "GloryEntityScenes"
include "GloryGLSLShaderLoader"
include "GloryMain"
include "GloryOpenGLGraphics"
include "GlorySDLImage"
include "GlorySDLWindow"
include "GloryVulkanGraphics"