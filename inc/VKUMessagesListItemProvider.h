/*
 * VKUMessagesListItemProvider.h
 *
 *  Created on: Nov 5, 2013
 *      Author: igorglotov
 */

#ifndef VKUMESSAGESLISTITEMPROVIDER_H_
#define VKUMESSAGESLISTITEMPROVIDER_H_

#include <FUi.h>
#include <FWebJson.h>
#include "VKU.h"
#include "AppResourceId.h"
#include <FUiCtrlIListViewItemProvider.h>

class VKUMessagesListItemProvider :
	public Tizen::Ui::Controls::IListViewItemProvider {
public:
	VKUMessagesListItemProvider();
	virtual ~VKUMessagesListItemProvider();

	// IListViewItemProvider
	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
	virtual bool DeleteItem(int index, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth);

	// custom functions
	void SetMessagesJson(Tizen::Web::Json::JsonObject *json);

private:
	Tizen::Web::Json::JsonObject* responseJson;
	Tizen::Web::Json::JsonArray* messagesJson;
};

#endif /* VKUMESSAGESLISTITEMPROVIDER_H_ */
