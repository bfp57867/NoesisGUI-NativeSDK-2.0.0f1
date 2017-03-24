////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MESHGEOMETRY_H__
#define __GUI_MESHGEOMETRY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Geometry.h>
#include <NsDrawing/Rect.h>
#include <NsCore/Vector.h>


NS_SFORWARD(Drawing, Point)


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a geometric shape, described using a mesh of vertices and indices.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API MeshGeometry: public Geometry
{
public:
    MeshGeometry();

    /// Sets number of vertices
    void SetNumVertices(NsSize numVertices);

    /// Sets number of indices
    void SetNumIndices(NsSize numIndices);

    /// Sets bounding box
    void SetBounds(const Drawing::Rect& bounds);

    /// Returns a pointer to the internal vertex buffer
    Drawing::Point* GetVertices();
    
    /// Returns a pointer to the internal index buffer
    NsUInt16* GetIndices();

    /// Notify about a change in the geometry
    void Update();

    /// From Geometry
    //@{
    NsBool IsEmpty() const override;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex) override;
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex) override;
    //@}

protected:
    /// From Freezable
    //@{
    Ptr<Freezable> CreateInstanceCore() const override;
    void CloneCommonCore(const Freezable* source) override;
    //@}

    /// From Geometry
    //@{
    Drawing::Rect GetRenderBoundsOverride(Pen* pen) const override;
    NsBool FillContainsOverride(const Drawing::Point& point) const override;
    NsBool StrokeContainsOverride(Pen* pen, const Drawing::Point& point) const override;
    //@}

private:
    enum UpdateFlags
    {
        UpdateFlags_Mesh = Geometry::UpdateFlags_Sentinel
    };

    NsVector<Drawing::Point> mVertices;
    NsVector<NsUInt16> mIndices;
    Drawing::Rect mBounds;

    NS_DECLARE_REFLECTION(MeshGeometry, Geometry)
};

NS_WARNING_POP

}
}


#endif
