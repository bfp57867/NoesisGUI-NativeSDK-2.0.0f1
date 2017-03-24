////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_PROPERTYPATH_H__
#define __GUI_PROPERTYPATH_H__


#include <Noesis.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/String.h>
#include <NsCore/Ptr.h>
#include <NsCore/Symbol.h>
#include <NsCore/Vector.h>
#include <NsCore/DelegateForward.h>
#include <NsGui/CoreApi.h>


NS_CFORWARD(Core, TypeProperty)
NS_CFORWARD(Gui, Collection)
NS_CFORWARD(Gui, DependencyProperty)
NS_CFORWARD(Gui, CollectionView)
NS_IFORWARD(Gui, IResourceKey)
class Noesis_PropertyPathTest;


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
struct NS_GUI_CORE_API PathElement
{
    PathElement();
    PathElement(const PathElement& pe);
    ~PathElement();
    
    PathElement& operator=(const PathElement& pe);

    // If you add a new member here, remember to add the proper code in copy ctor and operator=
    Ptr<Core::BaseComponent> source;
    Ptr<CollectionView> collection;
    const Core::TypeProperty* property;
    const DependencyProperty* dp;
    NsInt index;
    Ptr<IResourceKey> key;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// PropertyPath
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API PropertyPath: public Core::BaseComponent
{
public:
    PropertyPath();
    PropertyPath(const NsChar* str);
    PropertyPath(const DependencyProperty* dp);
    ~PropertyPath();

    /// Creates and caches a property path that points to a property
    /// Returns Null if path does not corresponds to a valid property name
    static PropertyPath* Create(const NsChar* path);

    /// Gets or sets path
    //@{
    const NsChar* GetPath() const;
    void SetPath(const NsChar* path);
    //@}

    /// Returns false if path cannot be resolved for the provided source
    typedef NsVector<PathElement> Elements;
    NsBool GetPathElements(BaseComponent* source, NsBool insertLastValue, Elements& elements) const;

    /// Returns false if path cannot be resolved for the provided source
    typedef Noesis::Core::Delegate<void (const PathElement&, void*)> EnumPathElementsDelegate;
    NsBool EnumPathElements(BaseComponent* source, NsBool enumLastValue,
        const EnumPathElementsDelegate& delegate, void* context = 0) const;

private:
    void AddPathElements(const PathElement& pathElement, void* context) const;
    NsBool UpdatePathItems() const;
    const NsString& RebuildPath() const;

private:
    friend class ::Noesis_PropertyPathTest;

    mutable NsString mPath;

    struct PathItem
    {
        NsBool slash;
        NsSymbol owner;
        NsSymbol prop;

        struct IndexKey
        {
            NsInt index;
            NsString key;

            /// Constructor
            IndexKey();
        };

        NsVector<IndexKey> keys;

        /// Constructor
        PathItem();
    };

    typedef NsVector<PathItem> PathItems;
    mutable PathItems mPathItems;

    NS_DECLARE_REFLECTION(PropertyPath, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif
