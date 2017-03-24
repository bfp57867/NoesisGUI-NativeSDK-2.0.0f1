////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASECOMMAND_H__
#define __GUI_BASECOMMAND_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/ICommand.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Delegate.h>
#include <NsCore/Symbol.h>

namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for commands. *Commands* allows you to define actions in one place and then refer to
/// them from all your user interface controls like menu items, toolbar or buttons. Examples of
/// commands are the *Copy*, *Cut*, and *Paste* operations found on many applications. Applications
/// often expose these actions through many mechanisms simultaneously: *MenuItems* in a Menu,
/// *MenuItems* on a ContextMenu, *Buttons* on a ToolBar, *keyboard shortcuts* and so on.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseCommand: public Core::BaseComponent, public ICommand
{
public:
    BaseCommand(NsSymbol name = NsSymbol::Null(), const Core::TypeClass* owner = 0);
    virtual ~BaseCommand() = 0;

    // From ICommand
    //@{
    Core::Symbol GetName() const override;
    const Core::TypeClass* GetOwnerType() const override;
    EventHandler& CanExecuteChanged() override;
    NsBool CanExecute(Core::BaseComponent* param) const override;
    void Execute(Core::BaseComponent* param) const override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

private:
    NsSymbol mName;
    const Core::TypeClass* mOwnerType;

    EventHandler mCanExecuteChanged;

    NS_DECLARE_REFLECTION(BaseCommand, Core::BaseComponent)
};

NS_WARNING_POP

}
}


#endif
