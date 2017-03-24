////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DRAWINGCONTEXT_H__
#define __GUI_DRAWINGCONTEXT_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/DelegateForward.h>
#include <NsCore/Ptr.h>

// hack
#undef DrawText


NS_SFORWARD(Drawing, Point)
NS_SFORWARD(Drawing, Rect)
NS_SFORWARD(Drawing, Size)
NS_CFORWARD(Drawing, Color)
NS_CFORWARD(Gui, Brush)
NS_CFORWARD(Gui, Pen)
NS_CFORWARD(Gui, Geometry)
NS_CFORWARD(Gui, ImageSource)
NS_CFORWARD(Gui, FormattedText)
NS_CFORWARD(Gui, Transform)
NS_CFORWARD(Gui, DrawingCommands)


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// DrawingContext. Describes visual content using draw, push, and pop commands.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DrawingContext: public Core::BaseComponent
{
public:
    /// Constructor
    DrawingContext();

    /// Destructor
    ~DrawingContext();

    /// Gets drawing commands generated for the specified drawing operations
    DrawingCommands* GetDrawingCommands() const;

    /// Resets stored drawing commands
    void Reset();

    /// Draws the specified Geometry using the specified Brush and Pen
    void DrawGeometry(Brush* brush, Pen* pen, Geometry* geometry);

    /// Draws an image into the region defined by the specified Rect
    void DrawImage(ImageSource* imageSource, const Drawing::Rect& rect);

    /// Draws formatted text at the specified location
    void DrawText(FormattedText* formattedText, const Drawing::Rect& bounds);

    /// Pops the last opacity mask, opacity, clip, effect, or transform operation that was pushed
    /// onto the drawing context
    void Pop();

    /// Pushes the specified clip region onto the drawing context
    void PushClip(Geometry* clipGeometry);

    /// Pushes the specified Transform onto the drawing context
    void PushTransform(Transform* transform);

private:
    Ptr<DrawingCommands> mCommands;
    NsSize mPushes;

    NS_DECLARE_REFLECTION(DrawingContext, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif
