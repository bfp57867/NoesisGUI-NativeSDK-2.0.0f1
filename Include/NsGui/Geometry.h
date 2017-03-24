////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GEOMETRY_H__
#define __GUI_GEOMETRY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Animatable.h>
#include <NsGui/IRenderProxyCreator.h>


NS_SFORWARD(Drawing, Rect)
NS_SFORWARD(Drawing, Point)
NS_CFORWARD(Gui, Transform)
NS_CFORWARD(Gui, Pen)
NS_SFORWARD(Gui, GeometryProxy)
class Noesis_RectangleTest;


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Classes that derive from this abstract base class define geometric shapes. Geometry
/// objects can be used for clipping, hit-testing, and rendering 2-D graphic data.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.geometry.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Geometry: public Animatable, public IRenderProxyCreator
{
public:
    NS_DISABLE_COPY(Geometry)

    Geometry();
    virtual ~Geometry() = 0;

    /// Creates a new Geometry instance from the specified string
    static NsBool TryParse(const NsChar* str, Ptr<Geometry>& result);

    /// Determines whether the object is empty
    virtual NsBool IsEmpty() const;

    /// Gets geometry bounds
    /// \prop
    Drawing::Rect GetBounds() const;

    /// Returns an axis-aligned rectangle that is exactly large enough to contain the geometry after it
    /// has been outlined with the specified Pen
    Drawing::Rect GetRenderBounds(Pen* pen) const;

    /// Indicates whether the geometry contains the specified Point
    NsBool FillContains(const Drawing::Point& point) const;
    
    /// Determines whether the specified Point is contained in the stroke produced by applying the
    /// specified Pen to the geometry
    NsBool StrokeContains(Pen* pen, const Drawing::Point& point) const;

    /// Gets or sets the Transform object applied to a Geometry
    //@{
    Transform* GetTransform() const;
    void SetTransform(Transform* transform);
    //@}

    /// From IRenderProxyCreator
    //@{
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex) override;
    void UnregisterRenderer(ViewId viewId) override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

public:
    /// Dependency Properties
    static const DependencyProperty* TransformProperty;

protected:
    /// Implements geometry render bounds calculation
    virtual Drawing::Rect GetRenderBoundsOverride(Pen* pen) const;

    /// Implements contain tests
    //@{
    virtual NsBool FillContainsOverride(const Drawing::Point& point) const;
    virtual NsBool StrokeContainsOverride(Pen* pen, const Drawing::Point& point) const;
    //@}

    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args) override;
    NsBool OnSubPropertyChanged(const DependencyProperty* dp) override;
    //@}

protected:
    friend class ::Noesis_RectangleTest;

    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Transform,

        UpdateFlags_Sentinel
    };

private:
    NS_DECLARE_REFLECTION(Geometry, Animatable)
};

NS_WARNING_POP

}
}

#endif
