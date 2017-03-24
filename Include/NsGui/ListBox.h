////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __GUI_LISTBOX_H__
#define __GUI_LISTBOX_H__


#include <Noesis.h>
#include <NsGui/Selector.h>
#include <NsGui/Enums.h>
#include <NsCore/ReflectionDeclareEnum.h>


NS_CFORWARD(Gui, ListBoxItem)
NS_IFORWARD(Gui, IList)
NS_SFORWARD(Gui, NotifyCollectionChangedEventArgs)
class Noesis_ListBoxTest;


namespace Noesis
{
namespace Gui
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Contains a list of selectable items. 
///
/// http://msdn.microsoft.com/en-us/library/system.windows.controls.listbox.aspx
////////////////////////////////////////////////////////////////////////////////////////////////////
class NS_GUI_CORE_API ListBox: public Selector
{
public:
    ListBox();
    
    /// Gets the currently selected items
    IList* GetSelectedItems() const;

    /// Gets or sets the selection behavior for a ListBox
    //@{
    SelectionMode GetSelectionMode() const;
    void SetSelectionMode(SelectionMode mode);
    //@}

    /// Select all the items
    void SelectAll();

    /// Clears all of the selected items
    void UnselectAll();

    /// Causes the object to scroll into view. If it is not visible, it is aligned either at the
    /// top or bottom of the viewport
    void ScrollIntoView(Core::BaseComponent* item);

    /// From ItemsControl
    //@{
    Ptr<Panel> GetDefaultItemsPanel() const;
    //@}

public:
    /// Dependency Properties
    //@{
    static const DependencyProperty* SelectedItemsProperty;
    static const DependencyProperty* SelectionModeProperty;
    //@}
    
protected:
    /// From DependencyObject
    //@{
    NsBool OnPropertyChanged(const DependencyPropertyChangedEventArgs& args);
    //@}
    
    /// From Selector
    //@{
    void OnSelectionChanged(const SelectionChangedEventArgs& args);
    NsBool IsMultiSelectEnabled() const;
    //@}

    /// From ItemsControl
    //@{
    Ptr<DependencyObject> GetContainerForItemOverride() const;
    NsBool IsItemItsOwnContainerOverride(Core::BaseComponent* item) const;
    void OnItemsChanged(const NotifyCollectionChangedEventArgs& args);
    //@}

private:
    void SingleSelection(ListBoxItem* item);
    void ToggleSelection(ListBoxItem* item, NsBool multiple);
    void RangeSelection(ListBoxItem* item);

    /// Used by ListBoxItem implementation
    friend class ListBoxItem;
    void ItemSelected(ListBoxItem* lbi);
    void ItemClicked(ListBoxItem* lbi, NsBool toggleSelection);
    void ItemEntered(ListBoxItem* lbi);

    // Used by testing
    friend class ::Noesis_ListBoxTest;
    void ItemClicked(ListBoxItem* lbi, NsBool toggleSelection, NsBool shiftKeyDown,
        NsBool ctrlKeyDown);
    void ItemEntered(ListBoxItem* lbi, NsBool ctrlKeyDown);

private:
    NsInt32 mFirstPressedItem;

    NS_DECLARE_REFLECTION(ListBox, Selector)
};

}
}


#endif
