////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_TEXTUREPROVIDER_H__
#define __DRAWING_TEXTUREPROVIDER_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/PtrForward.h>
#include <NsCore/ReflectionImplementEmpty.h>


NS_CFORWARD(Render, Texture);
NS_CFORWARD(Render, RenderDevice);


namespace Noesis
{
namespace Drawing
{

// Texture metadata
struct TextureInfo
{
    NsSize width;
    NsSize height;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for implementing providers of textures
////////////////////////////////////////////////////////////////////////////////////////////////////
class TextureProvider: public Core::BaseComponent
{
public:
    /// Returns metadata for the given texture. Returns 0 x 0 if no texture found
    virtual TextureInfo GetTextureInfo(const NsChar* uri) = 0;

    /// Creates texture in the given device. Returns null if no texture found
    virtual Ptr<Render::Texture> LoadTexture(const NsChar* uri, Render::RenderDevice* device) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(TextureProvider, Core::BaseComponent)
};

}
}

#endif
