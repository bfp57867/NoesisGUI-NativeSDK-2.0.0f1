////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ELLIPSE_H__
#define __GUI_ELLIPSE_H__


#include <Noesis.h>
#include <NsGui/Shape.h>
#include <NsDrawing/Rect.h>


NS_CFORWARD(Gui, EllipseGeometry)


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Draws an ellipse.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.shapes.ellipse.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Ellipse: public Shape
{
public:
    /// Constructor
    Ellipse();

    /// Destructor
    ~Ellipse();

protected:
    /// From UIElement
    //@{
    void OnRender(DrawingContext* context) override;
    //@}

    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize) override;
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize) override;
    //@}

private:
    Drawing::Size GetMinimumSize() const;

private:
    Ptr<EllipseGeometry> mRenderGeometry;

    NS_DECLARE_REFLECTION(Ellipse, Shape)
};

}
}

#endif
