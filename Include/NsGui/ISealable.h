////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ISEALABLE_H__
#define __GUI_ISEALABLE_H__


#include <Noesis.h>
#include <NsCore/Interface.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// This interface is shared across Freezable, Style and Template. A sealed object is free-threaded.
////////////////////////////////////////////////////////////////////////////////////////////////////
NS_INTERFACE ISealable: public Core::Interface
{
    /// Indicates if the current instance can be sealed
    virtual NsBool CanSeal() const = 0;

    /// Indicates if the current instance is sealed
    virtual NsBool IsSealed() const = 0;

    /// Seals the current instance
    virtual void Seal() = 0;

    NS_IMPLEMENT_INLINE_REFLECTION_(ISealable, Core::Interface)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
inline void SealIfSealable(ISealable* sealable)
{
    if (sealable != 0)
    {
        sealable->Seal();
    }
}

}
}


#endif
