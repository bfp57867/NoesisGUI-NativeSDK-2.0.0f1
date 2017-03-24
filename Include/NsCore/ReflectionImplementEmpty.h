////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_REFLECTIONIMPLEMENTEMPTY_H__
#define __CORE_REFLECTIONIMPLEMENTEMPTY_H__


#include <Noesis.h>
#include <NsCore/CompilerTools.h>
#include <NsCore/TypeCreate.h>
#include <NsCore/TypeInfo.h>
#include <NsCore/TypeClassCreatorEmpty.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
/// This type should be used as a null type when a class has no parent.
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Noesis
{
namespace Core
{
typedef NullType NoParent;
template<class T> struct T2T;
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements reflection for a class outside class definition
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_IMPLEMENT_REFLECTION_(classType) \
const Noesis::Core::TypeClass* classType::StaticGetClassType(Noesis::Core::T2T<classType>*)\
{\
    static const Noesis::Core::TypeClass* type;\
\
    if (type == 0)\
    {\
        type = (const Noesis::Core::TypeClass*)(Noesis::Core::TypeCreate::Create(\
            NS_TYPEID(classType),\
            Noesis::Core::TypeClassCreatorEmpty<SelfClass, ParentClass>::Create,\
            Noesis::Core::TypeClassCreatorEmpty<SelfClass, ParentClass>::Fill));\
    }\
\
    return type;\
}\
\
const Noesis::Core::TypeClass* classType::GetClassType() const\
{\
    return StaticGetClassType();\
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements static reflection functions for a class inside class definition
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_IMPLEMENT_INLINE_STATIC_REFLECTION_(classType, parentType) \
public:\
    static const Noesis::Core::TypeClass* StaticGetClassType(Noesis::Core::T2T<classType>* = 0)\
    {\
        static const Noesis::Core::TypeClass* type;\
\
        if (type == 0)\
        {\
            type = (const Noesis::Core::TypeClass*)(Noesis::Core::TypeCreate::Create(\
                NS_TYPEID(classType),\
                Noesis::Core::TypeClassCreatorEmpty<SelfClass, ParentClass>::Create,\
                Noesis::Core::TypeClassCreatorEmpty<SelfClass, ParentClass>::Fill));\
        }\
\
        return type;\
    }\
\
private:\
    typedef classType SelfClass;\
    typedef parentType ParentClass;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Implements reflection for a class inside class definition (templates must use this one)
////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_IMPLEMENT_INLINE_REFLECTION_(classType, parentType) \
public:\
    NS_WARNING_PUSH \
    NS_CLANG_WARNING_DISABLE("-Winconsistent-missing-override") \
        const Noesis::Core::TypeClass* GetClassType() const\
        {\
            return StaticGetClassType();\
        } \
    NS_WARNING_POP \
    NS_IMPLEMENT_INLINE_STATIC_REFLECTION_(classType, parentType)

#endif
