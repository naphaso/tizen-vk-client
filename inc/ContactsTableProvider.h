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
#include <FWebJson.h>
#include "RoundedAvatar.h"

class ContactsTableProvider: public Tizen::Ui::Controls::IGroupedTableViewItemProvider {
public:
	ContactsTableProvider();
	virtual ~ContactsTableProvider();

	virtual int GetGroupCount(void);

	// IGroupedTableViewItemProvider
	virtual int GetItemCount(int groupIndex);
	virtual Tizen::Ui::Controls::TableViewGroupItem* CreateGroupItem(int groupIndex, int itemWidth);
	virtual bool DeleteGroupItem(int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem);
	virtual void UpdateGroupItem(int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem);
	virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int groupIndex, int itemIndex,
			int itemWidth);
	virtual bool DeleteItem(int groupIndex, int itemIndex,
			Tizen::Ui::Controls::TableViewItem* pItem);
	virtual void UpdateItem(int groupIndex, int itemIndex,
			Tizen::Ui::Controls::TableViewItem* pItem);
	virtual int GetDefaultGroupItemHeight(void);
	virtual int GetDefaultItemHeight(void);

	// custom
	void SetUsersJson(Tizen::Web::Json::JsonObject *object);

private:
	Tizen::Web::Json::JsonObject * contactsObject;
	Tizen::Web::Json::JsonArray * contactsArray;

};

#endif /* CONTACTSTABLEPROVIDER_H_ */
