#ifndef __GRAPHICS_TYPES_H__
#define __GRAPHICS_TYPES_H__

#include <memory>
#include <map>
#include <vector>
#include <cstdint>
#include <string>

namespace el {

    class Viewport
    {
    public:

        Viewport() :
            x(0),
            y(0),
            width(0u),
            height(0u)
        {
        }

        Viewport(int32_t _x, int32_t _y, uint32_t _width, uint32_t _height) :
            x(_x),
            y(_y),
            width(_width),
            height(_height)
        {
        }

        int32_t x;
        int32_t y;
        uint32_t width;
        uint32_t height;
    };

    inline bool operator==(const Viewport& v1, const Viewport& v2)
    {
        return v1.x == v2.x && v1.y == v2.y && v1.width == v2.width && v1.height == v2.height;
    }

    inline bool operator!=(const Viewport& v1, const Viewport& v2)
    {
        return !(v1 == v2);
    }

    class GraphicsDeviceDesc;
    class GraphicsContextDesc;
    class GraphicsProgramDesc;
    class GraphicsShaderDesc;
    class GraphicsTextureDesc;
    class GraphicsDataDesc;
    class GraphicsSamplerDesc;
    class GraphicsInputLayoutDesc;
    class GraphicsInputBinding;
    class GraphicsInputAttribute;
    class GraphicsDepthStencilDesc;
    class GraphicsStencilOpState;

    typedef std::shared_ptr<class GraphicsDevice> GraphicsDevicePtr;
    typedef std::shared_ptr<class GraphicsContext> GraphicsContextPtr;
    typedef std::shared_ptr<class GraphicsShader> GraphicsShaderPtr;
    typedef std::shared_ptr<class GraphicsProgram> GraphicsProgramPtr;
    typedef std::shared_ptr<class GraphicsTexture> GraphicsTexturePtr;
    typedef std::shared_ptr<class GraphicsData> GraphicsDataPtr;
    typedef std::shared_ptr<class GraphicsInputLayout> GraphicsInputLayoutPtr;
    typedef std::shared_ptr<class GraphicsVertexAttribute> GraphicsVertexAttributePtr;
    typedef std::shared_ptr<class GraphicsSampler> GraphicsSamplerPtr;
    typedef std::shared_ptr<class GraphicsDepthStencil> GraphicsDepthStencilPtr;

    typedef std::weak_ptr<GraphicsDevice> GraphicsDeviceWeakPtr;

    typedef std::vector<GraphicsVertexAttributePtr> GraphicsVertexAttributes;
    typedef std::vector<GraphicsShaderPtr> GraphicsShaders;
    typedef std::vector<GraphicsInputBinding> GraphicsInputBindings;
    typedef std::vector<GraphicsInputAttribute> GraphicsInputAttributes;

    enum GraphicsDeviceType
    {
        GraphicsDeviceTypeD3D9 = 0,
        GraphicsDeviceTypeD3D11 = 1,
        GraphicsDeviceTypeD3D12 = 2,
        GraphicsDeviceTypeOpenGL = 3,
        GraphicsDeviceTypeOpenGLCore = 4,
        GraphicsDeviceTypeOpenGLES2 = 5,
        GraphicsDeviceTypeOpenGLES3 = 6,
        GraphicsDeviceTypeOpenGLES31 = 7,
        GraphicsDeviceTypeOpenGLES32 = 8,
        GraphicsDeviceTypeVulkan = 9,
        GraphicsDeviceTypeMetal = 10,
        GraphicsDeviceTypeFirst = GraphicsDeviceTypeD3D9,
        GraphicsDeviceTypeLast = GraphicsDeviceTypeMetal,
    };

    enum GraphicsTextureDim {
        GraphicsTextureDim1D = 0,
        GraphicsTextureDim1DArray,
        GraphicsTextureDim2D,
        GraphicsTextureDim2DArray,
        GraphicsTextureDim3D,
        GraphicsTextureDimRect,
        GraphicsTextureDimRectArray,
        GraphicsTextureDimCube,
        GraphicsTextureDimCubeArray,
        GraphicsTextureDimFirst = GraphicsTextureDim1D,
        GraphicsTextureDimLast = GraphicsTextureDimCubeArray
    };

