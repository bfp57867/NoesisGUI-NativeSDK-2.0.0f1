////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_GRADIENTSTOPCOLLECTION_H__
#define __GUI_GRADIENTSTOPCOLLECTION_H__


#include <Noesis.h>
#include <NsGui/FreezableCollection.h>
#include <NsGui/GradientStop.h>
#include <NsGui/IRenderProxyCreator.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents a collection of GradientStop objects that can be individually accessed by index.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API GradientStopCollection: public FreezableCollection, public IRenderProxyCreator
{
public:
    /// Constructor
    GradientStopCollection();

    /// Destructor
    ~GradientStopCollection();

    /// From IRenderProxyCreator
    //@{
    void CreateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex) override;
    void UpdateRenderProxy(RenderTreeUpdater& updater, NsSize proxyIndex) override;
    void UnregisterRenderer(ViewId viewId) override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    /// From FreezableCollection
    //@{
    NsBool CheckItem(Core::BaseComponent* item) const override;
    void OnItemAdded(Core::BaseComponent* item, NsSize index) override;
    void OnItemRemoved(Core::BaseComponent* item, NsSize index) override;
    //@}

private:
    void RegisterChild(Core::BaseComponent* item);
    void UnregisterChild(Core::BaseComponent* item);
    void OnChildChanged(Freezable* obj, FreezableEventReason reason);

private:
    RenderProxyCreatorFlags mUpdateFlags;

    enum UpdateFlags
    {
        UpdateFlags_Stops
    };

    NS_DECLARE_REFLECTION(GradientStopCollection, FreezableCollection)
};

NS_WARNING_POP

}
}

#endif
