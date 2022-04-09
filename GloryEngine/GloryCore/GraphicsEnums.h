#pragma once

namespace Glory
{
	enum class PixelFormat
	{
        PF_Undefined,

        // Basic format
        PF_R,
        PF_RG,
        PF_RGB,
        PF_BGR,
        PF_RGBA,
        PF_BGRA,
        PF_RI,
        PF_RGI,
        PF_RGBI,
        PF_BGRI,
        PF_RGBAI,
        PF_BGRAI,
        PF_Stencil,
        PF_Depth,
        PF_DepthStencil,

        // Internal format
        PF_R4G4UnormPack8,
        PF_R4G4B4A4UnormPack16,
        PF_B4G4R4A4UnormPack16,
        PF_R5G6B5UnormPack16,
        PF_B5G6R5UnormPack16,
        PF_R5G5B5A1UnormPack16,
        PF_B5G5R5A1UnormPack16,
        PF_A1R5G5B5UnormPack16,
        PF_R8Unorm,
        PF_R8Snorm,
        PF_R8Uscaled,
        PF_R8Sscaled,
        PF_R8Uint,
        PF_R8Sint,
        PF_R8Srgb,
        PF_R8G8Unorm,
        PF_R8G8Snorm,
        PF_R8G8Uscaled,
        PF_R8G8Sscaled,
        PF_R8G8Uint,
        PF_R8G8Sint,
        PF_R8G8Srgb,
        PF_R8G8B8Unorm,
        PF_R8G8B8Snorm,
        PF_R8G8B8Uscaled,
        PF_R8G8B8Sscaled,
        PF_R8G8B8Uint,
        PF_R8G8B8Sint,
        PF_R8G8B8Srgb,
        PF_B8G8R8Unorm,
        PF_B8G8R8Snorm,
        PF_B8G8R8Uscaled,
        PF_B8G8R8Sscaled,
        PF_B8G8R8Uint,
        PF_B8G8R8Sint,
        PF_B8G8R8Srgb,
        PF_R8G8B8A8Unorm,
        PF_R8G8B8A8Snorm,
        PF_R8G8B8A8Uscaled,
        PF_R8G8B8A8Sscaled,
        PF_R8G8B8A8Uint,
        PF_R8G8B8A8Sint,
        PF_R8G8B8A8Srgb,
        PF_B8G8R8A8Unorm,
        PF_B8G8R8A8Snorm,
        PF_B8G8R8A8Uscaled,
        PF_B8G8R8A8Sscaled,
        PF_B8G8R8A8Uint,
        PF_B8G8R8A8Sint,
        PF_B8G8R8A8Srgb,
        PF_A8B8G8R8UnormPack32,
        PF_A8B8G8R8SnormPack32,
        PF_A8B8G8R8UscaledPack32,
        PF_A8B8G8R8SscaledPack32,
        PF_A8B8G8R8UintPack32,
        PF_A8B8G8R8SintPack32,
        PF_A8B8G8R8SrgbPack32,
        PF_A2R10G10B10UnormPack32,
        PF_A2R10G10B10SnormPack32,
        PF_A2R10G10B10UscaledPack32,
        PF_A2R10G10B10SscaledPack32,
        PF_A2R10G10B10UintPack32,
        PF_A2R10G10B10SintPack32,
        PF_A2B10G10R10UnormPack32,
        PF_A2B10G10R10SnormPack32,
        PF_A2B10G10R10UscaledPack32,
        PF_A2B10G10R10SscaledPack32,
        PF_A2B10G10R10UintPack32,
        PF_A2B10G10R10SintPack32,
        PF_R16Unorm,
        PF_R16Snorm,
        PF_R16Uscaled,
        PF_R16Sscaled,
        PF_R16Uint,
        PF_R16Sint,
        PF_R16Sfloat,
        PF_R16G16Unorm,
        PF_R16G16Snorm,
        PF_R16G16Uscaled,
        PF_R16G16Sscaled,
        PF_R16G16Uint,
        PF_R16G16Sint,
        PF_R16G16Sfloat,
        PF_R16G16B16Unorm,
        PF_R16G16B16Snorm,
        PF_R16G16B16Uscaled,
        PF_R16G16B16Sscaled,
        PF_R16G16B16Uint,
        PF_R16G16B16Sint,
        PF_R16G16B16Sfloat,
        PF_R16G16B16A16Unorm,
        PF_R16G16B16A16Snorm ,
        PF_R16G16B16A16Uscaled,
        PF_R16G16B16A16Sscaled,
        PF_R16G16B16A16Uint,
        PF_R16G16B16A16Sint,
        PF_R16G16B16A16Sfloat,
        PF_R32Uint,
        PF_R32Sint,
        PF_R32Sfloat,
        PF_R32G32Uint,
        PF_R32G32Sint,
        PF_R32G32Sfloat,
        PF_R32G32B32Uint,
        PF_R32G32B32Sint,
        PF_R32G32B32Sfloat,
        PF_R32G32B32A32Uint,
        PF_R32G32B32A32Sint,
        PF_R32G32B32A32Sfloat,
        PF_R64Uint,
        PF_R64Sint,
        PF_R64Sfloat,
        PF_R64G64Uint,
        PF_R64G64Sint,
        PF_R64G64Sfloat,
        PF_R64G64B64Uint,
        PF_R64G64B64Sint,
        PF_R64G64B64Sfloat,
        PF_R64G64B64A64Uint,
        PF_R64G64B64A64Sint,
        PF_R64G64B64A64Sfloat,
        PF_B10G11R11UfloatPack32,
        PF_E5B9G9R9UfloatPack32,
        PF_D16Unorm,
        PF_X8D24UnormPack32,
        PF_D32Sfloat,
        PF_S8Uint,
        PF_D16UnormS8Uint,
        PF_D24UnormS8Uint,
        PF_D32SfloatS8Uint,
        PF_Bc1RgbUnormBlock,
        PF_Bc1RgbSrgbBlock,
        PF_Bc1RgbaUnormBlock,
        PF_Bc1RgbaSrgbBlock,
        PF_Bc2UnormBlock,
        PF_Bc2SrgbBlock,
        PF_Bc3UnormBlock,
        PF_Bc3SrgbBlock,
        PF_Bc4UnormBlock,
        PF_Bc4SnormBlock,
        PF_Bc5UnormBlock,
        PF_Bc5SnormBlock,
        PF_Bc6HUfloatBlock,
        PF_Bc6HSfloatBlock,
        PF_Bc7UnormBlock,
        PF_Bc7SrgbBlock,
        PF_Etc2R8G8B8UnormBlock,
        PF_Etc2R8G8B8SrgbBlock,
        PF_Etc2R8G8B8A1UnormBlock,
        PF_Etc2R8G8B8A1SrgbBlock,
        PF_Etc2R8G8B8A8UnormBlock,
        PF_Etc2R8G8B8A8SrgbBlock,
        PF_EacR11UnormBlock,
        PF_EacR11SnormBlock,
        PF_EacR11G11UnormBlock,
        PF_EacR11G11SnormBlock,
        PF_Astc4x4UnormBlock,
        PF_Astc4x4SrgbBlock,
        PF_Astc5x4UnormBlock,
        PF_Astc5x4SrgbBlock,
        PF_Astc5x5UnormBlock,
        PF_Astc5x5SrgbBlock,
        PF_Astc6x5UnormBlock,
        PF_Astc6x5SrgbBlock,
        PF_Astc6x6UnormBlock,
        PF_Astc6x6SrgbBlock,
        PF_Astc8x5UnormBlock,
        PF_Astc8x5SrgbBlock,
        PF_Astc8x6UnormBlock,
        PF_Astc8x6SrgbBlock,
        PF_Astc8x8UnormBlock,
        PF_Astc8x8SrgbBlock,
        PF_Astc10x5UnormBlock,
        PF_Astc10x5SrgbBlock,
        PF_Astc10x6UnormBlock,
        PF_Astc10x6SrgbBlock,
        PF_Astc10x8UnormBlock,
        PF_Astc10x8SrgbBlock,
        PF_Astc10x10UnormBlock,
        PF_Astc10x10SrgbBlock,
        PF_Astc12x10UnormBlock,
        PF_Astc12x10SrgbBlock,
        PF_Astc12x12UnormBlock,
        PF_Astc12x12SrgbBlock,

