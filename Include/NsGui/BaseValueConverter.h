////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASEVALUECONVERTER_H__
#define __GUI_BASEVALUECONVERTER_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IValueConverter.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for converters
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseValueConverter: public Core::BaseComponent, public IValueConverter
{
public:
    NS_DISABLE_COPY(BaseValueConverter)

    BaseValueConverter();
    virtual ~BaseValueConverter() = 0;

    /// From IValueConverter
    //@{
    NsBool TryConvert(Core::BaseComponent* value, const Core::Type* targetType,
        Core::BaseComponent* parameter, Ptr<Core::BaseComponent>& result) override;
    NsBool TryConvertBack(Core::BaseComponent* value, const Core::Type* targetType,
        Core::BaseComponent* parameter, Ptr<Core::BaseComponent>& result) override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

private:
    NS_DECLARE_REFLECTION(BaseValueConverter, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif
