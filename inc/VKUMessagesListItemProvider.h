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
#include <FUiCtrlIListViewItemProvider.h>
#include <FBase.h>

class VKUMessagesListItemProvider;

#include "VKU.h"
#include "../src/api/VKUApi.h"
#include "AppResourceId.h"
#include "MessageBubble.h"
#include "DialogHistoryListener.h"


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

	// custom
	void SetMessagesJson(Tizen::Web::Json::JsonObject *json);
	void RequestData(const Tizen::Base::String userId);

	DialogHistoryListener* GetListener();
	void SetListener(DialogHistoryListener * apListener);

private:
	Tizen::Web::Json::JsonObject* responseJson;
	Tizen::Web::Json::JsonArray* messagesJson;
	DialogHistoryListener* pListener;
};

#endif /* VKUMESSAGESLISTITEMPROVIDER_H_ */
