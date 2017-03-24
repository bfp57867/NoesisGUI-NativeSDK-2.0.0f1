////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/Symbol.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/Error.h>
#include <NsCore/Ptr.h>
#include <NsCore/TypeOfForward.h>
#include <NsCore/TypePropertyImpl.h>
#include <NsCore/TypeClass.h>


namespace Noesis
{
namespace Core
{

////////////////////////////////////////////////////////////////////////////////////////////////////
TypeClassCreator::TypeClassCreator(TypeClassBuilder* typeClass): mTypeClass(typeClass)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT>
Type* TypeClassCreator::Create(const TypeInfo& typeInfo)
{
    return new TypeClass(typeInfo, IsInterface<ClassT>::Result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class BaseT> 
void TypeClassCreator::Fill(Type* type)
{
    TypeClassCreator helper((TypeClassBuilder*)(type));
    helper.Base<ClassT, BaseT>(Int2Type<IsSame<BaseT, NoParent>::Result>());

    ClassT::template StaticFillClassType<void>(helper);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class ...Args>
Ptr<T> TypeClassCreator::Meta(Args... args)
{
    Ptr<T> metaData = *new T(args...);
    mTypeClass->GetMetaData().Add(metaData.GetPtr());
    return metaData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
void TypeClassCreator::Impl()
{
    enum { isDerived = IsDerived<ClassT, T>::Result };
    static_assert(isDerived, "class does not implement specified interface");
    static_assert(IsInterface<T>::Result, "NsImpl used with non interface class");

    NsSize offset = CalculateParentOffset<ClassT, T>();
    mTypeClass->AddInterface(T::StaticGetClassType((T2T<T>*)0), offset);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T> NsSize OffsetOf(T ClassT::* prop)
{
    return (NsSize)((ptrdiff_t)&reinterpret_cast<const volatile char&>((((ClassT *)0)->*prop)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    T ClassT::* prop)
{
    NsSize offset = OffsetOf(prop);
    TypeProperty* typeProperty = new TypePropertyOffset<T>(NsSymbol(name), offset);
    mTypeClass->AddProperty(typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T, NsInt N>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    T (ClassT::* prop)[N])
{
    NsSize offset = OffsetOf(prop);
    TypeProperty* typeProperty = new TypePropertyArray<T, N>(NsSymbol(name), offset);
    mTypeClass->AddProperty(typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T, NsInt N>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    T (ClassT::* prop)[N], NsSize index)
{
    NS_ASSERT(index < N);
    
    NsSize offset = OffsetOf(prop) + (index * sizeof(T));
    TypeProperty* typeProperty = new TypePropertyOffset<T>(NsSymbol(name), offset);
    mTypeClass->AddProperty(typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    NsSize offset)
{
    TypeProperty* typeProperty = new TypePropertyOffset<T>(NsSymbol(name), offset);
    mTypeClass->AddProperty(typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    T (ClassT::*getter)() const)
{
    typedef typename IsConst<typename IsReference<T>::NonReferenceType>::NonConstType Type;
    TypeProperty* typeProperty = new TypePropertyFunction<ClassT, Type>(NsSymbol(name), getter, 0);
    mTypeClass->AddProperty(typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
typename TypeClassCreator::TypePropertyCreator TypeClassCreator::Prop(const NsChar* name,
    T (ClassT::*getter)() const, void (ClassT::*setter)(T))
{
    typedef typename IsConst<typename IsReference<T>::NonReferenceType>::NonConstType Type;
    TypeProperty* typeProperty = new TypePropertyFunction<ClassT, Type>(NsSymbol(name), getter,
        setter);
    mTypeClass->AddProperty(typeProperty);

    return TypePropertyCreator(typeProperty);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TypeClassCreator::Event(const NsChar* name)
{
    mTypeClass->AddEvent(NsSymbol(name));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
void TypeClassCreator::Base(Int2Type<0>)
{
    enum { isDerived = IsDerived<ClassT, T>::Result };
    static_assert(isDerived, "class does not derive from specified base");

    mTypeClass->AddBase(TypeOf<T>());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class ClassT, class T>
void TypeClassCreator::Base(Int2Type<1>)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
TypeClassCreator::TypePropertyCreator::TypePropertyCreator(TypeProperty* typeProperty):
    mTypeProperty(typeProperty)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class ...Args>
typename TypeClassCreator::TypePropertyCreator&
TypeClassCreator::TypePropertyCreator::Meta(Args... args)
{
    Ptr<T> meta = *new T(args...);
    mTypeProperty->GetMetaData().Add(meta.GetPtr());
    return *this;
}

}
}
