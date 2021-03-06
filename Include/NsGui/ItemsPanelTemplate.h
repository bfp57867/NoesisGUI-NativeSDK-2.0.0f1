////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ITEMSPANELTEMPLATE_H__
#define __GUI_ITEMSPANELTEMPLATE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/FrameworkTemplate.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Specifies the panel that the ItemsPresenter creates for the layout of the items of an 
/// ItemsControl.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.itemspaneltemplate.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ItemsPanelTemplate: public FrameworkTemplate
{
public:
    ItemsPanelTemplate();
    ~ItemsPanelTemplate();

    NS_DECLARE_REFLECTION(ItemsPanelTemplate, FrameworkTemplate)
};

}
}

#endif