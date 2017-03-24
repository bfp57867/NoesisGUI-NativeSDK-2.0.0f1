////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_PAGE__
#define __GUI_PAGE__


#include <Noesis.h>
#include <NsCore/Ptr.h>
#include <NsGui/CoreApi.h>
#include <NsGui/UserControl.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Encapsulates a page of content.
///
///http://msdn.microsoft.com/en-us/library/system.windows.controls.page.aspx
class NS_GUI_CORE_API Page: public UserControl
{
public:
    Page();
    ~Page();

    /// Gets or sets page title
    //@{
    const NsChar* GetTitle() const;
    void SetTitle(const NsChar* title);
    //@}

private:
    NsString mTitle;

    NS_DECLARE_REFLECTION(Page, UserControl)
};

NS_WARNING_POP

}
}


#endif
