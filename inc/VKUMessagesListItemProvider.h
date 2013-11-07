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
#include "RichTextPanel.h"
#include <FUiCtrlIListViewItemProvider.h>


class VKUMessagesListItemProvider :
	public Tizen::Ui::Controls::ITableViewItemProvider {
public:
	VKUMessagesListItemProvider();
	virtual ~VKUMessagesListItemProvider();

	// ITableViewItemProvider
	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int itemIndex, int itemWidth);
	virtual bool DeleteItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual void UpdateItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual int GetDefaultItemHeight(void);

	void SetMessagesJson(Tizen::Web::Json::JsonObject *json);

private:
	Tizen::Web::Json::JsonObject* responseJson;
	Tizen::Web::Json::JsonArray* messagesJson;
};

#endif /* VKUMESSAGESLISTITEMPROVIDER_H_ */
