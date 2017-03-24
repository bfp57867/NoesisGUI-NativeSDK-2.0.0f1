////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_EASINGKEYFRAME_H__
#define __GUI_EASINGKEYFRAME_H__


#include <Noesis.h>
#include <NsGui/AnimationApi.h>
#include <NsGui/KeyFrame.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
class EasingFunctionBase;
template<class T> const NsChar* EasingKeyFrameIdOf();
//@}

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Defines a property that enables you to associate an easing function with an 
/// AnimationUsingKeyFrames key-frame animation. Existing types are:
///
/// EasingDoubleKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.easingdoublekeyframe.aspx
///
///
/// EasingInt16KeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.easingint16keyframe.aspx
///
///
/// EasingInt32KeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.easingint32keyframe.aspx
///
///
/// EasingColorKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.easingcolorkeyframe.aspx
///
///
/// EasingPointKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.easingpointkeyframe.aspx
///
///
/// EasingRectKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.easingrectkeyframe.aspx
///
///
/// EasingSizeKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.easingsizekeyframe.aspx
///
///
/// EasingThicknessKeyFrame:
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.easingthicknesskeyframe.aspx
///
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class NS_GUI_ANIMATION_API EasingKeyFrame: public KeyFrame<T>
{
public:
    EasingKeyFrame();
    ~EasingKeyFrame();
    
    //@{
    EasingFunctionBase* GetEasingFunction() const;
    void SetEasingFunction(EasingFunctionBase* function);
    //@}
    
public:
    /// Dependency properties
    //@{
    static const DependencyProperty* EasingFunctionProperty;
    //@}
    
protected:
    /// From KeyFrame
    //@{
    T InterpolateValueCore(typename Core::Param<T>::Type baseValue, 
        NsFloat32 keyFrameProgress);
    //@}
    
    NS_DECLARE_REFLECTION(EasingKeyFrame, KeyFrame<T>)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef EasingKeyFrame<NsFloat32> EasingDoubleKeyFrame;
typedef EasingKeyFrame<NsInt16> EasingInt16KeyFrame;
typedef EasingKeyFrame<NsInt32> EasingInt32KeyFrame;
typedef EasingKeyFrame<Noesis::Drawing::Color> EasingColorKeyFrame;
typedef EasingKeyFrame<Noesis::Drawing::Point> EasingPointKeyFrame;
typedef EasingKeyFrame<Noesis::Drawing::Rect> EasingRectKeyFrame;
typedef EasingKeyFrame<Noesis::Drawing::Size> EasingSizeKeyFrame;
typedef EasingKeyFrame<Noesis::Drawing::Thickness> EasingThicknessKeyFrame;

////////////////////////////////////////////////////////////////////////////////////////////////////
template<> inline const NsChar* EasingKeyFrameIdOf<DoubleKeyFrame>() 
{ return "EasingDoubleKeyFrame"; }
template<> inline const NsChar* EasingKeyFrameIdOf<Int16KeyFrame>() 
{ return "EasingInt16KeyFrame"; }
template<> inline const NsChar* EasingKeyFrameIdOf<Int32KeyFrame>() 
{ return "EasingInt32KeyFrame"; }
template<> inline const NsChar* EasingKeyFrameIdOf<ColorKeyFrame>() 
{ return "EasingColorKeyFrame"; }
template<> inline const NsChar* EasingKeyFrameIdOf<PointKeyFrame>() 
{ return "EasingPointKeyFrame"; }
template<> inline const NsChar* EasingKeyFrameIdOf<RectKeyFrame>() 
{ return "EasingRectKeyFrame"; }
template<> inline const NsChar* EasingKeyFrameIdOf<SizeKeyFrame>() 
{ return "EasingSizeKeyFrame"; }
template<> inline const NsChar* EasingKeyFrameIdOf<ThicknessKeyFrame>() 
{ return "EasingThicknessKeyFrame"; }

NS_WARNING_POP

}
}


#endif
