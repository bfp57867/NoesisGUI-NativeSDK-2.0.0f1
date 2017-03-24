////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_TRANSFORMGROUP_H__
#define __GUI_TRANSFORMGROUP_H__


#include <Noesis.h>
#include <NsGui/Transform.h>


NS_SFORWARD(Gui, NotifyCollectionChangedEventArgs)


namespace Noesis
{
namespace Gui
{

template <class T> class TypedFreezableCollection;
typedef Noesis::Gui::TypedFreezableCollection<Noesis::Gui::Transform> TransformCollection;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a composite Transform composed of other Transform objects.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.transformgroup.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API TransformGroup: public Transform
{
public:
    TransformGroup();
    ~TransformGroup();

    /// Gets the number of transforms that compose this group
    NsSize GetNumChildren() const;

    /// Gets the specified transform child
    Transform* GetChild(NsSize index) const;

    /// Gets or sets the TransformCollection that defines this TransformGroup
    //@{
    TransformCollection* GetChildren() const;
    void SetChildren(TransformCollection* children);
    //@}

    /// From Transform
    //@{
    Math::Transform2f GetTransform() const;
    //@}

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex);
    void UnregisterRenderer(ViewId viewId);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ChildrenProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& e);
    //@}

    /// From Freezable
    //@{
    NsBool FreezeCore(NsBool isChecking);
    //@}

private:
    void OnChildrenChanged(Core::BaseComponent* sender,
        const Gui::NotifyCollectionChangedEventArgs& args);
    void RegisterChildren(TransformCollection* children);
    void RegisterChild(Core::BaseComponent* child);
    void UnregisterChildren(TransformCollection* children);
    void UnregisterChild(Core::BaseComponent* child);

    void OnChildChanged(Freezable* obj, FreezableEventReason reason);

    void DisconnectChildren();

private:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Children
    };

    NS_DECLARE_REFLECTION(TransformGroup, Transform)
};

}
}

#endif
