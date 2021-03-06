////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ROWDEFINITION_H__
#define __GUI_ROWDEFINITION_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/BaseDefinition.h>


namespace Noesis
{
namespace Gui
{

// Forward declaration
class GridLength;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines row-specific properties that apply to Grid elements.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.rowdefinition.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API RowDefinition: public BaseDefinition
{
public:
    /// Constructor
    RowDefinition();

    /// Gets or sets column height
    /// \remarks Positive values indicates pixel units
    ///          Negative values indicates percentage of available space (where -1.0 is 100%)
    //@{
    const GridLength& GetHeight() const;
    void SetHeight(const GridLength& height);
    //@}

    /// Gets or sets column minimum height
    //@{
    NsFloat32 GetMinHeight() const;
    void SetMinHeight(NsFloat32 minHeight);
    //@}

    /// Gets or sets column maximum height
    //@{
    NsFloat32 GetMaxHeight() const;
    void SetMaxHeight(NsFloat32 maxHeight);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* HeightProperty;
    static const DependencyProperty* MinHeightProperty;
    static const DependencyProperty* MaxHeightProperty;
    //@}

private:
    NS_DECLARE_REFLECTION(RowDefinition, BaseDefinition)
};

}
}

#endif
