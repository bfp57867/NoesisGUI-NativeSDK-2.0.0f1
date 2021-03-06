////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_BASEDICTIONARY_H__
#define __GUI_BASEDICTIONARY_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/IDictionary.h>
#include <NsGui/INotifyDictionaryChanged.h>
#include <NsCore/ReflectionDeclare.h>
#include <NsCore/Delegate.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Base class for dictionaries
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API BaseDictionary: public Core::BaseComponent, public IDictionary,
    public INotifyDictionaryChanged
{
public:
    virtual ~BaseDictionary() = 0;

    /// Removes listeners subscribed to DictionaryChanged event
    void RemoveDictionaryChangedListeners();

    /// From INotifyDictionaryChanged
    //@{
    NotifyDictionaryChangedEventHandler& DictionaryChanged();
    //@}

protected:
    NotifyDictionaryChangedEventHandler mDictionaryChanged;

    NS_DECLARE_REFLECTION(BaseDictionary, Core::BaseComponent)
};

NS_WARNING_POP

}
}

#endif