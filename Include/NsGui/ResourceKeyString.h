////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1215]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_RESOURCEKEYSTRING_H__
#define __GUI_RESOURCEKEYSTRING_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/String.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IResourceKey.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A string being used as a resource dictionary key.
/// Example:
///     <ResourceDictionary>
///         <SolidColorBrush x:Key="DisabledForegroundBrush" Color="Black"/>
///     </ResourceDictionary>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ResourceKeyString: public Core::BaseComponent, public IResourceKey
{
public:
    ResourceKeyString();
    ~ResourceKeyString();
    
    // Creates a ResourceKeyString with the string passed as parameter
    static Ptr<ResourceKeyString> Create(const NsChar* str);

    /// Safe version of Create function that could return null
    static Ptr<ResourceKeyString> TryCreate(const NsChar* str);
    
    // Converter helper
    static NsBool TryParse(const NsChar*, Ptr<ResourceKeyString>& result);

    /// Gets the resource key string
    const NsChar* Get() const;

    /// From IResourceKey
    //@{
    using BaseComponent::Equals;
    NsBool Equals(const IResourceKey* resourceKey) const override;
    NsBool IsLessThan(const IResourceKey* resourceKey) const override;
    NsString GetStr() const override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    /// From BaseRefCounted
    //@{
    NsInt32 OnDestroy() const override;
    //@}

private:
    const NsString* mString;

    NS_DECLARE_REFLECTION(ResourceKeyString, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif