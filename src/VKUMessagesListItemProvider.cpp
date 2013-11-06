/*
 * VKUMessagesListItemProvider.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: igorglotov
 */

#include "VKUMessagesListItemProvider.h"

using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui::Scenes;

static const int LIST_HEIGHT = 100;

VKUMessagesListItemProvider::VKUMessagesListItemProvider() {
	// TODO Auto-generated constructor stub
	messagesJson = null;
}

VKUMessagesListItemProvider::~VKUMessagesListItemProvider() {
	// TODO Auto-generated destructor stub
}

// IListViewItemProvider
int VKUMessagesListItemProvider::GetItemCount() {
	if (messagesJson == null)
		return 0;

	return messagesJson->GetCount();
}

// FIXME: trycatch posible errors
ListItemBase* VKUMessagesListItemProvider::CreateItem(int index, int itemWidth) {
	CustomItem* item = new CustomItem();
	item->Construct(Dimension(itemWidth, LIST_HEIGHT), LIST_ANNEX_STYLE_NORMAL);

	AppLog("Getting item %d", index);
	IJsonValue *itemValue;
	messagesJson->GetAt(index, itemValue);
	JsonObject *itemObject = static_cast<JsonObject *>(itemValue);

	String messageText(L"no text????");

	AppLog("Getting content of item %d", index);
	IJsonValue *bodyValue;
	static const String bodyConst(L"body");
	if (itemObject->GetValue(&bodyConst, bodyValue) == E_SUCCESS) {
		if (bodyValue->GetType() == JSON_TYPE_STRING) {
			messageText = *static_cast<JsonString *>(bodyValue);
		}
	}

	item->AddElement(
			Rectangle(0, 0, itemWidth,
					LIST_HEIGHT / 2), 4242, messageText);

	return item;
}

bool VKUMessagesListItemProvider::DeleteItem(int index, ListItemBase* pItem, int itemWidth) {
	delete pItem;
	return true;
}

void VKUMessagesListItemProvider::SetMessagesJson(JsonObject *json) {
	responseJson = json;
	AppLog("Setting messaging json");

	IJsonValue *response;
	static const String responseConst(L"response");
	responseJson->GetValue(&responseConst, response);


	IJsonValue *items;
	static const String itemsConst(L"items");
	(static_cast<JsonObject *>(response))->GetValue(&itemsConst, items);

	messagesJson = static_cast<JsonArray *>(items);
	AppLog("Assigned %d items", messagesJson->GetCount());
}
