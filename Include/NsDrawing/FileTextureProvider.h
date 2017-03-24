////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __DRAWING_FILETEXTUREPROVIDER_H__
#define __DRAWING_FILETEXTUREPROVIDER_H__


#include <Noesis.h>
#include <NsDrawing/TextureProvider.h>
#include <NsDrawing/TextureProviderApi.h>


NS_CFORWARD(Core, Stream)


namespace Noesis
{
namespace Drawing
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A texture provider that loads standard image files (jpg, png, bmp, gif) from streams returned
/// by inheritors and create textures in the given device
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_DRAWING_TEXTUREPROVIDER_API FileTextureProvider: public TextureProvider
{
public:
    FileTextureProvider();

protected:
    virtual Ptr<Core::Stream> OpenStream(const NsChar* uri) const = 0;

private:
    /// From TextureProvider
    //@{
    TextureInfo GetTextureInfo(const NsChar* uri) override;
    Ptr<Render::Texture> LoadTexture(const NsChar* uri, Render::RenderDevice* device) override;
    //@}

private:
    NsByte mGammaTable[256];
};

NS_WARNING_POP

}
}

#endif
