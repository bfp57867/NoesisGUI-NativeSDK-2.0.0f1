////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
// [CR #1215]
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_RESOURCEKEYTYPE_H__
#define __GUI_RESOURCEKEYTYPE_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IResourceKey.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A Type being used as a resource dictionary key.
/// Example:
///     <ResourceDictionary>
///         <SolidColorBrush x:Key="{x:Type Button}" Color="Red"/>
///     </ResourceDictionary>
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ResourceKeyType: public Core::BaseComponent, public IResourceKey
{
public:
    ResourceKeyType();
    ~ResourceKeyType();
    
    // Creates a ResourceKeyType with the type passed as parameter
    static Ptr<ResourceKeyType> Create(const Core::Type* key);

    // Converter helper
    static NsBool TryParse(const NsChar* str, Ptr<ResourceKeyType>& result);

    /// Gets type key
    const Core::Type* Get() const;

    /// From IResourceKey
    //@{
    using BaseComponent::Equals;
    NsBool Equals(const IResourceKey* resourceKey) const override;
    NsBool IsLessThan(const IResourceKey* resourceKey) const override;
    NsString GetStr() const override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

private:
    const Core::Type* mType;

    NS_DECLARE_REFLECTION(ResourceKeyType, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif