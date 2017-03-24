////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ADORNERDECORATOR_H__
#define __GUI_ADORNERDECORATOR_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Decorator.h>
#include <NsGui/ILayerManager.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Ptr.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Provides an adorner layer for elements beneath it in the visual tree.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.documents.adornerdecorator.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API AdornerDecorator: public Decorator, public ILayerManager
{
public:
    /// Constructor
    AdornerDecorator(NsBool logicalChild = true);

    /// Destructor
    ~AdornerDecorator();

    /// From ILayerManager
    //@{
    void AddLayer(Visual* layerRoot) override;
    void RemoveLayer(Visual* layerRoot) override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    /// From DependencyObject
    //@{
    void OnInit() override;
    //@}

    /// From Visual
    //@{
    NsSize GetVisualChildrenCount() const override;
    Visual* GetVisualChild(NsSize index) const override;
    //@}

    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize) override;
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize) override;
    //@}

    /// From Decorator
    //@{
    void OnChildChanged(UIElement* oldChild, UIElement* newChild) override;
    //@}

private:
    struct AdornerLayers;
    Ptr<AdornerLayers> mLayers;

    NS_DECLARE_REFLECTION(AdornerDecorator, Decorator);
};

NS_WARNING_POP

}
}

#endif
