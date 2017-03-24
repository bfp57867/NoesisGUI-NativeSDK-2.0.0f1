////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CORE_BASECONVERTER_H__
#define __CORE_BASECONVERTER_H__


#include <Noesis.h>
#include <NsCore/TypeConverterApi.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ITypeConverter.h>


namespace Noesis
{
namespace Core
{

class BoxedValue;


NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for converters
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_TYPECONVERTER_API BaseConverter: public BaseComponent, public ITypeConverter
{
public:
    /// From ITypeConverter
    //@{
    Ptr<BaseComponent> ConvertFrom(BaseComponent* object) const override;
    Ptr<BaseComponent> ConvertFromString(const NsChar* str) const override;
    Ptr<BaseComponent> ConvertTo(BaseComponent* object, const Type* type) const override;
    NsString ConvertToString(BaseComponent* object) const override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

    NS_DECLARE_REFLECTION(BaseConverter, BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for converters that need conversion from string
/// Inheritors must implement TryConvertFromString
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_TYPECONVERTER_API BaseConverterOneWay: public BaseConverter
{
public:
    /// From ITypeConverter
    //@{
    NsBool CanConvertFrom(const Type* type) const;
    NsBool CanConvertTo(const Type* type) const;
    NsBool TryConvertFrom(BaseComponent* object, Ptr<BaseComponent>& result) const;
    NsBool TryConvertTo(BaseComponent* object, const Type* type, Ptr<BaseComponent>& result) const;
    NsBool TryConvertToString(BaseComponent* object, NsString& result) const;
    //@}

protected:
    NsBool TryConvertFrom_(BoxedValue* boxed, Ptr<BaseComponent>& result) const;

    NS_DECLARE_REFLECTION(BaseConverterOneWay, BaseConverter)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for converters that need conversion to/from string
/// Inheritors must implement TryConvertFromString and TryConvertToString
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_CORE_TYPECONVERTER_API BaseConverterBothWays: public BaseConverterOneWay
{
public:
    /// From ITypeConverter
    //@{
    NsBool CanConvertTo(const Type* type) const;
    NsBool TryConvertTo(BaseComponent* object, const Type* type, Ptr<BaseComponent>& result) const;
    //@}

    NS_DECLARE_REFLECTION(BaseConverterBothWays, BaseConverterOneWay)
};

NS_WARNING_POP

}
}

#endif