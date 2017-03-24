////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #473]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPECLASS_H__
#define __CORE_TYPECLASS_H__


#include <Noesis.h>
#include <NsCore/KernelApi.h>
#include <NsCore/TypeMeta.h>
#include <NsCore/Symbol.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Vector.h>


NS_CFORWARD(Core, TypeProperty)


namespace Noesis
{
namespace Core
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeClass. Defines reflection info for structs and classes.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_KERNEL_API TypeClass: public TypeMeta
{
public:
    /// Constructor
    TypeClass(const TypeInfo& typeInfo, NsBool isInterface);

    /// Destructor
    ~TypeClass();

    /// Defines ancestor information
    struct AncestorInfo
    {
        /// reflection type of ancestor class
        const TypeClass* type;

        /// offset from the implementation class pointer to the ancestor
        NsSize offset;

        /// Constructor
        AncestorInfo(const TypeClass* t, NsSize o): type(t), offset(o) { }
    };

    /// Gets base implementation class type
    const TypeClass* GetBase() const;

    /// Gets number of interfaces this class implements
    NsSize GetNumInterfaces() const;

    /// Gets info about an interface implemented by this class
    const AncestorInfo* GetInterface(NsSize index) const;

    /// Tells if this type represents an interface
    NsBool IsInterface() const;

    /// Determines if this class is a descendant of the specified type.
    NsBool IsDescendantOf(const TypeClass* ancestorType,
        const AncestorInfo** ancestorInfo = 0) const;

    /// Gets number of properties of this class reflection type
    NsSize GetNumProperties() const;

    /// Gets a property of the reflection type
    const TypeProperty* GetProperty(NsSize index) const;

    /// Looks for a property given its name. If this class type has the property requested then it
    /// returns the property, else it returns a null pointer.
    const TypeProperty* FindProperty(NsSymbol name) const;

    /// Gets number of events of this class reflection type
    NsSize GetNumEvents() const;

    /// Gets an event of the reflection type
    NsSymbol GetEvent(NsSize index) const;

    /// Indicates if this class type has the specified event
    NsBool FindEvent(NsSymbol name) const;

protected:
    NsBool mIsInterface;

    // Implementation base class
    const TypeClass* mBase;

    // List of interfaces implemented by this class
    typedef NsVector<AncestorInfo> AncestorVector;
    AncestorVector mInterfaces;

    typedef NsVector<TypeProperty*> PropertyVector;
    PropertyVector mProperties;

    typedef NsVector<NsSymbol> EventVector;
    EventVector mEvents;

private:
    void CollapseAncestors() const;
    void CollapseAncestors(const TypeClass* ancestorType, NsSize offset) const;
    void InsertAncestor(const TypeClass* ancestorType, NsSize offset) const;

private:
    // All ancestors collapsed in a unique list to speed up dynamic cast searches
    struct Ancestors;
    Ancestors* mAncestors;

    NS_DECLARE_REFLECTION(TypeClass, TypeMeta)
};

NS_WARNING_POP

}
}


#endif
