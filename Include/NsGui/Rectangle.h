////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_RECTANGLE_H__
#define __GUI_RECTANGLE_H__


#include <Noesis.h>
#include <NsGui/Shape.h>
#include <NsDrawing/Rect.h>


NS_CFORWARD(Gui, RectangleGeometry)
class Noesis_RectangleTest;


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Draws a rectangle.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.shapes.rectangle.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Rectangle: public Shape
{
public:
    /// Constructor
    Rectangle();

    /// Destructor
    ~Rectangle();

    /// Gets or sets the x-axis radius of the ellipse that is used to round the corners of the
    /// rectangle
    //@{
    NsFloat32 GetRadiusX() const;
    void SetRadiusX(NsFloat32 radius);
    //@}

    /// Gets or sets the y-axis radius of the ellipse that is used to round the corners of the
    /// rectangle
    //@{
    NsFloat32 GetRadiusY() const;
    void SetRadiusY(NsFloat32 radius);
    //@}

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* RadiusXProperty;
    static const DependencyProperty* RadiusYProperty;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args) override;
    //@}

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
    friend class ::Noesis_RectangleTest;

    Ptr<RectangleGeometry> mRenderGeometry;

    NS_DECLARE_REFLECTION(Rectangle, Shape)
};

NS_WARNING_POP

}
}

#endif
