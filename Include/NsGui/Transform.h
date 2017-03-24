////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRANSFORM_H__
#define __GUI_TRANSFORM_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Animatable.h>
#include <NsGui/IRenderProxyCreator.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>
#include <NsCore/TypeMetaData.h>
#include <NsMath/TransformForward.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

// TODO: [srodriguez] Transform must derive from GeneralTransform

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Transform. Defines functionality that enables transformations in a 2-D plane. Transformations
/// include rotation (RotateTransform), 
/// scale (ScaleTransform), 
/// skew (SkewTransform), and translation (TranslateTransform).
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.transform.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Transform: public Animatable, public IRenderProxyCreator
{
public:
    NS_DISABLE_COPY(Transform)

    Transform();
    virtual ~Transform() = 0;
    
    /// Parses a string value to create an instance of a MatrixTransform
    static NsBool TryParse(const NsChar* str, Ptr<Transform>& result);

    /// Gets Identity transform object
    /// \prop
    static Transform* GetIdentity();

    /// Gets the transformation matrix defined by a transform object
    virtual Math::Transform2f GetTransform() const = 0;

    NS_IMPLEMENT_INTERFACE_FIXUP

private:
    NS_DECLARE_REFLECTION(Transform, Animatable)
};

NS_WARNING_POP

}
}

#endif