    enum GraphicsDataType
    {
        GraphicsDataTypeNone = 0,
        GraphicsDataTypeTransferSrc = 1,
        GraphicsDataTypeTransferDst = 2,
        GraphicsDataTypeUniformTexelBuffer = 3,
        GraphicsDataTypeUniformBuffer = 4,
        GraphicsDataTypeStorageTexelBuffer = 5,
        GraphicsDataTypeStorageBuffer = 6,
        GraphicsDataTypeStorageVertexBuffer = 7,
        GraphicsDataTypeStorageIndexBuffer = 8,
    };

    enum class GraphicsIndexType: std::uint8_t
    {
        GraphicsIndexTypeUInt8 = 0,
        GraphicsIndexTypeUInt16 = 1,
        GraphicsIndexTypeUInt32 = 2,
    };

    // https://www.khronos.org/opengl/wiki/Buffer_Object
    enum GraphicsUsageFlagBits
    {
        GraphicsUsageFlagReadBit = 0x00000001,
        GraphicsUsageFlagWriteBit = 0x00000002,
        GraphicsUsageFlagPersistentBit = 0x00000004,
        GraphicsUsageFlagCoherentBit = 0x00000008,
        GraphicsUsageFlagFlushExplicitBit = 0x00000010,
        GraphicsUsageFlagDynamicStorageBit = 0x00000020,
        GraphicsUsageFlagClientStorageBit = 0x00000040
    };

    typedef std::uint32_t GraphicsUsageFlags;

    // From vulkan spec.
    enum GraphicsShaderStageFlagBits
    {
        GraphicsShaderStageNoneBit = 0x00000000,
        GraphicsShaderStageVertexBit = 0x00000001,
        GraphicsShaderStageTessellationControlBit = 0x00000002,
        GraphicsShaderStageTessellationEvaluationBit = 0x00000004,
        GraphicsShaderStageGeometryBit = 0x00000008,
        GraphicsShaderStageFragmentBit = 0x00000010,
        GraphicsShaderStageComputeBit = 0x00000020,
        GraphicsShaderStageAllGraphics = 0x0000001F,
        GraphicsShaderStageAll = 0x7FFFFFFF,
        GraphicsShaderStageRaygenBit = 0x00000100,
        GraphicsShaderStageAnyHitBit = 0x00000200,
        GraphicsShaderStageClosestHitBit = 0x00000400,
        GraphicsShaderStageMissBit = 0x00000800,
        GraphicsShaderStageIntersectionBit = 0x00001000,
        GraphicsShaderStageCallableBit = 0x00002000,
        GraphicsShaderStageTaskBit = 0x00000040,
        GraphicsShaderStageMeshBit = 0x00000080,
        GraphicsShaderStageFlagBitsMaxEnum = 0x7FFFFFFF
    };

    // From vulkan sepc.
    enum GraphicsSamplerAddressMode
    {
        GraphicsSamplerAddressModeRepeat = 0,
        GraphicsSamplerAddressModeMirroredReapt = 1,
        GraphicsSamplerAddressModeClampToEdge = 2,
        GraphicsSamplerAddressModeClampToBorder = 3,
        GraphicsSamplerAddressModeMirrorClampToEdge = 4
    };

    enum GraphicsFilter
    {
        GraphicsFilterNearest = 0,
        GraphicsFilterLinear = 1,
    };

    enum GraphicsSamplerMipmapMode {
        GraphicsSamplerMipmapModeNone = 0,
        GraphicsSamplerMipmapModeNearest = 1,
        GraphicsSamplerMipmapModeLinear = 2,
    };

    // From vulkan spec.
    enum GraphicsBorderColor {
        GraphicsBorderColorFloatTransparentBlack = 0,
        GraphicsBorderColorIntTransparentBlack = 1,
        GraphicsBorderColorFloatOpaqueBlack = 2,
        GraphicsBorderColorIntOpaqueBlack = 3,
        GraphicsBorderColorFloatOpaqueWhite = 4,
        GraphicsBorderColorIntOpaqueWhite = 5,
    };

    // From vulkan spec.
    enum GraphicsTextureUsageFlagBits
    {
        GraphicsTextureUsageTransferSrcBit = 0x00000001,
        GraphicsTextureUsageTransferDstBit = 0x00000002,
        GraphicsTextureUsageSampledBit = 0x00000004,
        GraphicsTextureUsageStorageBit = 0x00000008,
        GraphicsTextureUsageColorAttachmentBit = 0x00000010,
        GraphicsTextureUsageDepthStencilAttachmentBit = 0x00000020,
        GraphicsTextureUsageTransientAttachmentBit = 0x00000040,
        GraphicsTextureUsageInputAttachmentBit = 0x00000080,
        GraphicsTextureUsageUploadableBit = 0x00000100,
    };

    typedef uint32_t GraphicsTextureUsageFlags;
    
    // TODO: Replace with vulkan spec.
    // From MTLPixelFormat
    enum GraphicsPixelFormat
    {
        GraphicsPixelFormatInvalid = 0,
        GraphicsPixelFormatA8Unorm = 1,
        GraphicsPixelFormatR8Unorm = 10,
        GraphicsPixelFormatR8Unorm_sRGB = 11,
        GraphicsPixelFormatR8Snorm = 12,
        GraphicsPixelFormatR8Uint = 13,
        GraphicsPixelFormatR8Sint = 14,
        GraphicsPixelFormatR16Unorm = 20,
        GraphicsPixelFormatR16Snorm = 22,
        GraphicsPixelFormatR16Uint = 23,
        GraphicsPixelFormatR16Sint = 24,
        GraphicsPixelFormatR16Float = 25,
        GraphicsPixelFormatRG8Unorm = 30,
        GraphicsPixelFormatRG8Unorm_sRGB = 31,
        GraphicsPixelFormatRG8Snorm = 32,
        GraphicsPixelFormatRG8Uint = 33,
        GraphicsPixelFormatRG8Sint = 34,
        GraphicsPixelFormatB5G6R5Unorm = 40,
        GraphicsPixelFormatA1BGR5Unorm = 41,
        GraphicsPixelFormatABGR4Unorm = 42,
        GraphicsPixelFormatBGR5A1Unorm = 43,
        GraphicsPixelFormatR32Uint = 53,
        GraphicsPixelFormatR32Sint = 54,
        GraphicsPixelFormatR32Float = 55,
        GraphicsPixelFormatRG16Unorm = 60,
        GraphicsPixelFormatRG16Snorm = 62,
        GraphicsPixelFormatRG16Uint = 63,
        GraphicsPixelFormatRG16Sint = 64,
        GraphicsPixelFormatRG16Float = 65,
        GraphicsPixelFormatRGBA8Unorm = 70,
        GraphicsPixelFormatRGBA8Unorm_sRGB = 71,
        GraphicsPixelFormatRGBA8Snorm = 72,
        GraphicsPixelFormatRGBA8Uint = 73,
        GraphicsPixelFormatRGBA8Sint = 74,
        GraphicsPixelFormatBGRA8Unorm = 80,
        GraphicsPixelFormatBGRA8Unorm_sRGB = 81,
        GraphicsPixelFormatRGB10A2Unorm = 90,
        GraphicsPixelFormatRGB10A2Uint = 91,
        GraphicsPixelFormatRG11B10Float = 92,
        GraphicsPixelFormatRGB9E5Float = 93,
        GraphicsPixelFormatBGR10_XR = 554,
        GraphicsPixelFormatBGR10_XR_sRGB = 555,
        GraphicsPixelFormatRG32Uint = 103,
        GraphicsPixelFormatRG32Sint = 104,
        GraphicsPixelFormatRG32Float = 105,
        GraphicsPixelFormatRGBA16Unorm = 110,
        GraphicsPixelFormatRGBA16Snorm = 112,
        GraphicsPixelFormatRGBA16Uint = 113,
        GraphicsPixelFormatRGBA16Sint = 114,
        GraphicsPixelFormatRGBA16Float = 115,
        GraphicsPixelFormatBGRA10_XR = 552,
        GraphicsPixelFormatBGRA10_XR_sRGB = 553,
        GraphicsPixelFormatRGBA32Uint = 123,
        GraphicsPixelFormatRGBA32Sint = 124,
        GraphicsPixelFormatRGBA32Float = 125,
        GraphicsPixelFormatBC1_RGBA = 130,
        GraphicsPixelFormatBC1_RGBA_sRGB = 131,
        GraphicsPixelFormatBC2_RGBA = 132,
        GraphicsPixelFormatBC2_RGBA_sRGB = 133,
        GraphicsPixelFormatBC3_RGBA = 134,
        GraphicsPixelFormatBC3_RGBA_sRGB = 135,
        GraphicsPixelFormatBC4_RUnorm = 140,
        GraphicsPixelFormatBC4_RSnorm = 141,
        GraphicsPixelFormatBC5_RGUnorm = 142,
        GraphicsPixelFormatBC5_RGSnorm = 143,
        GraphicsPixelFormatBC6H_RGBFloat = 150,
        GraphicsPixelFormatBC6H_RGBUfloat = 151,
        GraphicsPixelFormatBC7_RGBAUnorm = 152,
        GraphicsPixelFormatBC7_RGBAUnorm_sRGB = 153,
        GraphicsPixelFormatPVRTC_RGB_2BPP = 160,
        GraphicsPixelFormatPVRTC_RGB_2BPP_sRGB = 161,
        GraphicsPixelFormatPVRTC_RGB_4BPP = 162,
        GraphicsPixelFormatPVRTC_RGB_4BPP_sRGB = 163,
        GraphicsPixelFormatPVRTC_RGBA_2BPP = 164,
        GraphicsPixelFormatPVRTC_RGBA_2BPP_sRGB = 165,
        GraphicsPixelFormatPVRTC_RGBA_4BPP = 166,
        GraphicsPixelFormatPVRTC_RGBA_4BPP_sRGB = 167,
        GraphicsPixelFormatEAC_R11Unorm = 170,
        GraphicsPixelFormatEAC_R11Snorm = 172,
        GraphicsPixelFormatEAC_RG11Unorm = 174,
        GraphicsPixelFormatEAC_RG11Snorm = 176,
        GraphicsPixelFormatEAC_RGBA8 = 178,
        GraphicsPixelFormatEAC_RGBA8_sRGB = 179,
        GraphicsPixelFormatETC2_RGB8 = 180,
        GraphicsPixelFormatETC2_RGB8_sRGB = 181,
        GraphicsPixelFormatETC2_RGB8A1 = 182,
        GraphicsPixelFormatETC2_RGB8A1_sRGB = 183,
        GraphicsPixelFormatASTC_4x4_sRGB = 186,
        GraphicsPixelFormatASTC_5x4_sRGB = 187,
        GraphicsPixelFormatASTC_5x5_sRGB = 188,
        GraphicsPixelFormatASTC_6x5_sRGB = 189,
        GraphicsPixelFormatASTC_6x6_sRGB = 190,
        GraphicsPixelFormatASTC_8x5_sRGB = 192,
        GraphicsPixelFormatASTC_8x6_sRGB = 193,
        GraphicsPixelFormatASTC_8x8_sRGB = 194,
        GraphicsPixelFormatASTC_10x5_sRGB = 195,
        GraphicsPixelFormatASTC_10x6_sRGB = 196,
        GraphicsPixelFormatASTC_10x8_sRGB = 197,
        GraphicsPixelFormatASTC_10x10_sRGB = 198,
        GraphicsPixelFormatASTC_12x10_sRGB = 199,
        GraphicsPixelFormatASTC_12x12_sRGB = 200,
        GraphicsPixelFormatASTC_4x4_LDR = 204,
        GraphicsPixelFormatASTC_5x4_LDR = 205,
        GraphicsPixelFormatASTC_5x5_LDR = 206,
        GraphicsPixelFormatASTC_6x5_LDR = 207,
        GraphicsPixelFormatASTC_6x6_LDR = 208,
        GraphicsPixelFormatASTC_8x5_LDR = 210,
        GraphicsPixelFormatASTC_8x6_LDR = 211,
        GraphicsPixelFormatASTC_8x8_LDR = 212,
        GraphicsPixelFormatASTC_10x5_LDR = 213,
        GraphicsPixelFormatASTC_10x6_LDR = 214,
        GraphicsPixelFormatASTC_10x8_LDR = 215,
        GraphicsPixelFormatASTC_10x10_LDR = 216,
        GraphicsPixelFormatASTC_12x10_LDR = 217,
        GraphicsPixelFormatASTC_12x12_LDR = 218,
        GraphicsPixelFormatGBGR422 = 240,
        GraphicsPixelFormatBGRG422 = 241,
        GraphicsPixelFormatDepth16Unorm = 250,
        GraphicsPixelFormatDepth32Float = 252,
        GraphicsPixelFormatStencil8 = 253,
        GraphicsPixelFormatDepth24Unorm_Stencil8 = 255,
        GraphicsPixelFormatDepth32Float_Stencil8 = 260,
        GraphicsPixelFormatX32_Stencil8 = 261,
        GraphicsPixelFormatX24_Stencil8 = 262,

        // TODO: replace with vulan pixel format?
        // Not supported in Metal but in OpenGL
        GraphicsPixelFormatRGB8Unorm = 265,
    };

    enum class GraphicsPixelAlignment : uint8_t
    {
        GraphicsPixelAlignment1 = 1,
        GraphicsPixelAlignment2 = 2,
        GraphicsPixelAlignment4 = 4,
        GraphicsPixelAlignment8 = 8,
    };

    enum GraphicsPrimitiveType : uint8_t
    {
        GraphicsPrimitiveTypeTriangle = 4,
        GraphicsPrimitiveTypeFan = 5,
    };

    // TODO:
    // from apple spec.
    enum class GraphicsVertexFormat
    {
        Invalid = 0,

        UChar2 = 1,
        UChar3 = 2,
        UChar4 = 3,

        Char2 = 4,
        Char3 = 5,
        Char4 = 6,

        UChar2Normalized = 7,
        UChar3Normalized = 8,
        UChar4Normalized = 9,

        Char2Normalized = 10,
        Char3Normalized = 11,
        Char4Normalized = 12,

        UShort2 = 13,
        UShort3 = 14,
        UShort4 = 15,

        Short2 = 16,
        Short3 = 17,
        Short4 = 18,

        UShort2Normalized = 19,
        UShort3Normalized = 20,
        UShort4Normalized = 21,

