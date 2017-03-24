////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_FREEZABLECOLLECTION_H__
#define __GUI_FREEZABLECOLLECTION_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Freezable.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsGui/IList.h>
#include <NsGui/IUITreeNode.h>
#include <NsCore/TypeId.h>
#include <NsCore/String.h>
#include <NsCore/Vector.h>
#include <NsCore/DynamicCast.h>
#include <NsCore/Error.h>
#include <NsCore/ReflectionImplement.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// FreezableCollection. Base collection implementation for storing Freezables
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API FreezableCollection: public Freezable, public IList,
    public INotifyCollectionChanged, public IUITreeNode
{
public:
    /// Constructor
    FreezableCollection();
    FreezableCollection(IUITreeNode* owner);

    /// Destructor
    virtual ~FreezableCollection();

    /// From IList
    //@{
    NsSize Count() const override;
    Core::BaseComponent* Get(NsSize index) const override;
    void Set(NsSize index, Core::BaseComponent* item) override;
    void Set(NsSize index, const NsChar* item) override;
    NsSize Add(Core::BaseComponent* item) override;
    NsSize Add(const NsChar* item) override;
    void Clear() override;
    NsBool Contains(Core::BaseComponent* item) const override;
    NsInt IndexOf(Core::BaseComponent* item) const override;
    void Insert(NsSize index, Core::BaseComponent* item) override;
    void Insert(NsSize index, const NsChar* item) override;
    void Remove(Core::BaseComponent* item) override;
    void RemoveAt(NsSize index) override;
    //@}

    /// From INotifyCollectionChanged
    //@{
    NotifyCollectionChangedEventHandler& CollectionChanged() override;
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

protected:
    // To check an item before adding it to the collection
    virtual NsBool CheckItem(Core::BaseComponent* item) const;

    /// Allows inheritors to perform specific actions when items are added or removed
    //@{
    virtual void OnItemAdded(Core::BaseComponent* item, NsSize index);
    virtual void OnItemRemoved(Core::BaseComponent* item, NsSize index);
    //@}
    
    /// From Freezable
    //@{
    NsBool FreezeCore(NsBool isChecking) override;
    void CloneCore(const Freezable* source) override;
    void CloneCurrentValueCore(const Freezable* source) override;
    void GetAsFrozenCore(const Freezable* source) override;
    void GetCurrentValueAsFrozenCore(const Freezable* source) override;
    //void CloneCommonCore(const Freezable* source) override;
    //@}
    
    /// From DependencyObject
    //@{
    void OnInit() override;
    //@}

private:
    NsBool CheckFrozen();

private:
    IUITreeNode* mOwner;

    typedef NsVector<Ptr<Core::BaseComponent> > Items;
    Items mItems;
    
    NotifyCollectionChangedEventHandler mEvent;

    NS_DECLARE_REFLECTION(FreezableCollection, Freezable)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_GUI_CORE_API NsSymbol IdOfTypedCollection(const Core::TypeClass* type);

////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class TypedFreezableCollection: public FreezableCollection
{
protected:
    /// From FreezableCollection
    //@{
    NsBool CheckItem(BaseComponent* item) const override
    {
        if (!ParentClass::CheckItem(item))
        {
            return false;
        }

        if (NsDynamicCast<T*>(item) == 0)
        {
            NS_ERROR("'%s' items not allowed for '%s' collection", item->GetClassType()->GetName(),
                GetClassType()->GetName());
            return false;
        }

        return true;
    }
    //@}
    
    NS_IMPLEMENT_INLINE_REFLECTION(TypedFreezableCollection, FreezableCollection)
    {
        NsMeta<Core::TypeId>(IdOfTypedCollection(Core::TypeOf<T>()).GetStr());
    }
};

NS_WARNING_POP

}
}


#endif
