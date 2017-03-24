////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPECLASSBUILDER_H__
#define __CORE_TYPECLASSBUILDER_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/TypeClass.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeClassBuilder. Fills type class with reflection info: constructors, functions, properties...
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TypeClassBuilder: public TypeClass
{
public:
    /// Constructor
    TypeClassBuilder(const TypeInfo& typeInfo, NsBool isInterface);

    /// Adds a type as the base of this class
    void AddBase(const TypeClass* baseType);

    /// Adds an interface to the type class. Provide offset applied to an instance of this type to
    /// convert it to an instance of the interface's type
    void AddInterface(const TypeClass* interfaceType, NsSize offset);

    /// Adds a property to the type class
    void AddProperty(TypeProperty* prop);

    /// Adds an event to the type class
    void AddEvent(NsSymbol event);

private:
    NS_DECLARE_REFLECTION(TypeClassBuilder, TypeClass)
};

}
}


#endif
