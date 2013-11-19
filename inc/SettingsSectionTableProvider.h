/*
 * SettingsSectionTableProvider.h
 *
 *  Created on: Nov 19, 2013
 *      Author: igorglotov
 */

#ifndef SETTINGSSECTIONTABLEPROVIDER_H_
#define SETTINGSSECTIONTABLEPROVIDER_H_

#include <FBase.h>
#include <FUi.h>

class SettingsSectionTableProvider:
	public Tizen::Ui::Controls::ISectionTableViewItemProvider,
	public Tizen::Ui::Controls::ISectionTableViewItemEventListener {
public:
	SettingsSectionTableProvider();
	virtual ~SettingsSectionTableProvider();

	// ISectionTableViewItemEventListener
	virtual void OnSectionTableViewItemStateChanged(Tizen::Ui::Controls::SectionTableView& tableView, int sectionIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status);
	virtual void OnSectionTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::SectionTableView& tableView, int sectionIndex, int itemIndex, Tizen::Ui::Controls::TableViewContextItem* pContextItem, bool activated);

	// ISectionTableViewItemProvider
	virtual int GetSectionCount(void);
	virtual int GetItemCount(int sectionIndex);
	virtual bool HasSectionHeader(int sectionIndex);
	virtual bool HasSectionFooter(int sectionIndex);
	virtual Tizen::Base::String GetSectionHeader(int sectionIndex);
	virtual Tizen::Base::String GetSectionFooter(int sectionIndex);
	virtual int GetDefaultItemHeight(void);
	virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int sectionIndex, int itemIndex, int itemWidth);
	virtual bool DeleteItem(int sectionIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual void UpdateItem(int sectionIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);

private:
	Tizen::Ui::Controls::SectionTableView* pSectionTableView;

	Tizen::Base::String GetSectionText(int section, int index);
	Tizen::Ui::Controls::TableViewAnnexStyle GetSectionStyle(int section, int index);
};

#endif /* SETTINGSSECTIONTABLEPROVIDER_H_ */
