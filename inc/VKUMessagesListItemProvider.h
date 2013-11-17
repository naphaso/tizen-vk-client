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
	void RequestData();
	Tizen::Base::Collection::ArrayList * GetMessageElementsN(const Tizen::Web::Json::JsonObject *pMessageJson, int itemWidth);


	DialogHistoryListener* GetListener();
	void SetListener(DialogHistoryListener * apListener);
	void SetUserJson(Tizen::Web::Json::JsonObject* json);
private:
	Tizen::Web::Json::JsonObject* responseJson;
	Tizen::Web::Json::JsonObject* userJson;
	Tizen::Web::Json::JsonArray* messagesJson;
	DialogHistoryListener* pListener;

};

#endif /* VKUMESSAGESLISTITEMPROVIDER_H_ */
