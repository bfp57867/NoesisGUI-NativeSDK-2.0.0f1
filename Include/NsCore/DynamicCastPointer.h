////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_DYNAMICCASTPOINTER_H__
#define __CORE_DYNAMICCASTPOINTER_H__


#include <Noesis.h>


/// Cast between types using RTTI extracted from reflection types
template<class CastT, class SourceT>
CastT NsDynamicCast(SourceT ptr);

/// Performs a DynamicCast only in Debug
template<class CastT, class SourceT>
CastT NsStaticCast(SourceT ptr);


#include <NsCore/DynamicCastPointer.inl>


#endif
