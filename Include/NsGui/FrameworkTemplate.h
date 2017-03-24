////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FRAMEWORKTEMPLATE_H__
#define __GUI_FRAMEWORKTEMPLATE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>
#include <NsCore/Delegate.h>
#include <NsGui/CoreApi.h>
#include <NsGui/INameScope.h>
#include <NsGui/ISealable.h>
#include <NsGui/IUITreeNode.h>


NS_CFORWARD(Gui, Visual)
NS_CFORWARD(Gui, FrameworkElement)
NS_CFORWARD(Gui, NameScope)
NS_CFORWARD(Gui, ResourceDictionary)
NS_CFORWARD(Gui, BaseTrigger)


namespace Noesis
{
namespace Gui
{

template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseTrigger> TriggerCollection;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Enables the instantiation of a tree of elements for a template.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.frameworktemplate.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API FrameworkTemplate: public Core::BaseComponent,public INameScope,
    public ISealable, public IUITreeNode
{
public:
    NS_DISABLE_COPY(FrameworkTemplate)

    FrameworkTemplate();
    virtual ~FrameworkTemplate() = 0;

    /// Applies current template to the element specified
    Ptr<FrameworkElement> Apply(FrameworkElement* templatedParent,
        BaseComponent* dataContext) const;

    /// Gets or sets the collection of resources that can be used within the scope of 
    /// this template.
    //@{
    ResourceDictionary* GetResources() const;
    void SetResources(ResourceDictionary* resources);
    //@}

    /// Gets or sets the root node of the template.
    //@{
    Visual* GetVisualTree() const;
    void SetVisualTree(Visual* root);
    //@}

    /// Finds the element associated with the specified name defined within this template
    Core::BaseComponent* FindName(const NsChar* name, FrameworkElement* templatedParent);

    /// Gets template triggers if available
    virtual TriggerCollection* GetAvailableTriggers() const;

    /// From INameScope
    //@{
    Core::BaseComponent* FindName(const NsChar* name) const final;
    void RegisterName(const NsChar* name, Core::BaseComponent* object) final;
    void UnregisterName(const NsChar* name) final;
    void UpdateName(const NsChar* name, Core::BaseComponent* object) final;
    INameScope::ChangedDelegate& NameScopeChanged() final;
    //@}

    /// From ISealable
    //@{
    NsBool CanSeal() const final;
    NsBool IsSealed() const final;
    void Seal() final;
    //@}

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const final;
    void SetNodeParent(IUITreeNode* parent) final;
    Core::BaseComponent* FindNodeResource(IResourceKey* key, NsBool fullElementSearch) const final;
    Core::BaseComponent* FindNodeName(const NsChar* name) const final;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const final;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    virtual NsBool IsValidTemplatedParent(FrameworkElement* templatedParent,
        BaseComponent* dataContext) const;

private:
    void EnumNameScope(const NsChar* name, BaseComponent* object, void* context) const;
    void EnsureNamescope() const;
    void EnsureResources() const;

private:
    friend class DynamicResourceExpression;
    friend class FrameworkElement;

    IUITreeNode* mOwner;

    mutable Ptr<NameScope> mNameScope;
    mutable Ptr<ResourceDictionary> mResources;
    Ptr<Visual> mVisualTree;

    NsBool mIsSealed;

    NS_DECLARE_REFLECTION(FrameworkTemplate, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif
