////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_NAMESCOPE_H__
#define __GUI_NAMESCOPE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/INameScope.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/HashMap.h>
#include <NsCore/Delegate.h>
#include <NsCore/String.h>


NS_CFORWARD(Gui, DependencyObject)
NS_CFORWARD(Gui, DependencyProperty)


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// NameScope. Store relationships between the XAML defined names of objects and their instances.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API NameScope: public Core::BaseComponent, public INameScope
{
public:
    /// Constructor
    NameScope();
    
    /// Destructor
    ~NameScope();

    /// Gets the attached NameScope property
    static NameScope* GetNameScope(const DependencyObject* element);
    /// Sets the attached NameScope property
    static void SetNameScope(DependencyObject* element, NameScope* nameScope);

    /// Finds the name of an object if it is registered in the NameScope
    /// \return Null if object was not found. Otherwise it returns the registration name
    /// \remarks This is a slow search
    const NsChar* FindObject(Core::BaseComponent* obj) const;

    /// Calls the delegate for each named object registered in the NameScope
    typedef Noesis::Core::Delegate<void (const NsChar*, Core::BaseComponent*, void*)>
        EnumNamedObjectsDelegate;
    void EnumNamedObjects(const EnumNamedObjectsDelegate& delegate, void* context = 0) const;

    /// From INameScope
    //@{
    Core::BaseComponent* FindName(const NsChar* name) const override;
    void RegisterName(const NsChar* name, Core::BaseComponent* obj) override;
    void UnregisterName(const NsChar* name) override;
    void UpdateName(const NsChar* name, Core::BaseComponent* obj) override;
    INameScope::ChangedDelegate& NameScopeChanged() override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

public:
    /// Dependency properties
    //@{
    static const DependencyProperty* NameScopeProperty; // attached property
    //@}

protected:
    NsInt32 OnDestroy() const override;

private:
    typedef NsHashMap<NsString, Core::BaseComponent*> NameObjectMap;

    NameObjectMap mNamedObjects;
    mutable Core::nstl::pair<NsString, Core::BaseComponent*> mKeyVal;

    ChangedDelegate mChanged;

    NS_DECLARE_REFLECTION(NameScope, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif
