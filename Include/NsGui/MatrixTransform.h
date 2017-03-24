////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MATRIXTRANSFORM_H__
#define __GUI_MATRIXTRANSFORM_H__


#include <Noesis.h>
#include <NsGui/Transform.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Creates an arbitrary affine matrix transformation that is used to manipulate
/// objects or coordinate systems in a 2-D plane.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.matrixtransform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API MatrixTransform: public Transform
{
public:
    MatrixTransform();
    MatrixTransform(const Math::Transform2f& matrix);
    ~MatrixTransform();

    /// Parses a string value to create an instance of a MatrixTransform
    static NsBool TryParse(const NsChar* str, Ptr<MatrixTransform>& result);

    /// Gets or sets matrix
    //@{
    const Math::Transform2f& GetMatrix() const;
    void SetMatrix(const Math::Transform2f& matrix);
    //@}

    /// From Transform
    //@{
    Math::Transform2f GetTransform() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UnregisterRenderer(ViewId viewId);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* MatrixProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& e);
    //@}

private:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Matrix
    };

    NS_DECLARE_REFLECTION(MatrixTransform, Transform)
};

}
}

#endif
