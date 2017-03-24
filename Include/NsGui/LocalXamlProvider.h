////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LOCALXAMLPROVIDER_H__
#define __GUI_LOCALXAMLPROVIDER_H__


#include <Noesis.h>
#include <NsGui/CoreApi.h>
#include <NsGui/XamlProvider.h>

#include <limits.h>


namespace Noesis
{
namespace Gui
{

NS_WARNING_PUSH
NS_MSVC_WARNING_DISABLE(4251 4275)

////////////////////////////////////////////////////////////////////////////////////////////////////
/// A XAML provider that searches in local directories
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API LocalXamlProvider: public XamlProvider
{
public:
    LocalXamlProvider(const NsChar* rootPath);

private:
    /// From XamlProvider
    //@{
    Ptr<Core::Stream> LoadXaml(const NsChar* filename) override;
    //@}

private:
    NsChar mRootPath[PATH_MAX];
};

NS_WARNING_POP

}
}

#endif
