////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_EXPRESSION_H__
#define __GUI_EXPRESSION_H__


#include <Noesis.h>
#include <NsGui/DependencySystemApi.h>
#include <NsGui/IExpression.h>
#include <NsCore/BaseComponent.h>
#include <NsCore/ReflectionDeclare.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base implementation for all expressions.
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_DEPENDENCYSYSTEM_API Expression: public Core::BaseComponent, public IExpression
{
public:
    /// Constructor
    Expression();

    /// Destructor
    virtual ~Expression() = 0;

    /// From IExpression
    //@{
    Ptr<Core::BaseComponent> Evaluate() const override;
    Ptr<IExpression> Reapply(DependencyObject* targetObject,
        const DependencyProperty* targetProperty) const override;
    BeforeSetAction BeforeSet(DependencyObject* obj, const DependencyProperty* prop,
        const void* value, NsBool valueHasChanged) override;
    void AfterSet(DependencyObject* obj, const DependencyProperty* prop, const void* value,
        NsBool valueHasChanged) override;
    //@}

    NS_IMPLEMENT_INTERFACE_FIXUP

    NS_DECLARE_REFLECTION(Expression, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif