////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DATATEMPLATESELECTOR_H__
#define __GUI_DATATEMPLATESELECTOR_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IUITreeNode.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class DataTemplate;
class DependencyObject;
//@}

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides a way to choose a DataTemplate based on the data object and the data-bound element.
///
/// https://msdn.microsoft.com/en-us/library/system.windows.controls.datatemplateselector.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DataTemplateSelector: public Core::BaseComponent, public IUITreeNode
{
public:
    DataTemplateSelector();
    virtual ~DataTemplateSelector() = 0;

    /// When overridden in a derived class, returns a DataTemplate based on custom logic
    virtual DataTemplate* SelectTemplate(Core::BaseComponent* item,
        DependencyObject* container) = 0;

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const override;
    void SetNodeParent(IUITreeNode* parent) override;
    Core::BaseComponent* FindNodeResource(IResourceKey* key,
        NsBool fullElementSearch) const override;
    Core::BaseComponent* FindNodeName(const NsChar* name) const override;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

private:
    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(DataTemplateSelector, Core::BaseComponent)
};

NS_WARNING_POP
}
}


#endif
