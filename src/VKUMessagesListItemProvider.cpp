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
using namespace Tizen::Ui;

static const int LIST_HEIGHT = 10000;

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

	MessageBubble* pMessageBubble;
	Panel* placeholder;
	VerticalBoxLayout placeholderLayout;

	JsonObject *itemObject;
	IJsonValue *itemValue;
	IJsonValue *bodyValue;
	IJsonValue *outValue;
	TableViewItem* pItem;
	JsonNumber outNumber;

	String messageText(L"no text????");
	int out = 0;

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

	static const String outConst(L"out");
	if (itemObject->GetValue(&outConst, outValue) == E_SUCCESS) {
		if (outValue->GetType() == JSON_TYPE_NUMBER) {
			outNumber = *static_cast<JsonNumber *>(outValue);
			out = outNumber.ToInt();
		}
	}


	// create rich text panel
	AppLog("Message is %d == out", out);
	pMessageBubble = new MessageBubble();
	pMessageBubble->SetMessage(messageText, out);
	r = pMessageBubble->Construct(Dimension(itemWidth, LIST_HEIGHT));
	TryCatch(r == E_SUCCESS, , "Failed Construct RichTextPanel");
	AppLog("RTPanel created and constructed");

	placeholderLayout.Construct(VERTICAL_DIRECTION_UPWARD);
	// create placeholder
	placeholder = new Panel();
	r = placeholder->Construct(placeholderLayout, Rectangle(0, 0, itemWidth, pMessageBubble->GetHeight()));
	TryCatch(r == E_SUCCESS, , "Failed Construct RichTextPanel");

	// add bubble to placeholder
	placeholder->AddControl(pMessageBubble);
	if (out == 1) {
		placeholderLayout.SetHorizontalAlignment(*pMessageBubble, LAYOUT_HORIZONTAL_ALIGN_RIGHT);
	}

	// create table item
	pItem = new TableViewItem();
	r = pItem->Construct(Dimension(itemWidth, pMessageBubble->GetHeight() + 2*BUBBLE_VERTICAL_MARGIN));
	TryCatch(r == E_SUCCESS, , "Failed GetAt");

	// add rich text panel to table item
	r = pItem->AddControl(placeholder);
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
