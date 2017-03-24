////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_ANIMATABLE_H__
#define __GUI_ANIMATABLE_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/Freezable.h>
#include <NsGui/IUITreeNode.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Abstract class that provides animation support.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.media.animation.animatable.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API Animatable: public Freezable, public IUITreeNode
{
public:
    /// Constructor
    Animatable();

    /// Destructor
    virtual ~Animatable() = 0;

    /// From IUITreeNode
    //@{
    IUITreeNode* GetNodeParent() const override;
    void SetNodeParent(IUITreeNode* parent) override;
    Core::BaseComponent* FindNodeResource(IResourceKey* key,
        NsBool fullElementSearch) const override;
    Core::BaseComponent* FindNodeName(const NsChar* name) const override;
    ObjectWithNameScope FindNodeNameAndScope(const NsChar* name) const override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

protected:
    /// From DependencyObject
    //@{
    void OnObjectValueSet(Core::BaseComponent* oldValue, Core::BaseComponent* newValue) override;
    //@}

private:
    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(Animatable, Freezable)
};

NS_WARNING_POP

}
}


#endif