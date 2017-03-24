////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #620]
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/DynamicCastPointer.h>
#include <NsCore/Ptr.h>
#include <NsCore/CompilerTools.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CastT, class SourceT>
CastT NsDynamicCast(const Noesis::Core::Ptr<SourceT>& ptr)
{
    static_assert(Noesis::Core::IsPtr<CastT>::Result, "Ptr can only be casted to Ptr");
    return CastT(NsDynamicCast<typename CastT::Type*>(ptr.GetPtr()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class CastT, class SourceT>
CastT NsStaticCast(const Noesis::Core::Ptr<SourceT>& ptr)
{
    static_assert(Noesis::Core::IsPtr<CastT>::Result, "Ptr can only be casted to Ptr");
    return CastT(NsStaticCast<typename CastT::Type*>(ptr.GetPtr()));
}
