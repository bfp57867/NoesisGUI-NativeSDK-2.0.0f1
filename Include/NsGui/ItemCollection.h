////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ITEMCOLLECTION_H__
#define __GUI_ITEMCOLLECTION_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Delegate.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ICollectionView.h>
#include <NsGui/IList.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class ItemsControl;
class Collection;
class CollectionView;
//@}

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// ItemCollection
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ItemCollection: public Core::BaseComponent, public ICollectionView, 
    public IList, public INotifyCollectionChanged, public IComponentInitializer, 
    public IUITreeNode
{
public:
    ItemCollection();
    ItemCollection(ItemsControl* itemsControl);
    ~ItemCollection();

    /// Sets ItemCollection owner, it would be an ItemsControl object
    void SetItemsControlOwner(ItemsControl* itemsControl);
    
    /// To be called from ItemsControl when the ItemsSource is assigned with a CollectionView
    void SetView(CollectionView* view);
    
    /// Check if the itemcollection is related to an external collection, and so it is readonly
    NsBool IsReadOnly() const;
    
    /// From ICollectionView
    //@{
    NsBool CanFilter() const override;
    NsBool CanGroup() const override;
    NsBool CanSort() const override;
    NsBool Contains(Core::BaseComponent* item) const override;
    Core::BaseComponent* CurrentItem() const override;
    NsInt CurrentPosition() const override;
    NsBool IsCurrentAfterLast() const override;
    NsBool IsCurrentBeforeFirst() const override;
    NsBool IsEmpty() const override;
    NsBool MoveCurrentTo(Core::BaseComponent* item) override;
    NsBool MoveCurrentToFirst() override;
    NsBool MoveCurrentToLast() override;
    NsBool MoveCurrentToNext() override;
    NsBool MoveCurrentToPosition(NsInt position) override;
    NsBool MoveCurrentToPrevious() override;
    void Refresh() override;
    EventHandler& CurrentChanged() override;
    //@}

    /// From IList
    //@{
    NsSize Count() const override;
    Core::BaseComponent* Get(NsSize index) const override;
    void Set(NsSize index, Core::BaseComponent* item) override;
    void Set(NsSize index, const NsChar* item) override;
    NsSize Add(Core::BaseComponent* item) override;
    NsSize Add(const NsChar* item) override;
    void Clear() override;
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

    /// From IComponentInitializer
    //@{
    NsBool IsInitialized() const override;
    void Init() override;
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
    NsBool CheckReadOnly() const;

    void ConnectChildren() const;
    void DisconnectChildren() const;

    void CreateCollections();

    void OnCollectionChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);
    void OnCurrentChanged(Core::BaseComponent* sender, const EventArgs& args);

    void ConnectCollection();
    void DisconnectCollection();

    void RegisterDelegates();
    void UnregisterDelegates();
    
private:
    NsBool mIsInitialized;
    IUITreeNode* mOwner;

    ItemsControl* mItemsControl;
    
    Ptr<Collection> mLocalCollection;
    Ptr<CollectionView> mEffectiveCollectionView;
    
    EventHandler mCurrentChanged;
    NotifyCollectionChangedEventHandler mCollectionChanged;

    NS_DECLARE_REFLECTION(ItemCollection, BaseComponent)
};

NS_WARNING_POP

}
}

#endif