////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_KEYSPLINE_H__
#define __GUI_KEYSPLINE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/Freezable.h>
#include <NsGui/AnimationApi.h>
#include <NsDrawing/Point.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// This class is used by a spline key frame to define animation progress.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.keyspline.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_ANIMATION_API KeySpline: public Freezable
{
public:
    KeySpline();
    KeySpline(const Drawing::Point& controlPoint1, const Drawing::Point& controlPoint2);
    KeySpline(NsFloat32 controlPoint1X, NsFloat32 controlPoint1Y, NsFloat32 controlPoint2X,
        NsFloat32 controlPoint2Y);
    
    /// Gets or sets the first control point used to define a Bezier curve that describes
    /// a KeySpline
    //@{
    const Drawing::Point& GetControlPoint1() const;
    void SetControlPoint1(const Drawing::Point& point);
    //@}
    
    /// Gets or sets the second control point used to define a Bezier curve that describes 
    /// a KeySpline
    //@{
    const Drawing::Point& GetControlPoint2() const;
    void SetControlPoint2(const Drawing::Point& point);
    //@}

    /// Calculates spline progress from a supplied linear progress.
    NsFloat32 GetSplineProgress(NsFloat32 linearProgress) const;

    /// Tries to parse a KeySpline from a string
    static NsBool TryParse(const NsChar* str, Ptr<KeySpline>& result);
    
private:
    /// From Freezable
    //@{
    void CloneCommonCore(const Freezable* source);
    //@}

private:
    Drawing::Point mControlPoint1;
    Drawing::Point mControlPoint2;

    NS_DECLARE_REFLECTION(KeySpline, Freezable)
};

NS_WARNING_POP

}
}

#endif