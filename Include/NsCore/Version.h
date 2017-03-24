////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_VERSION_H__
#define __CORE_VERSION_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>


namespace Noesis
{
namespace Core
{
 
/// Returns the build version, for example "1.2.6f5"
NS_CORE_KERNEL_API const NsChar* GetBuildVersion();

}
}

#endif
