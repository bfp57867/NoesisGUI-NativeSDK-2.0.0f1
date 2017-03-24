////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_TYPECLASSCREATOR_H__
#define __CORE_TYPECLASSCREATOR_H__


#include <Noesis.h>
#include <NsCore/CompilerTools.h>


NS_CFORWARD(Core, Type)
NS_CFORWARD(Core, TypeClassBuilder)
NS_CFORWARD(Core, TypeInfo)
NS_CFORWARD(Core, TypeProperty)
NS_CFORWARD(Core, TypeMetaData)
NS_CFORWARD(Core, Symbol)


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Class, class Parent> NsSize CalculateParentOffset()
{
    static_assert((IsDerived<Class, Parent>::Result), "class must inherit from parent");

    // First we define a pointer to the Class, then we cast to the Parent class, and finally we
    // calculate the offset from the Class pointer to the Parent class pointer
    Class* ptr = reinterpret_cast<Class*>(-1);
    NsByte* classPtr = reinterpret_cast<NsByte*>(ptr);
    NsByte* parentPtr = reinterpret_cast<NsByte*>(static_cast<Parent*>(ptr));

    return static_cast<NsSize>(parentPtr - classPtr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// TypeClassCreator implements helper functions for building types using Noesis reflection macros.
///
///  NS_IMPLEMENT_REFLECTION(Square)
///  {
///    NsMeta<Desc>("Defines a square shape that can be drawn");
///    NsMeta<Tag>("Visual");
///    NsImpl<IShape>();
///    NsProp("side", &Square::mSide)
///        .Meta<Desc>("Length of the square side")
///        .Meta<Tag>("Editable");
///  }
///
////////////////////////////////////////////////////////////////////////////////////////////////////
class TypeClassCreator
{
public:
    /// Constructor
    inline TypeClassCreator(TypeClassBuilder* typeClass);

    /// Creates a TypeClass for the specified class
    template<class ClassT> 
    static Type* Create(const TypeInfo& typeInfo);

    /// Fills TypeClass with members of the class
    template<class ClassT, class BaseT> 
    static void Fill(Type* type);

    /// Adds meta data to the type class
    template<class T, class ...Args>
    Ptr<T> Meta(Args... args);

    /// Specifies that the class implements the interface T
    template<class ClassT, class T>
    void Impl();

    /// Helper returned to add metadata to properties
    struct TypePropertyCreator
    {
        NS_FORCEINLINE TypePropertyCreator(TypeProperty* typeProperty);
        template<class T, class ...Args> NS_FORCEINLINE TypePropertyCreator& Meta(Args... args);

        TypeProperty* mTypeProperty;
    };

    /// Adds a property to the type class
    //@{
    template<class ClassT, class T>
    TypePropertyCreator Prop(const NsChar* name, T ClassT::* prop);

    template<class ClassT, class T, NsInt N>
    TypePropertyCreator Prop(const NsChar* name, T (ClassT::* prop)[N]);

    template<class ClassT, class T, NsInt N>
    TypePropertyCreator Prop(const NsChar* name, T (ClassT::* prop)[N], NsSize index);

    template<class T>
    TypePropertyCreator Prop(const NsChar* name, NsSize offset);

    template<class ClassT, class T>
    TypePropertyCreator Prop(const NsChar* name, T (ClassT::*getter)() const);

    template<class ClassT, class T>
    TypePropertyCreator Prop(const NsChar* name, T (ClassT::*getter)() const,
        void (ClassT::*setter)(T));
    //@}

    /// Adds a event to the type class
    inline void Event(const NsChar* name);

private:
    /// Adds base parent to the type class (only if T is different of NoParent)
    //@{
    template<class ClassT, class T>
    void Base(Int2Type<0>);

    template<class ClassT, class T>
    void Base(Int2Type<1>);
    //@}

private:
    TypeClassBuilder* mTypeClass;
};

}
}


#include <NsCore/TypeClassCreator.inl>


#endif
