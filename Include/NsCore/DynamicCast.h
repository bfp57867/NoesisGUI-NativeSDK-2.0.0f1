////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #620]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_DYNAMICCAST_H__
#define __CORE_DYNAMICCAST_H__


////////////////////////////////////////////////////////////////////////////////////////////////////
/// Functions for dynamic casting between pointers:
///
///    Ptr<Cube> cube = *new Cube();
///    IRenderable* renderable = NsDynamicCast<IRenderable*>(cube.GetPtr());
///
/// There are equivalent funtions for Ptr<> pointers:
///
///    Ptr<Cube> cube = *new Cube();
///    Ptr<IRenderable> renderable = NsDynamicCast< Ptr<IRenderable> >(cube);
///
/// NsStaticCast only performs the dynamic cast in debug configurations
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <Noesis.h>
#include <NsCore/DynamicCastPointer.h>
#include <NsCore/DynamicCastPtr.h>


#endif
