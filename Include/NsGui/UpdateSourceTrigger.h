////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_UPDATESOURCETRIGGER_H__
#define __GUI_UPDATESOURCETRIGGER_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclareEnum.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes the timing of binding source updates
////////////////////////////////////////////////////////////////////////////////////////////////////
enum UpdateSourceTrigger
{
    /// The default UpdateSourceTrigger value of the binding target property. The default value for 
    /// most dependency properties is PropertyChanged, while the Text property has a default value 
    /// of LostFocus. 
    UpdateSourceTrigger_Default,
    /// Updates the binding source immediately whenever the binding target property changes
    UpdateSourceTrigger_PropertyChanged,
    /// Updates the binding source whenever the binding target element loses focus
    UpdateSourceTrigger_LostFocus,
    /// Updates the binding source only when you call the UpdateSource method
    UpdateSourceTrigger_Explicit
};

}
}

NS_DECLARE_ENUM(NS_GUI_CORE_API, Noesis::Gui::UpdateSourceTrigger)


#endif