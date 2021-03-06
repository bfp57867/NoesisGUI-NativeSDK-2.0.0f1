////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_DEPENDSONATTRIBUTEMETADATA_H__
#define __GUI_DEPENDSONATTRIBUTEMETADATA_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/TypeMetaData.h>
#include <NsCore/Symbol.h>
#include <NsGui/CoreApi.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// DependsOnAttributeMetaData. Stores information for a property about another property that needs
/// to be evaluated first.
/// Note: A class can't have both DependsOnAttributeMetaData and ContentPropertyMetaData
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API DependsOnAttributeMetaData: public Core::TypeMetaData
{
public:
    /// Constructor
    DependsOnAttributeMetaData(const NsChar* propertyName);

    /// Constructor
    DependsOnAttributeMetaData(NsSymbol propertyName);

    /// Gets content property
    NsSymbol GetDependsOnProperty() const;

private:
    NsSymbol mDependsOnProperty;

    NS_DECLARE_REFLECTION(DependsOnAttributeMetaData, Core::TypeMetaData)
};

}
}


#endif
