////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TOOLBARTRAY_H__
#define __GUI_TOOLBARTRAY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/FrameworkElement.h>
#include <NsGui/Enums.h>


namespace Noesis
{
namespace Gui
{

/// Forward declarations
//@{
class Brush;
//@}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the container that handles the layout of a ToolBar. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.toolbartray.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ToolBarTray: public FrameworkElement
{
public:
    ToolBarTray();
    ~ToolBarTray();

    /// Gets a value that indicates whether a ToolBar can be moved inside a ToolBarTray
    static NsBool GetIsLocked(const DependencyObject* element);

    /// Sets a value that indicates whether a ToolBar can be moved inside a ToolBarTray
    static void SetIsLocked(DependencyObject* element, NsBool isLocked);

    /// Gets or sets a brush to use for the background color of the ToolBarTray
    //@{
    Brush* GetBackground() const;
    void SetBackground(Brush* brush);
    //@}

    /// Gets or sets a value that indicates whether the ToolBarTray overflow area is currently visible.
    //@{
    Orientation GetOrientation() const;
    void SetOrientation(Orientation orientation);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* BackgroundProperty;
    static const DependencyProperty* IsLockedProperty; // Attached property
    static const DependencyProperty* OrientationProperty;
    //@}

    NS_DECLARE_REFLECTION(ToolBarTray, FrameworkElement)
};

}
}


#endif
