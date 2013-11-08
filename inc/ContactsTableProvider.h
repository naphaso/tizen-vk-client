/*
 * ContactsTableProvider.h
 *
 *  Created on: Nov 8, 2013
 *      Author: igorglotov
 */

#ifndef CONTACTSTABLEPROVIDER_H_
#define CONTACTSTABLEPROVIDER_H_

#include <FUi.h>
#include <FUiCtrlIGroupedTableViewItemProvider.h>
#include "RoundedAvatar.h"

class ContactsTableProvider: public Tizen::Ui::Controls::IGroupedTableViewItemProvider {
public:
	ContactsTableProvider();
	virtual ~ContactsTableProvider();

	virtual int GetGroupCount(void) = 0;

	// IGroupedTableViewItemProvider
	virtual int GetItemCount(int groupIndex);
	virtual TableViewGroupItem* CreateGroupItem(int groupIndex, int itemWidth);
	virtual bool DeleteGroupItem(int groupIndex, TableViewGroupItem* pItem);
	virtual void UpdateGroupItem(int groupIndex, TableViewGroupItem* pItem);
	virtual TableViewItem* CreateItem(int groupIndex, int itemIndex,
			int itemWidth);
	virtual bool DeleteItem(int groupIndex, int itemIndex,
			TableViewItem* pItem);
	virtual void UpdateItem(int groupIndex, int itemIndex,
			TableViewItem* pItem);
	virtual int GetDefaultGroupItemHeight(void);
	virtual int GetDefaultItemHeight(void);

	// custom
	void SetUsersJson(Tizen::Web::Json::JsonObject *object);

};

#endif /* CONTACTSTABLEPROVIDER_H_ */
