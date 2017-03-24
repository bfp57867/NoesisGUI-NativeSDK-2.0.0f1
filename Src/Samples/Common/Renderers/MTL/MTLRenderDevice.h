////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __RENDER_MTLRENDERDEVICE_H__
#define __RENDER_MTLRENDERDEVICE_H__


#include <NsRender/RenderDevice.h>
#include <NsCore/PtrForward.h>
#include <NsCore/HashMap.h>

#include <Metal/Metal.h>


class MTLTexture;


namespace Noesis
{
namespace Render
{


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Apple Metal render device
///
/// Metal device requires setting a command buffer (if offscreen is needed) and a command encoder
/// per frame. Something like this:
///
/// .. code-block:: c++
///
///    renderer->UpdateRenderTree();
///
///    if (renderer->NeedsOffscreen())
///    {
///        device->SetOffScreenCommandBuffer(commands);
///        renderer->RenderOffscreen();
///    }
///
///    commandEncoder = [commands renderCommandEncoderWithDescriptor:passDescriptor];
///
///    device->SetOnScreenEncoder(commandEncoder);
///    renderer->Render();
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class MTLRenderDevice final: public RenderDevice
{
public:
    MTLRenderDevice(id<MTLDevice> device, MTLPixelFormat colorFormat, MTLPixelFormat depthFormat,
        MTLPixelFormat stencilFormat, NsSize sampleCount);
    ~MTLRenderDevice();

    // Creates a Noesis texture from a Metal texture
    static Ptr<Texture> WrapTexture(id<MTLTexture> texture, NsSize width, NsSize height,
        NsSize levels, TextureFormat::Enum format, NsBool isInverted);

    /// The passed command buffer will be used for each offscreen render pass
    /// This method must be invoked per frame and before rendering offscreens
    void SetOffScreenCommandBuffer(id<MTLCommandBuffer> commands);

    /// The passed encoder will be used to generate the commands for the onscreen rendering
    /// This method must be invoked per frame and before the main rendering
    void SetOnScreenEncoder(id<MTLRenderCommandEncoder> encoder);

private:
    /// From RenderDevice
    //@{
    const DeviceCaps& GetCaps() const override;
    Ptr<RenderTarget> CreateRenderTarget(const NsChar* label, NsSize width, NsSize height,
        NsSize sampleCount) override;
    Ptr<RenderTarget> CloneRenderTarget(const NsChar* label, RenderTarget* surface) override;
    Ptr<Texture> CreateTexture(const NsChar* label, NsSize width, NsSize height, NsSize numLevels,
        TextureFormat::Enum format) override;
    void UpdateTexture(Texture* texture, NsSize level, NsSize x, NsSize y, NsSize width,
        NsSize height, const void* data) override;
    void BeginRender(NsBool offscreen) override;
    void SetRenderTarget(RenderTarget* surface) override;
    void BeginTile(const Tile& tile, NsSize surfaceWidth, NsSize surfaceHeight) override;
    void EndTile() override;
    void ResolveRenderTarget(RenderTarget* surface, const Tile* tiles, NsSize numTiles) override;
    void EndRender() override;
    void* MapVertices(NsSize bytes) override;
    void UnmapVertices() override;
    void* MapIndices(NsSize bytes) override;
    void UnmapIndices() override;
    void DrawBatch(const Batch& batch) override;
    //@}

    void InvalidateStateCache();

    void SetRenderPipelineState(id<MTLRenderPipelineState> pipeline);
    void SetDepthStencilState(id<MTLDepthStencilState> state, NsUInt32 stencilRef);
    void SetFillMode(MTLTriangleFillMode fillMode);
    void SetRenderState(const Batch& batch);
    void SetBuffers(const Batch& batch);
    void SetFragmentTexture(NsSize index, id<MTLTexture> texture);
    void SetFragmentSamplerState(NsSize index, id<MTLSamplerState> sampler);
    void SetTexture(NsSize index, MTLTexture* texture, SamplerState state);
    void SetTextures(const Batch& batch);

    id<MTLTexture> CreateAttachment(NsSize width, NsSize height, NsSize sampleCount,
        MTLPixelFormat format, MTLTextureUsage usage) const;
    Ptr<RenderTarget> CreateRenderTarget(const NsChar* label, NsSize width, NsSize height,
        id<MTLTexture> colorAA, id<MTLTexture> stencil) const;
    void CreateBuffers();
    void CreateSamplers();
    void CreatePipelines();
    void FillCaps();

    struct DynamicBuffer;
    void* MapBuffer(DynamicBuffer& buffer, NsSize size) const;

private:
    MTLPixelFormat mColorFormat;
    MTLPixelFormat mDepthFormat;
    MTLPixelFormat mStencilFormat;
    NsSize mSampleCount;

    id<MTLDevice> mDevice;
    id<MTLCommandBuffer> mCommandBuffer;
    id<MTLRenderCommandEncoder> mCommandEncoder;

    struct DynamicBuffer
    {
        id<MTLBuffer> object;
        NsSize size;
        NsSize pos;
        NsSize drawPos;
    };

    DynamicBuffer mDynamicVB;
    DynamicBuffer mDynamicIB;

    id<MTLRenderPipelineState> mClearPipeline;
    typedef NsHashMap<NsUInt16, id<MTLRenderPipelineState>> Pipelines;
    Pipelines mPipelines;

    MTLTextureDescriptor* mTextureDesc;

    id<MTLSamplerState> mSamplers[64];
    id<MTLDepthStencilState> mDepthStencilStates[5];

    struct TextureIndex
    {
        enum Enum
        {
            Pattern,
            Ramps,
            Image,
            Glyphs,

            Count
        };
    };

    id<MTLRenderPipelineState> mCachedPipelineState;
    id <MTLSamplerState> mCachedSamplerStates[TextureIndex::Count];
    id <MTLTexture> mCachedTextures[TextureIndex::Count];
    MTLTriangleFillMode mCachedFillMode;
    id <MTLDepthStencilState> mCachedDepthStencilState;
    NsUInt32 mCachedStencilRef;
    NsUInt32 mCachedVertexCBHash;
    NsUInt32 mCachedFragmentCBHash;

    DeviceCaps mCaps;
    NsBool miOS9Runtime;
};

}
}

#endif
