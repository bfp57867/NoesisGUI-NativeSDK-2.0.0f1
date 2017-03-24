////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRIGGERACTION_H__
#define __GUI_TRIGGERACTION_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/DependencyObject.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/CoreApi.h>


NS_CFORWARD(Gui, FrameworkElement)
NS_CFORWARD(Gui, TriggerAction)


namespace Noesis
{
namespace Gui
{

template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::TriggerAction> TriggerActionCollection;


NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Describes an action to perform for a trigger.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.triggeraction.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TriggerAction: public DependencyObject, public IUITreeNode
{
public:
    TriggerAction();
    virtual ~TriggerAction() = 0;

    static void SealActions(TriggerActionCollection* actions);

    /// Performs the action over the supplied element
    virtual void Invoke(FrameworkElement* target, FrameworkElement* nameScope = 0) = 0;

    /// Seals the actions
    virtual void Seal();

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
    /// From DependencyObject
    //@{
    void OnObjectValueSet(Core::BaseComponent* oldValue, Core::BaseComponent* newValue) override;
    //@}

protected:
    NsBool mIsSealed;

private:
    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(TriggerAction, DependencyObject)
};

NS_WARNING_POP

}
}

#endif