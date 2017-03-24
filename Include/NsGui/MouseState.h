////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_MOUSESTATE_H__
#define __GUI_MOUSESTATE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/InputEnums.h>
#include <NsDrawing/Point.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API MouseState
{
    Drawing::Point position;
    MouseButtonState leftButton;
    MouseButtonState rightButton;
    MouseButtonState middleButton;
    MouseButtonState xButton1Button;
    MouseButtonState xButton2Button;

    MouseState();

    MouseState(const Drawing::Point& position, MouseButtonState leftButton, 
        MouseButtonState rightButton, MouseButtonState middleButton,
        MouseButtonState xButton1Button, MouseButtonState xButton2Button);
};

NS_WARNING_POP

}
}


#endif
