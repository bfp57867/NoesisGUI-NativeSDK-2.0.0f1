////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __RENDER_GLRENDERDEVICE_H__
#define __RENDER_GLRENDERDEVICE_H__


#include <NsRender/RenderDevice.h>

#include "GLHeaders.h"


class GLTexture;
class GLRenderTarget;


namespace Noesis
{
namespace Render
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// GLRenderDevice
////////////////////////////////////////////////////////////////////////////////////////////////////
class GLRenderDevice final: public RenderDevice
{
public:
    GLRenderDevice();
    ~GLRenderDevice();

    // Creates a Noesis texture from a GL texture
    static Ptr<Texture> WrapTexture(GLuint object, NsSize width, NsSize height, NsSize levels,
        TextureFormat::Enum format, NsBool isInverted);
    
    // Disconnect bound objects to avoid them being unintentionally modified by external code
    void UnbindObjects() const;

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

    friend class ::GLTexture;
    friend class ::GLRenderTarget;
    void DeleteTexture(GLTexture* texture);
    void DeleteRenderTarget(GLRenderTarget* surface);

    void InvalidateStateCache();

    struct DynamicBuffer;
    void CreateBuffer(DynamicBuffer& buffer, GLenum target, NsSize size) const;
    void DestroyBuffer(DynamicBuffer& buffer) const;
    void BindBuffer(DynamicBuffer& buffer);
    void SetVertexFormat(NsUInt8 format, NsUIntPtr offset);
    void DisableClientState() const;
    void EnableVertexAttribArrays(NsUInt32 state);
    void* MapBuffer(DynamicBuffer& buffer, NsSize size);
    void UnmapBuffer(DynamicBuffer& buffer);
    void CreateSamplers();
    void CreatePrograms();
    void CreateVertexFormats();
    GLboolean HaveMapBufferRange() const;
    GLvoid* MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length,
        GLbitfield access) const;
    void UnmapBuffer(GLenum target) const;
    GLboolean HaveVertexArrayObject() const;
    void GenVertexArrays(GLsizei n, GLuint *arrays) const;
    void BindVertexArray(GLuint name);
    void DeleteVertexArrays(GLsizei n, const GLuint *arrays) const;
    GLboolean IsVertexArray(GLuint array) const;

    GLuint RenderbufferStorage(GLsizei samples, GLenum format, GLsizei width, GLsizei height) const;
    void RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat,
        GLsizei width, GLsizei height) const;
    GLboolean HaveMultisampledRenderToTexture() const;
    void FramebufferTexture2DMultisample(GLenum target, GLenum attachment, GLenum textarget,
        GLuint texture, GLint level, GLsizei samples) const;
    GLuint CreateStencil(GLsizei width, GLsizei height, GLsizei samples) const;
    GLuint CreateColor(GLsizei width, GLsizei height, GLsizei samples) const;
    void CreateFBO(GLsizei samples, GLuint texture, GLuint stencil, GLuint colorAA, GLuint& fbo,
        GLuint& fboResolved) const;
    void Resolve(GLRenderTarget* target, const Tile* tiles, NsSize numTiles);
    void BindRenderTarget(GLRenderTarget* renderTarget);
    void CheckFramebufferStatus() const;
    void DiscardFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments) const;
    NsBool HaveBlitFramebuffer() const;
    void BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0,
        GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const;
    void DeleteFramebuffer(GLuint framebuffer) const;
    void DeleteRenderbuffer(GLuint renderbuffer) const;

    NsBool HaveBorderClamp() const;
    NsBool HaveTexStorage() const;
    NsBool HaveTexRG() const;
    void GetGLFormat(TextureFormat::Enum texFormat, GLenum& internalFormat, GLenum& format,
        GLenum& type);
    GLint GLWrapSMode(SamplerState sampler) const;
    GLint GLWrapTMode(SamplerState sampler) const;
    GLint GLMinFilter(SamplerState sampler) const;
    GLint GLMagFilter(SamplerState sampler) const;

    void TexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width,
        GLsizei height);
    void InitTexture(GLTexture* texture, GLenum internalFormat, GLenum format, GLenum type);
    void SetTextureState(GLTexture* texture, SamplerState state);
    void SetTexture(NsSize unit, GLTexture* texture, SamplerState state);
    void SetTextures(const Batch& batch);
    void ActiveTexture(NsSize unit);
    void BindTexture2D(GLuint texture);
    void SetUnpackState();
    void TexSubImage2D(GLint level, GLint xoffset, GLint yoffset, GLint width, GLint height,
        GLenum format, GLenum type, const GLvoid* data);
    void BindSampler(GLuint sampler);
    void DeleteSampler(GLuint sampler) const;
    void DeleteTexture(GLuint texture) const;

    GLuint CompileShader(GLenum type, const NsChar* source) const;
    GLuint LinkProgram(GLuint vso, GLuint pso, const NsChar** binds) const;
    void BindTextureLocation(GLuint program, const NsChar* name, GLint unit);
    void ActivateProgram(const Batch& batch);
    void UseProgram(GLuint name);
    void DeleteShader(GLuint shader) const;
    void DeleteProgram(GLuint program) const;

    union GLRenderState;
    void SetRenderState(GLRenderState state);
    void EnableScissor();
    void EnableColor();
    void Scissor(NsUInt32 x, NsUInt32 y, NsUInt32 width, NsUInt32 height);
    void Viewport(NsSize width, NsSize height);
    void SetClearColor(NsUInt32 color);
    void SetClearStencil(NsUInt32 stencil);

    void BindAPI();
    void DetectGLVersion();
    void FindExtensions();
    NsSize MaxSamples() const;
    void FillCaps();
 
    void PushGroupMarker(GLsizei length, const char *marker) const;
    void PopGroupMarker() const;

    GLint GetInteger(GLenum name) const;
    GLint GetInteger(GLenum name, NsSize i) const;
    GLfloat GetFloat(GLenum name) const;
    GLfloat GetFloat(GLenum name, NsSize i) const;
    GLboolean GetBoolean(GLenum name, NsSize i) const;
    GLboolean VertexAttribArrayEnabled(GLuint index) const;
    GLint GetTexParameter(GLenum name) const;

private:
    NsUInt32 mGLVersion;

#if NS_RENDERER_USE_WGL
    HMODULE mOpenGL32;
    PFNWGLGETPROCADDRESSPROC wglGetProcAddress;
    PFNWGLGETCURRENTCONTEXT wglGetCurrentContext;
#endif

    #define GL_IMPORT(_optional, _proto, _func) _proto _func
    #include "GLImports.h"
    #undef GL_IMPORT

    struct Attr
    {
        enum
        {
            Pos,
            Color,
            Tex0,
            Tex1,
            Coverage,

            Count
        };
    };

    NsSize mMaxVertexAttribs;

    struct VertexFormat
    {
        GLuint vao;
        GLsizei stride;
    };

    VertexFormat mVertexFormats[16];

    struct DynamicBuffer
    {
        GLenum target;
        GLuint object;
        GLuint boundObject;
        NsSize size;
        NsSize pos;
        NsSize drawPos;
        void* cpuMemory;
    };

    DynamicBuffer mDynamicVB;
    DynamicBuffer mDynamicIB;
    GLuint mDefaultVAO;

    DeviceCaps mCaps;

    struct ProgramInfo
    {
        NsUInt8 vertexFormat;
        GLuint object;

        NsInt8 projectionMtxLocation;
        NsInt8 opacityLocation;
        NsInt8 radialGradLocation;
        NsInt8 rgbaLocation;

        NsUInt32 projectionMtxHash;
        NsUInt32 opacityHash;
        NsUInt32 radialGradHash;
        NsUInt32 rgbaHash;
    };

    ProgramInfo mPrograms[84];
    GLuint mSamplers[64];

    struct TextureUnit
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

    union GLRenderState
    {
        struct
        {
            NsUInt32 invalidated:1;
            NsUInt32 scissorEnable:1;
            NsUInt32 colorMask:4;
            NsUInt32 blendEnable:1;
            NsUInt32 stencilEnable:1;
            NsUInt32 stencilMode:2;
            NsUInt32 stencilRef:8;

        } f;

        NsUInt32 v;

        GLRenderState(): v(0) {}
        GLRenderState(RenderState state, GLint stencilRef);
    };

    //Cached state
    //@{
    NsUInt32 mViewportWidth, mViewportHeight;
    NsUInt32 mScissorX, mScissorY, mScissorWidth, mScissorHeight;
    NsUInt64 mClearColor;
    NsUInt32 mClearStencil;
    GLuint mVertexArray;
    NsUInt32 mActiveTextureUnit;
    GLRenderState mRenderState;
    GLuint mBoundTextures[TextureUnit::Count];
    GLuint mBoundSamplers[TextureUnit::Count];
    GLuint mProgram;
    NsUInt32 mEnabledVertexAttribArrays;
    GLRenderTarget* mBoundRenderTarget;
    NsBool mUnpackStateSet;
    //@}

    struct Extension
    {
        enum Enum
        {
            ANGLE_framebuffer_blit,
            ANGLE_framebuffer_multisample,
            EXT_texture_format_BGRA8888,
            EXT_map_buffer_range,
            EXT_discard_framebuffer,
            EXT_framebuffer_blit,
            EXT_framebuffer_multisample,
            EXT_multisampled_render_to_texture,
            EXT_texture_compression_s3tc,
            EXT_debug_marker,
            EXT_texture_storage,
            EXT_texture_rg,
            EXT_texture_border_clamp,
            APPLE_texture_format_BGRA8888,
            APPLE_framebuffer_multisample,
            APPLE_texture_max_level,
            APPLE_vertex_array_object,
            ARB_half_float_vertex,
            ARB_debug_output,
            ARB_map_buffer_range,
            ARB_vertex_array_object,
            ARB_framebuffer_object,
            ARB_invalidate_subdata,
            ARB_ES3_compatibility,
            ARB_texture_storage,
            ARB_texture_rg,
            ARB_vertex_attrib_binding,
            ARB_sampler_objects,
            ARB_texture_border_clamp,
            OES_vertex_half_float,
            OES_packed_depth_stencil,
            OES_rgb8_rgba8,
            OES_vertex_array_object,
            IMG_multisampled_render_to_texture,
            KHR_debug,

            Count
        };

        NsBool supported;
    };

    NsBool IsSupported(Extension::Enum extension) const;
    Extension mExtensions[Extension::Count];

    GLvoid* (GL_APIENTRYP MapBufferRange_)(GLenum, GLintptr, GLsizeiptr, GLbitfield);
    GLboolean (GL_APIENTRYP UnmapBuffer_)(GLenum);
    void (GL_APIENTRYP BindVertexArray_)(GLuint);
    void (GL_APIENTRYP DeleteVertexArrays_)(GLsizei, const GLuint *);
    void (GL_APIENTRYP GenVertexArrays_)(GLsizei, GLuint *);
    GLboolean (GL_APIENTRYP IsVertexArray_)(GLuint array);
    void (GL_APIENTRYP BlitFramebuffer_)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint,
        GLbitfield, GLenum);
    void (GL_APIENTRYP RenderbufferStorageMultisample_)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
    void (GL_APIENTRYP FramebufferTexture2DMultisample_)(GLenum, GLenum, GLenum, GLuint, GLint,
        GLsizei);
    void (GL_APIENTRYP InvalidateFramebuffer_)(GLenum, GLsizei, const GLenum *);
    void (GL_APIENTRYP PushGroupMarker_)(GLsizei, const GLchar*);
    void (GL_APIENTRYP PopGroupMarker_)();
    void (GL_APIENTRYP TexStorage2D_)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
};

}
}

#endif