        PF_Depth16,
        PF_Depth24,
        PF_Depth32,


        // NOT SUPPORTED FOR NOW
        PF_G8B8G8R8422Unorm = 1000156000,
        PF_B8G8R8G8422Unorm,
        PF_G8B8R83Plane420Unorm,
        PF_G8B8R82Plane420Unorm,
        PF_G8B8R83Plane422Unorm,
        PF_G8B8R82Plane422Unorm,
        PF_G8B8R83Plane444Unorm,
        PF_R10X6UnormPack16,
        PF_R10X6G10X6Unorm2Pack16,
        PF_R10X6G10X6B10X6A10X6Unorm4Pack16,
        PF_G10X6B10X6G10X6R10X6422Unorm4Pack16,
        PF_B10X6G10X6R10X6G10X6422Unorm4Pack16,
        PF_G10X6B10X6R10X63Plane420Unorm3Pack16,
        PF_G10X6B10X6R10X62Plane420Unorm3Pack16,
        PF_G10X6B10X6R10X63Plane422Unorm3Pack16,
        PF_G10X6B10X6R10X62Plane422Unorm3Pack16,
        PF_G10X6B10X6R10X63Plane444Unorm3Pack16,
        PF_R12X4UnormPack16,
        PF_R12X4G12X4Unorm2Pack16,
        PF_R12X4G12X4B12X4A12X4Unorm4Pack16,
        PF_G12X4B12X4G12X4R12X4422Unorm4Pack16,
        PF_B12X4G12X4R12X4G12X4422Unorm4Pack16,
        PF_G12X4B12X4R12X43Plane420Unorm3Pack16,
        PF_G12X4B12X4R12X42Plane420Unorm3Pack16,
        PF_G12X4B12X4R12X43Plane422Unorm3Pack16,
        PF_G12X4B12X4R12X42Plane422Unorm3Pack16,
        PF_G12X4B12X4R12X43Plane444Unorm3Pack16,
        PF_G16B16G16R16422Unorm,
        PF_B16G16R16G16422Unorm,
        PF_G16B16R163Plane420Unorm,
        PF_G16B16R162Plane420Unorm,
        PF_G16B16R163Plane422Unorm,
        PF_G16B16R162Plane422Unorm,
        PF_G16B16R163Plane444Unorm,
        PF_Pvrtc12BppUnormBlockIMG,
        PF_Pvrtc14BppUnormBlockIMG,
        PF_Pvrtc22BppUnormBlockIMG,
        PF_Pvrtc24BppUnormBlockIMG,
        PF_Pvrtc12BppSrgbBlockIMG,
        PF_Pvrtc14BppSrgbBlockIMG,
        PF_Pvrtc22BppSrgbBlockIMG,
        PF_Pvrtc24BppSrgbBlockIMG,
        PF_Astc4x4SfloatBlockEXT,
        PF_Astc5x4SfloatBlockEXT,
        PF_Astc5x5SfloatBlockEXT,
        PF_Astc6x5SfloatBlockEXT,
        PF_Astc6x6SfloatBlockEXT,
        PF_Astc8x5SfloatBlockEXT,
        PF_Astc8x6SfloatBlockEXT,
        PF_Astc8x8SfloatBlockEXT,
        PF_Astc10x5SfloatBlockEXT,
        PF_Astc10x6SfloatBlockEXT,
        PF_Astc10x8SfloatBlockEXT,
        PF_Astc10x10SfloatBlockEXT,
        PF_Astc12x10SfloatBlockEXT,
        PF_Astc12x12SfloatBlockEXT,
        PF_B10X6G10X6R10X6G10X6422Unorm4Pack16KHR,
        PF_B12X4G12X4R12X4G12X4422Unorm4Pack16KHR,
        PF_B16G16R16G16422UnormKHR,
        PF_B8G8R8G8422UnormKHR,
        PF_G10X6B10X6G10X6R10X6422Unorm4Pack16KHR,
        PF_G10X6B10X6R10X62Plane420Unorm3Pack16KHR,
        PF_G10X6B10X6R10X62Plane422Unorm3Pack16KHR,
        PF_G10X6B10X6R10X63Plane420Unorm3Pack16KHR,
        PF_G10X6B10X6R10X63Plane422Unorm3Pack16KHR,
        PF_G10X6B10X6R10X63Plane444Unorm3Pack16KHR,
        PF_G12X4B12X4G12X4R12X4422Unorm4Pack16KHR,
        PF_G12X4B12X4R12X42Plane420Unorm3Pack16KHR,
        PF_G12X4B12X4R12X42Plane422Unorm3Pack16KHR,
        PF_G12X4B12X4R12X43Plane420Unorm3Pack16KHR,
        PF_G12X4B12X4R12X43Plane422Unorm3Pack16KHR,
        PF_G12X4B12X4R12X43Plane444Unorm3Pack16KHR,
        PF_G16B16G16R16422UnormKHR,
        PF_G16B16R162Plane420UnormKHR,
        PF_G16B16R162Plane422UnormKHR,
        PF_G16B16R163Plane420UnormKHR,
        PF_G16B16R163Plane422UnormKHR,
        PF_G16B16R163Plane444UnormKHR,
        PF_G8B8G8R8422UnormKHR,
        PF_G8B8R82Plane420UnormKHR,
        PF_G8B8R82Plane422UnormKHR,
        PF_G8B8R83Plane420UnormKHR,
        PF_G8B8R83Plane422UnormKHR,
        PF_G8B8R83Plane444UnormKHR,
        PF_R10X6G10X6B10X6A10X6Unorm4Pack16KHR,
        PF_R10X6G10X6Unorm2Pack16KHR,
        PF_R10X6UnormPack16KHR,
        PF_R12X4G12X4B12X4A12X4Unorm4Pack16KHR,
        PF_R12X4G12X4Unorm2Pack16KHR,
        PF_R12X4UnormPack16KHR,
	};

