////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BORDER_H__
#define __GUI_BORDER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Decorator.h>


NS_CFORWARD(Gui, Brush)
NS_CFORWARD(Gui, Pen)
NS_CFORWARD(Gui, StreamGeometryContext)
NS_SFORWARD(Drawing, Thickness)
NS_SFORWARD(Drawing, CornerRadius)


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Draws a border, background, or both around another element. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.border.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Border: public Decorator
{
public:
    /// Constructor
    Border(NsBool logicalChild = true);

    /// Destructor
    ~Border();

    /// Gets or sets border background
    //@{
    Brush* GetBackground() const;
    void SetBackground(Brush* brush);
    //@}

    /// Gets or sets border brush
    //@{
    Brush* GetBorderBrush() const;
    void SetBorderBrush(Brush* brush);
    //@}

    /// Gets or sets border thickness
    //@{
    const Drawing::Thickness& GetBorderThickness() const;
    void SetBorderThickness(const Drawing::Thickness& thickness);
    //@}

    /// Gets or sets corner radius
    //@{
    const Drawing::CornerRadius& GetCornerRadius() const;
    void SetCornerRadius(const Drawing::CornerRadius& corners);
    //@}

    /// Gets or sets the amount of space between a border and its child element
    //@{
    const Drawing::Thickness& GetPadding() const;
    void SetPadding(const Drawing::Thickness& padding);
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}

    /// From UIElement
    //@{
    void OnRender(DrawingContext* context);
    //@}

    /// From FrameworkElement
    //@{
    Drawing::Size MeasureOverride(const Drawing::Size& availableSize);
    Drawing::Size ArrangeOverride(const Drawing::Size& finalSize);
    //@}

private:
    void CreatePen();
    void UpdateGeometries();
    NsBool IsBorderUniform(const Drawing::Thickness& borders,
        const Drawing::CornerRadius& corners) const;
    void GenerateSimpleGeometry(const Drawing::Thickness& borders,
        const Drawing::CornerRadius& corners);
    void GenerateComplexGeometry(const Drawing::Thickness& borders,
        const Drawing::CornerRadius& corners);
    void CoerceBorders(NsFloat32 width, NsFloat32 height, NsFloat32& topBorder,
        NsFloat32& bottomBorder, NsFloat32& leftBorder, NsFloat32& rightBorder) const;
    void CoerceCorners(NsFloat32 width, NsFloat32 height, Drawing::Size& topLeftCorner,
        Drawing::Size& topRightCorner, Drawing::Size& bottomLeftCorner,
        Drawing::Size& bottomRightCorner) const;
    NsFloat32 ExtrudeCorner(NsFloat32 cornerSize, NsFloat32 halfBorderSize) const;
    void BuildPathData(const StreamGeometryContext& context,
        const Drawing::Point& p0, const Drawing::Point& p1,
        const Drawing::Point& p2, const Drawing::Point& p3,
        const Drawing::Point& p4, const Drawing::Point& p5,
        const Drawing::Point& p6, const Drawing::Point& p7,
        const Drawing::Size& a12, const Drawing::Size& a34,
        const Drawing::Size& a56, const Drawing::Size& a70) const;

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* BackgroundProperty;
    static const DependencyProperty* BorderBrushProperty;
    static const DependencyProperty* BorderThicknessProperty;
    static const DependencyProperty* CornerRadiusProperty;
    static const DependencyProperty* PaddingProperty;
    //@}

private:
    Ptr<Pen> mPen;

    Ptr<Geometry> mBorderGeometry;
    Ptr<Geometry> mBackgroundGeometry;

    Drawing::Size mPreviousRenderSize;

    union
    {
        struct
        {
            NsBool isComplexGeometry: 1;
            NsBool isValidGeometry: 1;
            NsBool hasBorder: 1;
        } mFlags;

        // To quickly set all flags to 0
        NsUInt8 mAllFlags;
    };

    NS_DECLARE_REFLECTION(Border, Decorator)
};

NS_WARNING_POP

}
}

#endif
