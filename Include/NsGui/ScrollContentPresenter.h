////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_SCROLLCONTENTPRESENTER_H__
#define __GUI_SCROLLCONTENTPRESENTER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ContentPresenter.h>
#include <NsGui/IScrollInfo.h>
#include <NsGui/ILayerManager.h>
#include <NsDrawing/Size.h>
#include <NsDrawing/Point.h>
#include <NsCore/ReflectionDeclare.h>

#include <memory>


NS_SFORWARD(Drawing, Rect)
NS_CFORWARD(Gui, ScrollViewer)
NS_CFORWARD(Gui, VisualCollection)
NS_CFORWARD(Gui, RectangleGeometry)
class Noesis_ItemsControlTest;
class Noesis_ScrollViewerTest;

namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the measurements for the VirtualizingPanel.CacheLength attached property.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.scrollcontentpresenter.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ScrollContentPresenter: public ContentPresenter, public IScrollInfo,
    public ILayerManager
{
public:
    ScrollContentPresenter();
    ~ScrollContentPresenter();

    /// Indicates whether the content, if IScrollInfo, should be allowed to control scrolling.
    //@{
    NsBool GetCanContentScroll() const;
    void SetCanContentScroll(NsBool value);
    //@}

    // From IScrollInfo
    //@{
    NsBool GetCanHorizontallyScroll() const override;
    void SetCanHorizontallyScroll(NsBool canScroll) override;
    NsBool GetCanVerticallyScroll() const override;
    void SetCanVerticallyScroll(NsBool canScroll) override;
    NsFloat32 GetExtentWidth() const override;
    NsFloat32 GetExtentHeight() const override;
    NsFloat32 GetViewportWidth() const override;
    NsFloat32 GetViewportHeight() const override;
    NsFloat32 GetHorizontalOffset() const override;
    NsFloat32 GetVerticalOffset() const override;
    ScrollViewer* GetScrollOwner() const override;
    void SetScrollOwner(ScrollViewer* owner) override;
    void LineLeft() override;
    void LineRight() override;
    void LineUp() override;
    void LineDown() override;
    void PageLeft() override;
    void PageRight() override;
    void PageUp() override;
    void PageDown() override;
    void MouseWheelLeft(NsFloat32 delta = 1.0f) override;
    void MouseWheelRight(NsFloat32 delta = 1.0f) override;
    void MouseWheelUp(NsFloat32 delta = 1.0f) override;
    void MouseWheelDown(NsFloat32 delta = 1.0f) override;
    void SetHorizontalOffset(NsFloat32 offset) override;
    void SetVerticalOffset(NsFloat32 offset) override;
    Drawing::Rect MakeVisible(Visual* visual, const Drawing::Rect& rect) override;
    //@}

    /// From ILayerManager
    //@{
    void AddLayer(Visual* layerRoot) override;
    void RemoveLayer(Visual* layerRoot) override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

public:
    static const DependencyProperty* CanContentScrollProperty;

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args) override;
    //@}

    /// From Visual
    //@{
    NsSize GetVisualChildrenCount() const override;
    Visual* GetVisualChild(NsSize index) const override;
    //@}

    /// From UIElement
    //@{
    Ptr<Geometry> GetLayoutClip(const Drawing::Size& layoutSlotSize) const override;
    //@}

    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize) override;
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize) override;
    void OnTemplatedParentChanged(FrameworkElement* oldParent,
        FrameworkElement* newParent) override;
    //@}

    /// From ContentPresenter
    //@{
    void OnContentChanged(Core::BaseComponent* oldContent,
        Core::BaseComponent* newContent) override;
    //@}

private:
    NsBool IsScrollClient() const;
    void UpdateScrollInfo(FrameworkElement* templatedParent, Core::BaseComponent* content);

    void EnsureScrollData();
    NsBool HasScrollData() const;
    NsBool UpdateScrollData(const Drawing::Size& extent, const Drawing::Size& viewport);

private:
    friend class ItemsPresenter;
    friend class ::Noesis_ScrollViewerTest;
    friend class ::Noesis_ItemsControlTest;

    Ptr<VisualCollection> mLayers;
    mutable Ptr<RectangleGeometry> mLayoutClip;

    struct ScrollData;
    std::unique_ptr<ScrollData> mScrollData;
    IScrollInfo* mScrollInfo;

    NS_DECLARE_REFLECTION(ScrollContentPresenter, ContentPresenter)
};

NS_WARNING_POP

}
}

#endif