	enum class ImageType
	{
		IT_UNDEFINED,
		IT_1D,
		IT_2D,
		IT_3D,
		IT_Cube,
		IT_1DArray,
		IT_2DArray,
		IT_CubeArray,
	};

	enum ImageAspect : int
	{
		IA_Color			= 0x00000001,
		IA_Depth			= 0x00000002,
		IA_Stencil			= 0x00000004,
		IA_Metadata			= 0x00000008,
		IA_Plane0			= 0x00000010,
		IA_Plane1			= 0x00000020,
		IA_Plane2			= 0x00000040,
		IA_MemoryPlane0EXT	= 0x00000080,
		IA_MemoryPlane1EXT	= 0x00000100,
		IA_MemoryPlane2EXT	= 0x00000200,
		IA_MemoryPlane3EXT	= 0x00000400,
		IA_Plane0KHR		= 0x00000800,
		IA_Plane1KHR		= 0x00001000,
		IA_Plane2KHR		= 0x00002000,
	};

	enum class Filter
	{
		F_Nearest,
		F_Linear,
		F_CubicIMG,
		F_CubicEXT,
	};

	enum class SamplerAddressMode
	{
		SAM_Repeat,
		SAM_MirroredRepeat,
		SAM_ClampToEdge,
		SAM_ClampToBorder,
		SAM_MirrorClampToEdge,
		SAM_MirrorClampToEdgeKHR,
	};

	enum class CompareOp
	{
		OP_Never,
		OP_Less,
		OP_Equal,
		OP_LessOrEqual,
		OP_Greater,
		OP_NotEqual,
		OP_GreaterOrEqual,
		OP_Always,
	};

	struct SamplerSettings
	{
		Filter MagFilter;
		Filter MinFilter;
		SamplerAddressMode AddressModeU;
		SamplerAddressMode AddressModeV;
		SamplerAddressMode AddressModeW;
		bool AnisotropyEnable;
		float MaxAnisotropy;
		bool UnnormalizedCoordinates;
		bool CompareEnable;
		CompareOp CompareOp;
		Filter MipmapMode;
		float MipLODBias;
		float MinLOD;
		float MaxLOD;
	};

    enum class ShaderType
    {
        ST_Unknown,
        ST_Vertex,
        ST_Fragment,
        ST_Geomtery,
        ST_TessControl,
        ST_TessEval,
        ST_Compute,
    };
}
