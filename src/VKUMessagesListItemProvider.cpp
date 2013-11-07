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

static const int LIST_HEIGHT = 200;

VKUMessagesListItemProvider::VKUMessagesListItemProvider() {
	messagesJson = null;
}

VKUMessagesListItemProvider::~VKUMessagesListItemProvider() {
	AppLog("Destruction of VKUMessagesListItemProvider");

	delete messagesJson;
	delete responseJson;
}

// IListViewItemProvider
int VKUMessagesListItemProvider::GetItemCount() {
	AppLog("GetItemCount call");
	if (messagesJson == null)
		return 0;

	return messagesJson->GetCount();
}

TableViewItem* VKUMessagesListItemProvider::CreateItem(int index, int itemWidth) {
	result r;
	AppLog("Create item");

	RichTextPanel* pRtPanel;
	JsonObject *itemObject;
	IJsonValue *itemValue;
	IJsonValue *bodyValue;
	TableViewItem* pItem;

	String messageText(L"no text????");

	// reverse list
	int reversedIndex = GetItemCount()-1 - index;
	AppLog("Item %d of %d", reversedIndex, GetItemCount());

	// get message string
	r = messagesJson->GetAt(reversedIndex, itemValue);
	TryCatch(r == E_SUCCESS, , "Failed GetAt");
	itemObject = static_cast<JsonObject *>(itemValue);

	static const String bodyConst(L"body");
	if (itemObject->GetValue(&bodyConst, bodyValue) == E_SUCCESS) {
		if (bodyValue->GetType() == JSON_TYPE_STRING) {
			messageText = *static_cast<JsonString *>(bodyValue);
		}
	}

	// create rich text panel
	AppLog("RTPanel");
	pRtPanel = new RichTextPanel();
	r = pRtPanel->Construct(Dimension(itemWidth, 200), messageText);
	TryCatch(r == E_SUCCESS, , "Failed Construct RichTextPanel");
	AppLog("RTPanel created and constructed");

	// create table item
	pItem = new TableViewItem();
	r = pItem->Construct(Dimension(itemWidth, pRtPanel->GetHeight()));
	TryCatch(r == E_SUCCESS, , "Failed GetAt");

	// add rich text panel to table item
	r = pItem->AddControl(pRtPanel);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	AppLog("Returning item");
	return pItem;

	CATCH:
	    AppLogException("$${Function:CreateItem} is failed.", GetErrorMessage(r));
	    return null;
}

bool VKUMessagesListItemProvider::DeleteItem(int index, TableViewItem* pItem) {
	delete pItem;
	return true;
}

void VKUMessagesListItemProvider::UpdateItem(int itemIndex, TableViewItem* pItem) {
	result r = E_SUCCESS;

//	RichTextPanel * pRtPanel = new RichTextPanel();
//
//	int reversedIndex = GetItemCount()-1 - itemIndex;
//	IJsonValue *itemValue;
//	r = messagesJson->GetAt(reversedIndex, itemValue);
//	TryCatch(r == E_SUCCESS, , "Failed GetAt");
//
//	JsonObject *itemObject = static_cast<JsonObject *>(itemValue);
//
//	String messageText(L"no text????");
//
//	IJsonValue *bodyValue;
//	static const String bodyConst(L"body");
//	if (itemObject->GetValue(&bodyConst, bodyValue) == E_SUCCESS) {
//		if (bodyValue->GetType() == JSON_TYPE_STRING) {
//			messageText = *static_cast<JsonString *>(bodyValue);
//		}
//	}
//
//	r = pRtPanel->Construct(Dimension(200, 200), Construct);
//	TryCatch(r == E_SUCCESS, , "Failed Construct RichTextPanel");
//
//	r = pItem->AddControl(pRtPanel);
//	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	SetLastResult(r);
	return;

	CATCH:
	    AppLogException("$${Function:UpdateItem} is failed.", GetErrorMessage(r));
	    SetLastResult(r);
}

int VKUMessagesListItemProvider::GetDefaultItemHeight() {
	return LIST_HEIGHT;
}

void VKUMessagesListItemProvider::SetMessagesJson(JsonObject *json) {
	result r = E_SUCCESS;

	responseJson = json;
	AppLog("Setting messaging json");

	IJsonValue *response;
	static const String responseConst(L"response");
	r = responseJson->GetValue(&responseConst, response);
	TryCatch(r == E_SUCCESS, , "Failed GetValue");


	IJsonValue *items;
	static const String itemsConst(L"items");
	r = (static_cast<JsonObject *>(response))->GetValue(&itemsConst, items);
	TryCatch(r == E_SUCCESS, , "Failed GetValue");

	messagesJson = static_cast<JsonArray *>(items);
	AppLog("Assigned %d items", messagesJson->GetCount());

	SetLastResult(r);
	return;

	CATCH:
	    AppLogException("$${Function:UpdateItem} is failed.", GetErrorMessage(r));
	    SetLastResult(r);
}
