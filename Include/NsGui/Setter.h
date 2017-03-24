////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SETTER_H__
#define __GUI_SETTER_H__


#include <Noesis.h>
#include <NsGui/BaseSetter.h>
#include <NsCore/String.h>
#include <NsCore/Ptr.h>


NS_CFORWARD(Gui, DependencyProperty)


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a setter that applies a property value.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.setter.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Setter: public BaseSetter
{
public:
    /// Constructor
    Setter();

    /// Gets or sets the name of the target element
    //@{
    const NsChar* GetTargetName() const;
    void SetTargetName(const NsChar* targetName);
    //@}

    /// Gets or sets property
    //@{
    const DependencyProperty* GetProperty() const;
    void SetProperty(const DependencyProperty* property);
    //@}

    /// Gets or sets value
    //@{
    Core::BaseComponent* GetValue() const;
    void SetValue(Core::BaseComponent* value);
    //@}

    /// From BaseSetter
    //@{
    void Seal(NsBool allowTargetName) override;
    //@}

private:
    NsString mTargetName;
    const DependencyProperty* mProperty;
    Ptr<Core::BaseComponent> mValue;

    NS_DECLARE_REFLECTION(Setter, BaseSetter)
};

NS_WARNING_POP

}
}

#endif
