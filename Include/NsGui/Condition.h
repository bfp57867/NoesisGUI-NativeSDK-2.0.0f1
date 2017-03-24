////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_CONDITION_H__
#define __GUI_CONDITION_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/String.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>


NS_CFORWARD(Gui, DependencyProperty)
NS_CFORWARD(Gui, BaseBinding)
NS_CFORWARD(Gui, Condition)


namespace Noesis
{
namespace Gui
{

template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::Condition> ConditionCollection;

enum ConditionType
{
    ConditionType_Property,
    ConditionType_Binding
};

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a condition for the MultiTrigger and the MultiDataTrigger, which apply changes to
/// property values based on a set of conditions.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.condition.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Condition: public Core::BaseComponent, public IUITreeNode
{
public:
    Condition();
    ~Condition();

    static void SealConditions(ConditionCollection* conditions, ConditionType type);

    /// Gets or sets the binding that produces the property value of the data object.
    //@{
    BaseBinding* GetBinding() const;
    void SetBinding(BaseBinding* binding);
    //@}

    /// Gets or sets the property of the condition. This is only applicable to MultiTrigger objects
    //@{
    const DependencyProperty* GetProperty() const;
    void SetProperty(const DependencyProperty* property);
    //@}

    /// Gets or sets the name of the object with the property that causes the associated setters to 
    /// be applied. This is only applicable to MultiTrigger objects. 
    //@{
    const NsChar* GetSourceName() const;
    void SetSourceName(const NsChar* name);
    //@}

    /// Gets or sets the value of the condition.
    //@{
    Core::BaseComponent* GetValue() const;
    void SetValue(Core::BaseComponent* object);
    //@}

    /// Seals the conditions
    void Seal(ConditionType type);

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

    Ptr<BaseBinding> mBinding;
    const DependencyProperty* mProperty;
    Ptr<BaseComponent> mValue;
    NsString mSourceName;

    NsBool mIsSealed;

    NS_DECLARE_REFLECTION(Condition, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif