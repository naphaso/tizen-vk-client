/*
 * DialogsTableProvider.h
 *
 *  Created on: Nov 11, 2013
 *      Author: igorglotov
 */

#ifndef DIALOGSTABLEPROVIDER_H_
#define DIALOGSTABLEPROVIDER_H_

#include <FUi.h>
#include <FBase.h>
#include <FWebJson.h>

#include "RoundedAvatar.h"
#include "JsonParseUtils.h"
#include "TimeUtils.h"

class DialogsTableProvider:
	public Tizen::Ui::Controls::ITableViewItemProvider {
public:
	DialogsTableProvider();
	virtual ~DialogsTableProvider();

	// ITableViewItemProvider
	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int itemIndex, int itemWidth);
	virtual bool DeleteItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual void UpdateItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual int GetDefaultItemHeight(void);

	void SetDialogsJson(Tizen::Web::Json::JsonObject* obj);

private:
	Tizen::Web::Json::JsonObject* responseJson;
	Tizen::Web::Json::JsonArray* dialogsJson;
//	DialogHistoryListener* pListener;
};

#endif /* DIALOGSTABLEPROVIDER_H_ */
