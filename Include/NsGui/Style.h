////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STYLE_H__
#define __GUI_STYLE_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/ISealable.h>


NS_CFORWARD(Gui, BaseSetter)
NS_CFORWARD(Gui, BaseTrigger)
NS_CFORWARD(Gui, ResourceDictionary)
NS_CFORWARD(Gui, ResourceKeyType)
NS_CFORWARD(Gui, FrameworkElement)


namespace Noesis
{
namespace Gui
{

template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseSetter> BaseSetterCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseTrigger> TriggerCollection;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Enables the sharing of properties, resources, and event handlers between instances of a type.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Style: public Core::BaseComponent, public ISealable, public IUITreeNode
{
public:
    Style();
    ~Style();

    /// Gets or sets the type for which this style is intended
    //@{
    ResourceKeyType* GetTargetType() const;
    void SetTargetType(ResourceKeyType* targetType);
    //@}

    /// Gets or sets a defined style that is the basis of the current style
    //@{
    Style* GetBasedOn() const;
    void SetBasedOn(Style* style);
    //@}

    /// Gets or sets the collection of resources that can be used within the scope of this style
    //@{
    ResourceDictionary* GetResources() const;
    void SetResources(ResourceDictionary* resources);
    //@}

    /// Gets a collection of Setter and EventSetter objects
    BaseSetterCollection* GetSetters() const;

    /// Gets a collection of TriggerBase objects that apply property values based on specified
    /// conditions
    TriggerCollection* GetTriggers() const;

    /// From ISealable
    //@{
    NsBool CanSeal() const final;
    NsBool IsSealed() const final;
    void Seal() final;
    //@}

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
    void EnsureResources() const;
    void EnsureSetters() const;
    void EnsureTriggers() const;

    NsBool CheckTargetType(const Core::TypeClass* elementType) const;

    NsBool CheckBasedOnType() const;
    NsBool CheckBasedOnCircularity() const;

private:
    friend struct BaseStyleTriggerProvider;
    friend struct BaseStyleSetterProvider;
    friend class DynamicResourceExpression;
    friend class StaticResourceExtension;
    friend class FrameworkElement;

    IUITreeNode* mOwner;
    Ptr<ResourceKeyType> mTargetType;
    Ptr<Style> mBasedOn;
    mutable Ptr<ResourceDictionary> mResources;
    mutable Ptr<BaseSetterCollection> mSetters;
    mutable Ptr<TriggerCollection> mTriggers;
    NsBool mIsSealed;

    NS_DECLARE_REFLECTION(Style, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif
