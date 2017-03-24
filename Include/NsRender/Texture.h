////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __RENDER_TEXTURE_H__
#define __RENDER_TEXTURE_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Ptr.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsRender/RenderDevice.h>
#include <NsRender/RenderDeviceApi.h>


namespace Noesis
{
namespace Render
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for 2D textures
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_RENDER_RENDERDEVICE_API Texture: public Core::BaseComponent
{
public:
    /// Returns the width of the texture
    virtual NsSize GetWidth() const = 0;

    /// Returns the height of the texture
    virtual NsSize GetHeight() const = 0;

    /// Returns the format of the texture
    virtual TextureFormat::Enum GetFormat() const = 0;

    /// True if the texture has mipmaps
    virtual NsBool HasMipMaps() const = 0;

    /// True is the texture must be vertically inverted when mapped. This is true for render targets
    /// on platforms (OpenGL) where texture V coordinate is zero at the "bottom of the texture"
    virtual NsBool IsInverted() const = 0;

    /// Sets a user context associated with the texture. We use it for example to store the managed
    /// texture object to avoid GC to release it
    void SetContext(Core::BaseComponent* context);

private:
    Ptr<Core::BaseComponent> mContext;

    NS_DECLARE_REFLECTION(Texture, BaseComponent)
};

NS_WARNING_POP

}
}


#endif
