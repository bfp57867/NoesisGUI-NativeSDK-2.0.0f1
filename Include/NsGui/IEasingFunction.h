////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IEASINGFUNCTION_H__
#define __GUI_IEASINGFUNCTION_H__


#include <Noesis.h>
#include <NsCore/Interface.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// IEasingFunction
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE IEasingFunction: public Core::Interface
{
    /// Transforms normalized time to control the pace of an animation.
    virtual NsFloat32 Ease(NsFloat32 normalizedTime) = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(IEasingFunction, Core::Interface)
};

}
}

#endif