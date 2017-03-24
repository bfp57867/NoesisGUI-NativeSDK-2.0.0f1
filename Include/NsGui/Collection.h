////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_COLLECTION_H__
#define __GUI_COLLECTION_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/INotifyCollectionChanged.h>
#include <NsGui/IList.h>
#include <NsGui/IComponentInitializer.h>
#include <NsGui/IUITreeNode.h>
#include <NsCore/ReflectionImplement.h>
#include <NsCore/TypeId.h>
#include <NsCore/NSTLForwards.h>
#include <NsCore/Vector.h>
#include <NsCore/String.h>
#include <NsCore/DynamicCast.h>
#include <NsCore/Error.h>
#include <NsCore/Delegate.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides the base class for a generic collection.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Collection: public Core::BaseComponent, public IList,
    public INotifyCollectionChanged, public IComponentInitializer, public IUITreeNode
{
public:
    /// Constructor
    Collection();
    Collection(IUITreeNode* owner);

    /// Destructor
    virtual ~Collection();

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

protected:
    /// Allows inheritors to perform specific actions when items are added or removed
    //@{
    virtual void OnItemAdded(Core::BaseComponent* item, NsSize index);
    virtual void OnItemRemoved(Core::BaseComponent* item, NsSize index);
    //@}

    // To check before adding an element
    virtual NsBool CheckItem(Core::BaseComponent* item) const;

    // Helper function to get item's type name taking into account boxed values
    static const NsChar* GetItemType(Core::BaseComponent* item);

private:
    NsBool mIsInitialized;
    IUITreeNode* mOwner;

    typedef NsVector<Ptr<Core::BaseComponent> > Items;
    Items mItems;

    NotifyCollectionChangedEventHandler mEvent;

    NS_DECLARE_REFLECTION(Collection, Core::BaseComponent)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
NS_GUI_CORE_API NsSymbol IdOfTypedCollection(const Core::TypeClass* type);

////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class TypedCollection: public Collection
{
public:
    TypedCollection() { }
    TypedCollection(IUITreeNode* owner): Collection(owner) { }

protected:
    /// From Collection
    //@{
    NsBool CheckItem(BaseComponent* item) const override
    {
        if (!ParentClass::CheckItem(item))
        {
            return false;
        }

        if (NsDynamicCast<T*>(item) == 0)
        {
            NS_ERROR("Can't add a '%s' to a '%s'", GetItemType(item), GetClassType()->GetName());
            return false;
        }

        return true;
    }
    //@}

    NS_IMPLEMENT_INLINE_REFLECTION(TypedCollection, Collection)
    {
        NsMeta<Core::TypeId>(IdOfTypedCollection(Core::TypeOf<T>()).GetStr());
    }
};

NS_WARNING_POP

}
}

#endif