        Short2Normalized = 22,
        Short3Normalized = 23,
        Short4Normalized = 24,

        Half2 = 25,
        Half3 = 26,
        Half4 = 27,

        Float = 28,
        Float2 = 29,
        Float3 = 30,
        Float4 = 31,

        Int = 32,
        Int2 = 33,
        Int3 = 34,
        Int4 = 35,

        UInt = 36,
        UInt2 = 37,
        UInt3 = 38,
        UInt4 = 39,

        Int1010102Normalized = 40,
        UInt1010102Normalized = 41,
    };

    // from vulkan spec.
    enum GraphicsInputRate
    {
        GraphicsInputRateVertex = 0,
        GraphicsInputRateInstance = 1
    };

    enum class GraphicsCompareOp : uint32_t
    {
        GraphicsCompareOpNever = 0,
        GraphicsCompareOpLess = 1,
        GraphicsCompareOpEqual = 2,
        GraphicsCompareOpLessOrEqual = 3,
        GraphicsCompareOpGreater = 4,
        GraphicsCompareOpNotEqual = 5,
        GraphicsCompareOpGreaterOrEqual = 6,
        GraphicsCompareOpAlways = 7,
        GraphicsCompareOpMaxEnum = 0x7FFFFFFF
    };

    // From vulkan sepc.
    enum class GraphicsStencilOp : uint32_t
    {
        GraphicsStencilOpKeep = 0,
        GraphicsStencilOpZero = 1,
        GraphicsStencilOpReplace = 2,
        GraphicsStencilOpIncrementAndClamp = 3,
        GraphicsStencilOpDecrementAndClamp = 4,
        GraphicsStencilOpInvert = 5,
        GraphicsStencilOpIncrementAndWrap = 6,
        GraphicsStencilOpDecrementAndWrap = 7,
        GraphicsStencilOpMaxEnum = 0x7FFFFFFF
    };

    uint32_t asVertexFormatSize(GraphicsVertexFormat format);
    uint32_t asTexelSize(GraphicsPixelFormat format);

    enum GraphicsTargetBufferFlagBits : uint8_t
    {
        GraphicsTargetBufferFlagBitNone = 0,
        GraphicsTargetBufferFlagBitColor = 1 << 0,
        GraphicsTargetBufferFlagBitDepth = 1 << 1,
        GraphicsTargetBufferFlagBitStencil = 1 << 2,
        GraphicsTargetBufferFlagBitColorDepth = GraphicsTargetBufferFlagBitColor | GraphicsTargetBufferFlagBitDepth,
        GraphicsTargetBufferFlagBitAll = GraphicsTargetBufferFlagBitColorDepth | GraphicsTargetBufferFlagBitStencil,
    };
    typedef uint8_t GraphicsTargetBufferFlags;

    struct GraphicsRenderPassFlags
    {
        GraphicsTargetBufferFlags clear;
        GraphicsTargetBufferFlags loadDiscard;
        GraphicsTargetBufferFlags storeDiscard;
    };


} // namespace el

#endif // __GRAPHICS_TYPES_H__
