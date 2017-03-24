////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_INPUTGESTURE_H__
#define __GUI_INPUTGESTURE_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{
namespace Gui
{

// Forward declarations
//@{
struct RoutedEventArgs;
//@}

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Abstract class that describes input device gestures.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.input.inputgesture.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API InputGesture: public Core::BaseComponent
{
public:
    NS_DISABLE_COPY(InputGesture)

    InputGesture();
    virtual ~InputGesture() = 0;

    /// When overridden in a derived class, determines whether the specified InputGesture matches
    /// the input specified
    virtual NsBool Matches(Core::BaseComponent* target, const RoutedEventArgs& args) = 0;

private:
    NS_DECLARE_REFLECTION(InputGesture, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif
