/*
 * VKUMessagesListItemProvider.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: igorglotov
 */

#include "VKUMessagesListItemProvider.h"
#include "JsonParseUtils.h"
#include "TimeUtils.h"

using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;
using namespace Tizen::Base;
//using namespace Tizen::App;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Ui;

static const int LIST_HEIGHT = 10000;
static const int TIMESTAMP_TEXT_COLOR = 0x6d7175;
#define USE_CACHE 1

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
	RelativeLayout itemLayout;

	JsonObject *itemObject;
	IJsonValue *itemValue;
	IJsonValue *bodyValue;
	IJsonValue *outValue;
	TableViewItem* pItem;
	JsonNumber outNumber;

	Label *pTimeStamp;
	String timespampText;
	int timestampValue;

	String messageText(L"no text????");
	int out = 0;

	// reverse list
	int reversedIndex = GetItemCount()-1 - index;
	AppLog("Item %d of %d", reversedIndex, GetItemCount());

	// get message string
	r = messagesJson->GetAt(reversedIndex, itemValue);
	TryCatch(r == E_SUCCESS, , "Failed GetAt");
	itemObject = static_cast<JsonObject *>(itemValue);

	JsonParseUtils::GetString(*itemObject, L"body", messageText);
	JsonParseUtils::GetInteger(*itemObject, L"out", out);
	JsonParseUtils::GetInteger(*itemObject, L"date", timestampValue);

	TimeUtils::GetDialogsTime(timestampValue, timespampText);

	// create rich text panel
	AppLog("Message is %d == out", out);
	pMessageBubble = new MessageBubble();
	pMessageBubble->SetMessage(messageText, out);
	r = pMessageBubble->Construct(Dimension(itemWidth, LIST_HEIGHT));
	TryCatch(r == E_SUCCESS, , "Failed Construct RichTextPanel");
	AppLog("RTPanel created and constructed");

//	placeholderLayout.Construct(VERTICAL_DIRECTION_UPWARD);
	itemLayout.Construct();

	// timestamp label
	pTimeStamp = new Label();
	pTimeStamp->Construct(Rectangle(0, 0, 100, 28), timespampText);
	pTimeStamp->SetTextConfig(28, LABEL_TEXT_STYLE_NORMAL);
	pTimeStamp->SetTextColor(Color(TIMESTAMP_TEXT_COLOR, false));

	// create table item
	pItem = new TableViewItem();
	r = pItem->Construct(itemLayout, Dimension(itemWidth, pMessageBubble->GetHeight() + 2*BUBBLE_VERTICAL_MARGIN));
	TryCatch(r == E_SUCCESS, , "Failed GetAt");

	// add rich text panel to table item
	r = pItem->AddControl(pMessageBubble);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");
	r = pItem->AddControl(pTimeStamp);

	itemLayout.SetCenterAligned(*pMessageBubble, CENTER_ALIGN_VERTICAL);
	itemLayout.SetHorizontalFitPolicy(*pTimeStamp, FIT_POLICY_CONTENT);

	if (out == 1) {
		itemLayout.SetRelation(*pMessageBubble, *pItem, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
		itemLayout.SetMargin(*pMessageBubble, 0, 10, 0, 0);

		itemLayout.SetRelation(*pTimeStamp, *pMessageBubble, RECT_EDGE_RELATION_RIGHT_TO_LEFT);
		itemLayout.SetRelation(*pTimeStamp, *pItem, RECT_EDGE_RELATION_BOTTOM_TO_BOTTOM);
		itemLayout.SetMargin(*pTimeStamp, 0, 10, 0, 30);
	} else {
		itemLayout.SetRelation(*pMessageBubble, *pItem, RECT_EDGE_RELATION_LEFT_TO_LEFT);
		itemLayout.SetMargin(*pMessageBubble, 10, 0, 0, 0);

		itemLayout.SetRelation(*pTimeStamp, *pMessageBubble, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
		itemLayout.SetRelation(*pTimeStamp, *pItem, RECT_EDGE_RELATION_BOTTOM_TO_BOTTOM);
		itemLayout.SetMargin(*pTimeStamp, 10, 0, 0, 30);
	}

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

	// save cache
	int userId;
	JsonParseUtils::GetInteger(*userJson, L"id", userId);
	String cacheFile(VKUApp::GetInstance()->GetCacheDir() + "dialog" + Integer::ToString(userId) + ".json");
	JsonWriter::Compose(json, cacheFile);

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

void VKUMessagesListItemProvider::SetListener(DialogHistoryListener * apListener) {
	pListener = apListener;
}

DialogHistoryListener* VKUMessagesListItemProvider::GetListener() {
	return pListener;
}

void VKUMessagesListItemProvider::SetUserJson(JsonObject *json) {
	userJson = json;
}

void VKUMessagesListItemProvider::RequestData() {
	TryReturnVoid(pListener != null, "IAPIRequestListener cannot be null, response will be omitted");
	int userId;
	JsonParseUtils::GetInteger(*userJson, L"id", userId);

	VKUApi::GetInstance().CreateRequest("messages.getHistory", GetListener())->Put(
			L"count", L"20")->Put(L"user_id", Integer::ToString(userId))->Submit();
}
