////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_STACKPANEL_H__
#define __GUI_STACKPANEL_H__


#include <Noesis.h>
#include <NsGui/Panel.h>
#include <NsGui/IScrollInfo.h>

#include <memory>


class Noesis_ScrollViewerTest;


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
enum Orientation;
enum TextAlignment;
//@}

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Arranges child elements into a single horizontal or vertical line.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.stackpanel.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API StackPanel: public Panel, public IScrollInfo
{
public:
    StackPanel();
    ~StackPanel();

    /// Gets or sets orientation of children elements
    //@{
    Orientation GetOrientation() const;
    void SetOrientation(Orientation orientation);
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

    NS_IMPLEMENT_INTERFACE_FIXUP

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* OrientationProperty;
    //@}

protected:
    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize) override;
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize) override;
    //@}

private:
    void EnsureScrollData();
    NsBool HasScrollData() const;
    NsBool IsScrolling() const;

private:
    friend class VirtualizingStackPanel;
    friend class ::Noesis_ScrollViewerTest;

    struct ScrollData;
    std::unique_ptr<ScrollData> mScrollData;

    NS_DECLARE_REFLECTION(StackPanel, Panel)
};

NS_WARNING_POP

}
}

#endif
