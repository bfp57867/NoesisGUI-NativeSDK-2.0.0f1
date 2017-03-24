////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASESETTER_H__
#define __GUI_BASESETTER_H__


#include <Noesis.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IUITreeNode.h>


NS_CFORWARD(Gui, BaseSetter)


namespace Noesis
{
namespace Gui
{

template<class T> class TypedCollection;
typedef Noesis::Gui::TypedCollection<Noesis::Gui::BaseSetter> BaseSetterCollection;

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Represents the base class for value setters.
///
/// http://msdn.microsoft.com/en-us/library/system.windows.setterbase.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseSetter: public Core::BaseComponent, public IUITreeNode
{
public:
    NS_DISABLE_COPY(BaseSetter)

    BaseSetter();
    virtual ~BaseSetter() = 0;

    static void SealSetters(BaseSetterCollection* setters, NsBool allowTargetName);

    // Seals the setters
    virtual void Seal(NsBool allowTargetName);

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
    NsBool mIsSealed;

private:
    IUITreeNode* mOwner;

    NS_DECLARE_REFLECTION(BaseSetter, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif
