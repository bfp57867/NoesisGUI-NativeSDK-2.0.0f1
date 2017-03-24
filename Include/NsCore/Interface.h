////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_INTERFACE_H__
#define __CORE_INTERFACE_H__


#include <NsCore/Types.h>
#include <NsCore/ReflectionImplementEmpty.h>
#include <NsCore/CompilerSettings.h>


NS_CFORWARD(Core, TypeClass)
NS_CFORWARD(Core, BaseObject)


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Interface. Used as base for all component interfaces.
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SWIG
NS_INTERFACE Interface
{
    virtual ~Interface() = 0;

    /// Gets the class type information
    virtual const TypeClass* GetClassType() const = 0;

    /// Returns a pointer to the BaseObject implementing this interface
    virtual BaseObject* GetBaseObject() const = 0;

    // Increments reference count and returns the new value
    virtual NsInt32 AddReference() const = 0;

    /// Decrements reference count and returns the new value
    virtual NsInt32 Release() const = 0;

    /// Gets current reference count for the object
    virtual NsInt32 GetNumReferences() const = 0;

    NS_IMPLEMENT_INLINE_STATIC_REFLECTION_(Interface, NoParent)
};

inline Interface::~Interface() {}

// Helper macro to be inserted in classes that implement one or more interfaces
#define NS_IMPLEMENT_INTERFACE_FIXUP \
    Noesis::Core::BaseObject* GetBaseObject() const override \
    { return (Noesis::Core::BaseObject*)this; } \
    NsInt32 AddReference() const override { return InternalAddReference(); } \
    NsInt32 Release() const override { return InternalRelease(); } \
    NsInt32 GetNumReferences() const override \
    { return Noesis::Core::BaseRefCounted::GetNumReferences(); }

#endif

}
}


#endif
