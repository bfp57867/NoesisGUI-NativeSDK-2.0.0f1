
////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_INTEGRATIONAPI_H__
#define __GUI_INTEGRATIONAPI_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/LoggerMacros.h>
#include <NsCore/Ptr.h>
#include <NsCore/DynamicCast.h>


NS_CFORWARD(Core, BaseComponent)
NS_CFORWARD(Core, MemoryAllocator)
NS_CFORWARD(Render, RenderDevice)
NS_IFORWARD(Gui, IView)
NS_CFORWARD(Gui, UIElement)
NS_CFORWARD(Gui, FrameworkElement)
NS_CFORWARD(Gui, ResourceDictionary)
NS_CFORWARD(Gui, XamlProvider)
NS_CFORWARD(Drawing, TextureProvider)
NS_CFORWARD(Drawing, FontProvider)


namespace Noesis
{
namespace Gui
{

typedef Core::BaseComponent VGContext;

// Xaml, texture and font provider
struct Provider
{
    Gui::XamlProvider* xamlProvider;
    Drawing::TextureProvider* textureProvider;
    Drawing::FontProvider* fontProvider;
};

// Vector graphics renderer initialization options
struct VGOptions
{
    VGOptions(): offscreenWidth(0), offscreenHeight(0), offscreenSampleCount(1),
        offscreenDefaultNumSurfaces(0), offscreenMaxNumSurfaces(0),
        glyphCacheTextureWidth(1024), glyphCacheTextureHeight(1024),
        glyphCacheMeshTreshold(96) {}

    /// Dimensions of offscreen textures (0 = automatic)
    NsSize offscreenWidth;
    NsSize offscreenHeight;

    /// Multisampling of offscreen textures
    NsSize offscreenSampleCount;

    /// Number of offscreen textures created at startup
    NsSize offscreenDefaultNumSurfaces;

    /// Maximum number of offscreen textures (0 = unlimited)
    NsSize offscreenMaxNumSurfaces;

    /// Dimensions of texture used to cache glyphs
    NsSize glyphCacheTextureWidth;
    NsSize glyphCacheTextureHeight;

    /// Glyphs with size above this are rendered using triangles meshes
    NsSize glyphCacheMeshTreshold;
};

namespace GUI
{
    /// Initialization passing fatal error handler and optional memory allocator.
    /// Errors notified through the handler are always unrecoverable. Application must terminate
    typedef void (*ErrorHandler)(const NsChar* filename, NsSize line, const NsChar* desc, 
        NsBool fatal);
    NS_GUI_CORE_API void Init(ErrorHandler h, Core::MemoryAllocator* allocator = 0);

    /// Indicates that resources (xaml, images, fonts) will be loaded from the given local folder
    NS_GUI_CORE_API void SetResourceProvider(const NsChar* rootFolder);

    /// Provides custom loaders for each kind of resource
    NS_GUI_CORE_API void SetResourceProvider(const Provider& provider);

    /// Sets Theme dictionary containing default styles and resources for all controls
    NS_GUI_CORE_API void SetTheme(ResourceDictionary* theme);

    /// Sets the callbacks used for showing/hiding the software keyboard on touch devices
    typedef void(*ShowSoftwareKeyboardCallbackFn)(UIElement* focusedElement);
    typedef void(*HideSoftwareKeyboardCallbackFn)();
    NS_GUI_CORE_API void SetSoftwareKeyboardCallbacks(ShowSoftwareKeyboardCallbackFn showCallback,
        HideSoftwareKeyboardCallbackFn hideCallback);

    /// Loads a XAML. If it is not found by the provider an error is raised and null is returned
    NS_GUI_CORE_API Ptr<Core::BaseComponent> LoadXaml(const NsChar* filename);

    /// Loads a XAML and casts to given class
    template<class T> Ptr<T> LoadXaml(const NsChar* filename)
    {
        Ptr<T> root;

        Ptr<Core::BaseComponent> xaml = LoadXaml(filename);
        if (xaml != 0)
        {
            root = NsDynamicCast< Ptr<T> >(xaml);
            if (root == 0)
            {
                NS_ERROR("LoadXaml('%s'): invalid requested root type", filename);
            }
        }

        return root;
    }

    /// Loads contents of the specified component from a XAML. If it is not found by the provider
    /// an error is raised. Used from InitializeComponent, supplied component must match the type of
    /// the XAML root
    NS_GUI_CORE_API void LoadComponent(Core::BaseComponent* component, const NsChar* filename);

    /// Creates vector graphics context. Needed to initialize the renderer of a view. Note that
    /// several views can share the same context if they are rendered in the same thread
    NS_GUI_CORE_API Ptr<VGContext> CreateVGContext(Render::RenderDevice* device,
        const VGOptions& options);

    /// Creates a view with the given content. After the view is created its renderer must be
    /// initialized in the corresponding thread
    NS_GUI_CORE_API Ptr<IView> CreateView(FrameworkElement* content);

    /// Shuts down
    NS_GUI_CORE_API void Shutdown();
}
}
}

#endif
