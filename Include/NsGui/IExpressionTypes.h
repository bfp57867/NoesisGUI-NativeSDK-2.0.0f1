////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_IEXPRESSIONTYPES_H__
#define __GUI_IEXPRESSIONTYPES_H__


#include <Noesis.h>


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
enum BeforeSetAction
{
    /// Execute method and delete expression (updating cached value). This is the common
    /// return value for expression that do not require the BeforeSet call
    BeforeSetAction_Delete = 0,
    BeforeSetAction_Default = 0,
    /// Execute method and update cached value (maintain expression)
    BeforeSetAction_Maintain = 1
};

}
}

#endif
