////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_PACKAGE_H__
#define __CORE_PACKAGE_H__


#include <NsCore/RegisterComponent.h>


NS_MSVC_WARNING_DISABLE(4100)


////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_REGISTER_REFLECTION(module, package) \
    void NsRegisterReflection##module##package( \
    Noesis::Core::ComponentFactory* factory, NsBool registerComponents) \

////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_REGISTER_COMPONENT(componentClass) \
    { \
        const Noesis::Core::TypeClass* type = Noesis::Core::TypeOf<componentClass>(); \
        if (registerComponents) \
        { \
            Noesis::Core::RegisterComponent(type, NsComponentCreator<componentClass>); \
        } \
        else \
        { \
            Noesis::Core::UnregisterComponent(type); \
        } \
    }

////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NS_TESTS_ENABLED
    #define NS_REGISTER_TEST(n) \
        extern void Noesis_Register##n##Test(NsBool doRegister); \
        Noesis_Register##n##Test(registerComponents);
#else
    #define NS_REGISTER_TEST(n)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_INIT_PACKAGE(module, package) \
    void NsInitPackage##module##package()

////////////////////////////////////////////////////////////////////////////////////////////////////
#define NS_SHUTDOWN_PACKAGE(module, package) \
    void NsShutdownPackage##module##package()

#endif
