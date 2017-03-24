////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_BASECOMPONENT_H__
#define __CORE_BASECOMPONENT_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/BaseRefCounted.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for components
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API BaseComponent: public BaseRefCounted
{
public:
    NS_DISABLE_COPY(BaseComponent)

    BaseComponent();
    virtual ~BaseComponent() = 0;

private:
    NS_DECLARE_REFLECTION(BaseComponent, BaseRefCounted)
};

}
}


#endif
