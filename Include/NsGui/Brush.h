////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BRUSH_H__
#define __GUI_BRUSH_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Animatable.h>
#include <NsGui/IRenderProxyCreator.h>


namespace Noesis
{

/// Forward declarations
//@{
namespace Gui
{
class Transform;
struct BrushProxy;
}
//@}

namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines objects used to paint graphical objects. Classes that derive from Brush describe how
/// the area is painted. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.brush.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Brush: public Animatable, public IRenderProxyCreator
{
public:
    NS_DISABLE_COPY(Brush)

    Brush();
    virtual ~Brush() = 0;

    /// Use this method to convert a Color string into a SolidColorBrush
    static NsBool TryParse(const NsChar* str, Ptr<Brush>& brush);

    /// Get/Set Opacity
    //@{
    NsFloat32 GetOpacity() const;
    void SetOpacity(NsFloat32 opacity);
    //@}

    /// Gets or sets the transformation that is applied to the brush using relative coordinates. 
    //@{
    Transform* GetRelativeTransform() const;
    void SetRelativeTransform(Transform* transform);
    //@}

    /// Gets or sets the transformation that is applied to the brush. This transformation is 
    /// applied after the brush's output has been mapped and positioned. 
    //@{
    Transform* GetTransform() const;
    void SetTransform(Transform* transform);
    //@}

    /// Indicates if this brush is transparent
    NsBool IsTransparent() const;

    /// From IRenderProxyCreator
    //@{
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex) override;
    void UnregisterRenderer(ViewId viewId) override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* OpacityProperty;
    static const DependencyProperty* RelativeTransformProperty;
    static const DependencyProperty* TransformProperty;
    //@}

protected:
    virtual NsBool IsTransparentOverride() const;

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args) override;
    NsBool OnSubPropertyChanged(const DependencyProperty* dp) override;
    //@}

protected:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Opacity,
        UpdateFlags_RelativeTransform,
        UpdateFlags_Transform,

        UpdateFlags_Sentinel
    };

private:
    NS_DECLARE_REFLECTION(Brush, Animatable)
};

NS_WARNING_POP

}
}

#endif
