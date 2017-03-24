////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __RENDER_RENDERDEVICE_H__
#define __RENDER_RENDERDEVICE_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/PtrForward.h>
#include <NsRender/RenderDeviceApi.h>


NS_CFORWARD(Render, RenderTarget)
NS_CFORWARD(Render, Texture)


namespace Noesis
{
namespace Render
{

// Texture formats enumeration
struct TextureFormat
{
    enum Enum
    {
        BGRA8,
        BGRX8,
        R8,
        BC1,
        BC2,
        BC3,

        Count
    };
};

// Render device capabilities
struct DeviceCaps
{
    // Offset in pixel units from top-left corner to center of pixel 
    NsFloat32 centerPixelOffset;

    // Maximum size that can be passed to MapVertices function
    NsSize dynamicVerticesSize;

    // Maximum size that can be passed to MapIndices function
    NsSize dynamicIndicesSize;

    // If texture coordinates can be sent as float16 or float32 to this device
    NsBool halfFloatUV;

    // If the device writes to the render target in linear or gamma space
    NsBool linearRendering;

    // Texture format availability
    NsBool supportedTextureFormats[TextureFormat::Count];
};

// Shader effect
struct Effect
{
    enum Enum
    {
        RGBA,
        Mask,
        Path,
        PathAA,
        ImagePaintOpacity,
        Text,

        Count
    };
};

// Shader paint
struct Paint
{
    enum Enum
    {
        Solid,
        Linear,
        Radial,
        Pattern,

        Count
    };
};

// Shaders, identified by 8-bit integers, are the combination of an effect with a given paint.
// The following table descibes the vertex data sent for each shader combination.
//
//  ------------------------------------------------------
//  Pos = X32Y32
//  Color = R8G8B8A8
//  Tex0 = caps.halfFloatUV ? U16V16 : U32V32
//  Tex1 = caps.halfFloatUV ? U16V16 : U32V32
//  Coverage = X32
//  ------------------------------------------------------
//  RGBA                        Pos
//  Mask                        Pos
//  PathSolid                   Pos | Color
//  PathLinear                  Pos | Tex0
//  PathRadial                  Pos | Tex0
//  PathPattern                 Pos | Tex0
//  PathAASolid                 Pos | Color | Coverage
//  PathAALinear                Pos | Tex0 | Coverage
//  PathAARadial                Pos | Tex0 | Coverage
//  PathAAPattern               Pos | Tex0 | Coverage
//  ImagePaintOpacitySolid      Pos | Color| Tex1
//  ImagePaintOpacityLinear     Pos | Tex0 | Tex1
//  ImagePaintOpacityRadial     Pos | Tex0 | Tex1
//  ImagePaintOpacityPattern    Pos | Tex0 | Tex1
//  TextSolid                   Pos | Color | Tex1
//  TextLinear                  Pos | Tex0 | Tex1
//  TextRadial                  Pos | Tex0 | Tex1
//  TextPattern                 Pos | Tex0 | Tex1
//  ------------------------------------------------------

union Shader
{
    struct
    {
        NsUInt8 paint:4;
        NsUInt8 effect:4;
    } f;

    NsUInt8 v;
};

// Alpha blending mode
struct BlendMode
{
    enum Enum
    {
        Src,
        SrcOver,

        Count
    };
};

// Stencil buffer mode
struct StencilMode
{
    enum Enum
    {
        Disabled,
        Equal_Keep,
        Equal_Incr,
        Equal_Decr,

        Count
    };
};

// Render state
union RenderState
{
    struct
    {
        NsUInt8 scissorEnable:1;
        NsUInt8 colorEnable:1;
        NsUInt8 blendMode:2;
        NsUInt8 stencilMode:2;
        NsUInt8 wireframe:1;
        NsUInt8 unused:1;
    } f;

    NsUInt8 v;
};

// Texture wrapping mode
struct WrapMode
{
    enum Enum
    {
        // Clamp between 0.0 and 1.0
        ClampToEdge,
        // Out of range texture coordinates return transparent zero (0,0,0,0)
        ClampToZero,
        // Wrap to the other side of the texture
        Repeat,
        // The same as repeat but flipping horizontally
        MirrorU,
        // The same as repeat but flipping vertically
        MirrorV,
        // The combination of MirrorU and MirrorV
        Mirror,

        Count
    };
};

// Texture minification and magnification filter
struct MinMagFilter
{
    enum Enum
    {
        // Select the single pixel nearest to the sample point
        Nearest,
        // Select two pixels in each dimension and interpolate linearly between them
        Linear,

        Count
    };
};

// Texture Mipmap filter
struct MipFilter
{
    enum Enum
    {
        // Texture sampled from mipmap level 0
        Disabled,
        // The nearest mipmap level is selected
        Nearest,
        // Both nearest levels are sampled and linearly interpolated
        Linear,

        Count
    };
};

// Texture sampler state
union SamplerState
{
    struct
    {
        NsUInt8 wrapMode:3;
        NsUInt8 minmagFilter:1;
        NsUInt8 mipFilter:2;
        NsUInt8 unused:2;
    } f;

    NsUInt8 v;
};

// Render batch information
struct Batch
{
    // Render state
    Shader shader;
    RenderState renderState;
    NsUInt8 stencilRef;

    // Draw parameters
    NsUInt32 vertexOffset;
    NsUInt32 startIndex;
    NsUInt32 numIndices;

    // Textures. Unused textures are set to null
    Texture* pattern;
    SamplerState patternSampler;

    Texture* ramps;
    SamplerState rampsSampler;

    Texture* image;
    SamplerState imageSampler;

    Texture* glyphs;
    SamplerState glyphsSampler;

    // Shader constants. Unused constants are set to null
    const NsFloat32 (*projMtx)[16];
    NsUInt32 projMtxHash;

    const NsFloat32* opacity;
    NsUInt32 opacityHash;

    const NsFloat32 (*rgba)[4];
    NsUInt32 rgbaHash;

    const NsFloat32 (*radialGrad)[8];
    NsUInt32 radialGradHash;
};

// A tile is a region of render target. The origin is located at the lower left corner
struct Tile
{
    NsUInt32 x;
    NsUInt32 y;
    NsUInt32 width;
    NsUInt32 height;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Abstraction of a graphics rendering device
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_RENDER_RENDERDEVICE_API RenderDevice: public Core::BaseComponent
{
public:
    /// Retrieves device render capabilities
    virtual const DeviceCaps& GetCaps() const = 0;

    /// Creates render target surface with given dimensions and number of samples
    virtual Ptr<RenderTarget> CreateRenderTarget(const NsChar* label, NsSize width, NsSize height,
        NsSize sampleCount) = 0;

    /// Creates render target sharing transient (stencil, colorAA) buffers with the given surface
    virtual Ptr<RenderTarget> CloneRenderTarget(const NsChar* label, RenderTarget* surface) = 0;

    /// Creates texture with given dimensions and format
    virtual Ptr<Texture> CreateTexture(const NsChar* label, NsSize width, NsSize height,
        NsSize numLevels, TextureFormat::Enum format) = 0;

    /// Updates texture mipmap copying the given image to desired position. The passed image is
    /// tightly packed (no extra pitch). Origin is located at the left of the first scanline
    virtual void UpdateTexture(Texture* texture, NsSize level, NsSize x, NsSize y, NsSize width,
        NsSize height, const void* data) = 0;

    /// Begins rendering offscreen or onscreen commands
    virtual void BeginRender(NsBool offscreen) = 0;

    /// Binds render target and sets viewport to cover the entire surface
    virtual void SetRenderTarget(RenderTarget* surface) = 0;

    /// Clears the given region to transparent (#000000) and sets the scissor rectangle to fit it.
    /// Until next call to EndTile() all rendering commands will only update the extents of the tile
    virtual void BeginTile(const Tile& tile, NsSize surfaceWidth, NsSize surfaceHeight) = 0;

    /// Completes rendering to the tile specified by BeginTile()
    virtual void EndTile() = 0;

    /// Resolves multisample render target
    virtual void ResolveRenderTarget(RenderTarget* surface, const Tile* tiles, NsSize numTiles) = 0;

    /// Ends rendering
    virtual void EndRender() = 0;

    /// Gets a pointer to stream vertices
    virtual void* MapVertices(NsSize bytes) = 0;

    /// Invalidates the pointer previously mapped
    virtual void UnmapVertices() = 0;

    /// Gets a pointer to stream 16-bit indices
    virtual void* MapIndices(NsSize bytes) = 0;

    /// Invalidates the pointer previously mapped
    virtual void UnmapIndices() = 0;

    /// Draws primitives for the given batch
    virtual void DrawBatch(const Batch& batch) = 0;

protected:
    /// Returns whether the passed render state is compatible with the given shader
    NsBool IsValidState(Shader shader, RenderState state) const;

    NS_DECLARE_REFLECTION(RenderDevice, BaseComponent)
};

}
}


#endif
