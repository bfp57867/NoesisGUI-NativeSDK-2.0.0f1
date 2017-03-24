////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COLLECTIONVIEW_H__
#define __GUI_COLLECTIONVIEW_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>
#include <NsGui/Events.h>
#include <NsGui/ICollectionView.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/Vector.h>
#include <NsCore/Delegate.h>


NS_IFORWARD(Gui, IList)
class Noesis_CollectionViewTest;


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// CollectionView
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API CollectionView: public Core::BaseComponent, public ICollectionView,
    public INotifyCollectionChanged, public IComponentInitializer, public IUITreeNode
{
public:
    /// Serialization constructor
    CollectionView();

    /// Constructor
    CollectionView(IList* collection);

    /// Destructor
    ~CollectionView();

    /// Returns the underlying unfiltered collection
    IList* GetSourceCollection() const;

    /// Gets the number of records in the view
    NsSize Count() const;

    /// Retrieves the item at the specified zero-based index in the view
    Core::BaseComponent* GetItemAt(NsSize index) const;

    /// Returns the index at which the specified item is located; -1 if the item is unknown
    NsInt IndexOf(Core::BaseComponent* item) const;

    /// From ICollectionView
    //@{
    NsBool CanFilter() const override;
    NsBool CanGroup() const override;
    NsBool CanSort() const override;
    NsBool Contains(Core::BaseComponent* item) const override;
    BaseComponent* CurrentItem() const override;
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
    void InternalCollectionChanged(Core::BaseComponent* sender,
        const NotifyCollectionChangedEventArgs& args);

    void ConnectCollection();
    
    void SetCurrentPosition(NsInt pos);

private:
    friend class ::Noesis_CollectionViewTest;

    NsBool mIsInitialized;
    IUITreeNode* mOwner;

    NsBool mIsDynamic;
    NsInt mCurrentPosition;

    Ptr<IList> mCollection;

    EventHandler mCurrentChanged;
    NotifyCollectionChangedEventHandler mCollectionChanged;

    NS_DECLARE_REFLECTION(CollectionView, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif