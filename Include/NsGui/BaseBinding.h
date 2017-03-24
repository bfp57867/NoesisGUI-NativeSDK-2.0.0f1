////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #952]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASEBINDING_H__
#define __GUI_BASEBINDING_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/String.h>
#include <NsCore/Ptr.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IMarkupExtension.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines the common features for Binding.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.data.bindingbase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseBinding: public Core::BaseComponent, public IMarkupExtension
{
public:
    NS_DISABLE_COPY(BaseBinding)

    BaseBinding();
    virtual ~BaseBinding() = 0;

    /// Gets or sets the value to use when the binding is unable to return a value
    //@{
    Core::BaseComponent* GetFallbackValue() const;
    void SetFallbackValue(Core::BaseComponent* value);
    //@}

    /// Gets or sets a string that specifies how to format the binding if it displays the bound 
    /// value as a string.
    ///
    /// Examples:
    ///
    /// .. code-block:: xml
    ///
    ///     <TextBlock Text="{Binding Amount, StringFormat=F2}" />
    ///     <TextBlock Text="{Binding Amount, StringFormat={}{0:F2}}" />
    ///     <TextBlock Text="{Binding Amount, StringFormat=Value is {0:F2} units}" />
    ///
    //@{
    const NsChar* GetStringFormat() const;
    void SetStringFormat(const NsChar* format);
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    NsBool CheckSealed() const;

protected:
    /// Indicates if this binding is unmodifiable. The binding becomes sealed the first time a
    /// binding expression is generated
    NsBool mSealed;

private:
    /// Fallback value to return when the binding cannot be resolved
    Ptr<Core::BaseComponent> mFallbackValue;
    NsString mStringFormat;

    NS_DECLARE_REFLECTION(BaseBinding, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif
