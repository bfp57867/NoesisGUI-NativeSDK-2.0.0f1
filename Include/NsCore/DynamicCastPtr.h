////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_DYNAMICCASTPTR_H__
#define __CORE_DYNAMICCASTPTR_H__


#include <Noesis.h>
#include <NsCore/PtrForward.h>


/// Cast between types using RTTI extracted from reflection types
template<class CastT, class SourceT>
CastT NsDynamicCast(const Noesis::Core::Ptr<SourceT>& ptr);

/// Performs a DynamicCast only in Debug
template<class CastT, class SourceT>
CastT NsStaticCast(const Noesis::Core::Ptr<SourceT>& ptr);


#include <NsCore/DynamicCastPtr.inl>


#endif
