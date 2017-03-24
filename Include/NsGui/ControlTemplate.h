////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONTROLTEMPLATE_H__
#define __GUI_CONTROLTEMPLATE_H__


#include <Noesis.h>
#include <NsGui/FrameworkTemplate.h>


NS_CFORWARD(Gui, ResourceKeyType)
NS_CFORWARD(Gui, Control)


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies the visual structure and behavioral aspects of a Control that can be
/// shared across multiple instances of the control.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.controltemplate.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ControlTemplate: public FrameworkTemplate
{
public:
    ControlTemplate();
    ~ControlTemplate();

    /// Gets or sets the type for which this template is intended
    //@{
    ResourceKeyType* GetTargetType() const;
    void SetTargetType(ResourceKeyType* targetType);
    //@}

    /// Gets a collection of TriggerBase objects that apply property changes or perform actions
    /// based on specified conditions
    TriggerCollection* GetTriggers() const;

protected:
    /// From FrameworkTemplate
    //@{
    NsBool IsValidTemplatedParent(FrameworkElement* templatedParent,
        Core::BaseComponent* dataContext) const override;
    TriggerCollection* GetAvailableTriggers() const final;
    //@}

private:
    void EnsureTriggers() const;

private:
    Ptr<ResourceKeyType> mTargetType;
    mutable Ptr<TriggerCollection> mTriggers;

    NS_DECLARE_REFLECTION(ControlTemplate, FrameworkTemplate)
};

NS_WARNING_POP

}
}

#endif
