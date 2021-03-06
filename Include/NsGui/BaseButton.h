////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASEBUTTON_H__
#define __GUI_BASEBUTTON_H__


#include <Noesis.h>
#include <NsGui/ContentControl.h>
#include <NsGui/ICommandSource.h>
#include <NsGui/Enums.h>


namespace Noesis
{
namespace Gui
{

// Forward declaration
//@{
NS_INTERFACE ICommand;
enum ClickMode;
//@}

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for all button controls.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.primitives.buttonbase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseButton: public ContentControl, public ICommandSource
{
public:
    NS_DISABLE_COPY(BaseButton)

    BaseButton();
    virtual ~BaseButton() = 0;

    /// Gets or sets when the Click event occurs
    //@{
    ClickMode GetClickMode() const;
    void SetClickMode(ClickMode mode);
    //@}

    /// Gets or sets the command to invoke when this button is pressed
    //@{
    ICommand* GetCommand() const override;
    void SetCommand(ICommand* command);
    //@}

    /// Gets or sets the parameter to pass to the Command property
    //@{
    Core::BaseComponent* GetCommandParameter() const override;
    void SetCommandParameter(Core::BaseComponent* param);
    //@}

    /// Gets or sets the element on which to raise the specified command
    //@{
    UIElement* GetCommandTarget() const override;
    void SetCommandTarget(UIElement* target);
    //@}

    /// Gets a value that indicates whether a button is currently activated
    NsBool GetIsPressed() const;

    /// Occurs when a Button is clicked
    UIElement::RoutedEvent_<RoutedEventHandler> Click();

    NS_IMPLEMENT_INTERFACE_FIXUP

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* ClickModeProperty;
    static const DependencyProperty* CommandProperty;
    static const DependencyProperty* CommandParameterProperty;
    static const DependencyProperty* CommandTargetProperty;
    static const DependencyProperty* IsPressedProperty;
    //@}

    /// Routed events
    //@{
    static const RoutedEvent* ClickEvent;
    //@}

protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args) override;
    //@}

    /// From UIElement
    //@{
    NsBool IsEnabledCore() const override;
    void OnKeyDown(const KeyEventArgs& e) override;
    void OnKeyUp(const KeyEventArgs& e) override;
    void OnLostKeyboardFocus(const KeyboardFocusChangedEventArgs& e) override;
    void OnLostMouseCapture(const MouseEventArgs& e) override;
    void OnMouseEnter(const MouseEventArgs& e) override;
    void OnMouseLeave(const MouseEventArgs& e) override;
    void OnMouseLeftButtonDown(const MouseButtonEventArgs& e) override;
    void OnMouseLeftButtonUp(const MouseButtonEventArgs& e) override;
    void OnMouseMove(const MouseEventArgs& e) override;
    //@}
    
    /// From Control
    //@{
    void UpdateVisualStates() override;
    //@}

    /// Event handlers
    //@{
    virtual void OnClick();
    virtual void OnIsPressedChanged(const DependencyPropertyChangedEventArgs& e);
    //@}

private:
    /// Controls if the Space key has been pressed
    NsBool mSpaceKeydown;
    
    /// Controls if the left mouse button is down
    NsBool mLeftButtonDown;

    /// Mantains the CanExecute state
    NsBool mCanExecute;

    NS_DECLARE_REFLECTION(BaseButton, ContentControl)
};

NS_WARNING_POP

}
}


#endif
