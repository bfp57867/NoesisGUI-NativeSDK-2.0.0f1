////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsCore/MemProfiler.h>
#include <NsCore/StringUtils.h>
#include <NsGui/BoxingUtils.h>
#include <NsGui/DependencyPropertyImpl.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyData::RegisterProperty(const DependencyProperty*& dp, const NsChar* name,
    const Ptr<PropertyMetadata>& metadata)
{
    DependencyProperty::ValidateValueDelegate validate;
    RegisterProperty<T>(dp, name, metadata, PropertyAccess_ReadWrite, validate);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyData::RegisterPropertyRO(const DependencyProperty*& dp, const NsChar* name,
    const Ptr<PropertyMetadata>& metadata)
{
    DependencyProperty::ValidateValueDelegate validate;
    RegisterProperty<T>(dp, name, metadata, PropertyAccess_ReadOnly, validate);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyData::RegisterProperty(const DependencyProperty*& dp, const NsChar* name,
    const Ptr<PropertyMetadata>& metadata, 
    const DependencyProperty::ValidateValueDelegate& validate)
{
    RegisterProperty<T>(dp, name, metadata, PropertyAccess_ReadWrite, validate);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyData::RegisterPropertyRO(const DependencyProperty*& dp, const NsChar* name,
    const Ptr<PropertyMetadata>& metadata,
    const DependencyProperty::ValidateValueDelegate& validate)
{
    RegisterProperty<T>(dp, name, metadata, PropertyAccess_ReadOnly, validate);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyData::RegisterProperty(const DependencyProperty*& dp, const NsChar* name,
    const Ptr<PropertyMetadata>& metadata, PropertyAccess access, 
    const DependencyProperty::ValidateValueDelegate& validate)
{
    NS_PROFILE_MEM("Gui/DependencyProperty");

    /// Force creation of T type and related properties
    Core::TypeOf<T>();

    if (metadata == 0)
    {
        NS_ERROR("Can't register dependency property, metadata is null");
        return;
    }
    if (!metadata->HasDefaultValue())
    {
        NS_ERROR("Can't register dependency property, metadata doesn't have a default value");
        return;
    }
    if (!CheckMetadata<T>(metadata.GetPtr()))
    {
        NS_ERROR("Can't register dependency property, invalid metadata default value type");
        return;
    }

    if (dp != 0)
    {
        NS_ASSERT(CheckPropertyType<T>(dp, Core::Int2Type<Core::IsPtr<T>::Result>()));
        RegisterExistingProperty(dp, name, metadata, access, validate);
    }
    else
    {
        Ptr<DependencyProperty> prop = CreateProperty<T>(name, metadata, access, validate,
            Core::Int2Type<Core::IsPtr<T>::Result>());
        dp = InsertProperty(prop.GetPtr());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyData::AddOwner(const DependencyProperty*& dp, const NsChar* name,
    const DependencyProperty*& source, const Ptr<PropertyMetadata>& metadata)
{
    NS_PROFILE_MEM("Gui/DependencyProperty");

    /// Force creation of T type and related properties
    Core::TypeOf<T>();

    NS_ASSERT(!Core::String::IsNullOrEmpty(name));

    if (dp != 0)
    {
        NS_ASSERT(dp->GetName() == NsSymbol(name));
        NS_ASSERT(CheckPropertyType<T>(dp, Core::Int2Type<Core::IsPtr<T>::Result>()));
    }

    if (source != 0)
    {
        NS_ASSERT(!Core::String::IsNullOrEmpty(name));
        NS_ASSERT(source->GetName() == NsSymbol(name));
        NS_ASSERT(CheckPropertyType<T>(source, Core::Int2Type<Core::IsPtr<T>::Result>()));
        dp = InsertProperty(source);
    }
    else
    {
        // Ensure insertion because the property could had been created in a previous call to
        // OverrideMetadata but not registered in the owner DependencyData
        if (dp != 0)
        {
            InsertProperty(dp);
        }
        else
        {
            Ptr<DependencyProperty> prop = CreateProperty<T>(name,
                Core::Int2Type<Core::IsPtr<T>::Result>());
            dp = InsertProperty(prop.GetPtr());
        }
        source = dp;
    }

    if (dp != 0 && metadata != 0)
    {
        NS_ASSERT(!metadata->HasDefaultValue() || CheckMetadata<T>(metadata.GetPtr()));
        const_cast<DependencyProperty*>(dp)->AddMetadata(mOwnerType, metadata.GetPtr());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
void DependencyData::OverrideMetadata(const DependencyProperty*& dp, const NsChar* name,
    const Ptr<PropertyMetadata>& metadata)
{
    NS_PROFILE_MEM("Gui/DependencyProperty");

    if (metadata == 0)
    {
        NS_ERROR("Metadata is null");
        return;
    }

    /// Force creation of T type and related properties
    Core::TypeOf<T>();

    if (dp != 0)
    {
        NS_ASSERT(!Core::String::IsNullOrEmpty(name));
        NS_ASSERT(dp->GetName() == NsSymbol(name));
        NS_ASSERT(CheckPropertyType<T>(dp, Core::Int2Type<Core::IsPtr<T>::Result>()));
    }
    else
    {
        Ptr<DependencyProperty> prop = CreateProperty<T>(name,
            Core::Int2Type<Core::IsPtr<T>::Result>());
        dp = InsertProperty(prop.GetPtr());
    }

    if (dp != 0)
    {
        NS_ASSERT(!metadata->HasDefaultValue() || CheckMetadata<T>(metadata.GetPtr()));
        const_cast<DependencyProperty*>(dp)->AddMetadata(mOwnerType, metadata.GetPtr());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<DependencyProperty> DependencyData::CreateProperty(const NsChar* name,
    const Ptr<PropertyMetadata>& metadata, PropertyAccess access,
    const DependencyProperty::ValidateValueDelegate& validate, IsNotBaseComponent)
{
    return *new DependencyPropertyImpl<T>(NsSymbol(name), mOwnerType, metadata, validate, access);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<DependencyProperty> DependencyData::CreateProperty(const NsChar* name,
    const Ptr<PropertyMetadata>& metadata, PropertyAccess access,
    const DependencyProperty::ValidateValueDelegate& validate, IsBaseComponent)
{
    return *new DependencyPropertyImpl<Ptr<BaseComponent> >(NsSymbol(name),
        Core::TypeOf<typename T::Type>(), sizeof(Ptr<BaseComponent>), mOwnerType,
        metadata, validate, access);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<DependencyProperty> DependencyData::CreateProperty(const NsChar* name, IsNotBaseComponent)
{
    return *new DependencyPropertyImpl<T>(NsSymbol(name));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
Ptr<DependencyProperty> DependencyData::CreateProperty(const NsChar* name, IsBaseComponent)
{
    return *new DependencyPropertyImpl<Ptr<BaseComponent> >(NsSymbol(name),
        Core::TypeOf<typename T::Type>(), sizeof(Ptr<BaseComponent>));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool DependencyData::CheckPropertyType(const DependencyProperty* dp, IsNotBaseComponent)
{
#if NS_ASSERTS_ENABLED
    return dp->GetClassType() == Core::TypeOf<DependencyPropertyImpl<T> >() &&
        dp->GetType() == Core::TypeOf<T>();
#else
    NS_UNUSED(dp);
    NS_ASSERT_UNREACHABLE;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool DependencyData::CheckPropertyType(const DependencyProperty* dp, IsBaseComponent)
{
#if NS_ASSERTS_ENABLED
    typedef typename T::Type TT;
    static_assert(!Core::IsInterface<TT>::Result, "Interface not supported in DPs");
    return dp->GetClassType() == Core::TypeOf<DependencyPropertyImpl<Ptr<BaseComponent> > >() &&
        (dp->GetType() == Core::TypeOf<TT>() || Core::IsSame<TT, Core::BaseComponent>::Result);
#else
    NS_UNUSED(dp);
    NS_ASSERT_UNREACHABLE;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
NsBool DependencyData::CheckMetadata(PropertyMetadata* metadata) const
{
    typedef typename Core::IsPtr<T>::PointedType TT;
    return BoxingUtils::CheckType<T>(metadata->GetDefaultValue(), Core::TypeOf<TT>()) ||
        Core::IsSame<TT, Core::BaseComponent>::Result;
}

}
}
