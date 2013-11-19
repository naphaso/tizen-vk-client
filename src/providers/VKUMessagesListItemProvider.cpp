/*
 * VKUMessagesListItemProvider.cpp
 *
 *  Created on: Nov 5, 2013
 *      Author: igorglotov
 */

#include "VKUMessagesListItemProvider.h"
#include "JsonParseUtils.h"
#include "TimeUtils.h"
#include "ImageUtils.h"

#include "MessageTextElement.h"

#include "MessagePhotoElement.h"
#include "MessageVideoElement.h"
#include "MessageWallElement.h"
#include "MessageAudioElement.h"
#include "MessageDocElement.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;


static const int LIST_HEIGHT = 10000;
static const int TIMESTAMP_TEXT_COLOR = 0x6d7175;
static const int LIST_ITEM_UNREAD_COLOR = 0x191f25;
#define USE_CACHE 1

static const wchar_t *PRELOAD_MESSAGES = L"20";

VKUMessagesListItemProvider::VKUMessagesListItemProvider() {
	_messagesJson = null;
}

VKUMessagesListItemProvider::~VKUMessagesListItemProvider() {
	AppLog("Destruction of VKUMessagesListItemProvider");

	delete _messagesJson;
}

result VKUMessagesListItemProvider::Construct(JsonObject *userJson, TableView *tableView) {
	_userJson = userJson;
	_tableView = tableView;

	int userId;
	JsonParseUtils::GetInteger(*userJson, L"id", userId);
	JsonArray *dialogData = static_cast<JsonArray *>(JsonParser::ParseN(VKUApp::GetInstance()->GetCacheDir() + "dialog" + Integer::ToString(userId) + ".json"));
	if(GetLastResult() == E_SUCCESS) {
		_messagesJson = dialogData;
	}

	SetLastResult(E_SUCCESS);
	return E_SUCCESS;
}

// IListViewItemProvider
int VKUMessagesListItemProvider::GetItemCount() {
	AppLog("GetItemCount call");
	if (_messagesJson == null)
		return 0;

	return _messagesJson->GetCount();
}

TableViewItem* VKUMessagesListItemProvider::CreateItem(int index, int itemWidth) {
	result r;
	AppLog("VKUMessagesListItemProvider::CreateItem");

	MessageBubble* pMessageBubble;
	RelativeLayout itemLayout;
	Color bgColor;

	JsonObject *itemObject;
	IJsonValue *itemValue;
	TableViewItem* pItem;
	JsonNumber outNumber;

	ArrayList *pMessageElements;

	Label *pTimeStamp;
	String timespampText;
	int timestampValue;

	String messageText(L"no text????");
	int out = 0, readState = 0;

	// reverse list
	int reversedIndex = _messagesJson->GetCount() - 1 - index;
	AppLog("Item %d of %d", reversedIndex, GetItemCount());

	// get message string
	r = _messagesJson->GetAt(reversedIndex, itemValue);
	TryCatch(r == E_SUCCESS, , "Failed GetAt");
	itemObject = static_cast<JsonObject *>(itemValue);

	JsonParseUtils::GetInteger(*itemObject, L"out", out);
	JsonParseUtils::GetInteger(*itemObject, L"date", timestampValue);
	JsonParseUtils::GetInteger(*itemObject, L"read_state", readState);

	TimeUtils::GetDialogsTime(timestampValue, timespampText);

	// create rich text panel
	AppLog("Message is %d == out", out);
	pMessageBubble = new MessageBubble();
	r = pMessageBubble->Construct(Dimension(itemWidth, LIST_HEIGHT));
	TryCatch(r == E_SUCCESS, , "Failed Construct RichTextPanel");

	pMessageBubble->SetOut(out);
	AppLog("RTPanel created and constructed");
	itemLayout.Construct();

	// get available elements
	pMessageElements = GetMessageElementsN(itemObject, itemWidth);

	// message text element
	for (int i=0; i<pMessageElements->GetCount(); i++) {
		AppLog("Adding element %d to pItem", i);
		MessageElement *pElement = static_cast<MessageElement *>(pMessageElements->GetAt(i));
		pMessageBubble->AddElement(pElement);
		AppLog("Added element %d to pItem", i);
	}

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

	// colors
	if (out == 1 && readState == 0) {
		bgColor = Color(LIST_ITEM_UNREAD_COLOR, false);
	} else {
		bgColor = Color::GetColor(COLOR_ID_BLACK);
	}

	pItem->SetBackgroundColor(bgColor, TABLE_VIEW_ITEM_DRAWING_STATUS_NORMAL);
	pItem->SetBackgroundColor(bgColor, TABLE_VIEW_ITEM_DRAWING_STATUS_PRESSED);
	pItem->SetBackgroundColor(bgColor, TABLE_VIEW_ITEM_DRAWING_STATUS_HIGHLIGHTED);

	pItem->RequestRedraw(true);

	AppLog("Returning item");
	return pItem;

CATCH:
	AppLogException("$${Function:CreateItem} is failed. %s", GetErrorMessage(r));
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

void VKUMessagesListItemProvider::OnTableViewItemStateChanged(
		Tizen::Ui::Controls::TableView& tableView, int itemIndex,
		Tizen::Ui::Controls::TableViewItem* pItem,
		Tizen::Ui::Controls::TableViewItemStatus status) {

	switch(status) {
	case TABLE_VIEW_ITEM_STATUS_SELECTED:
		AppLog("TABLE_VIEW_ITEM_STATUS_HIGHLIGHTED");
		break;
	case TABLE_VIEW_ITEM_STATUS_HIGHLIGHTED:
		AppLog("TABLE_VIEW_ITEM_STATUS_HIGHLIGHTED");
		break;
	case TABLE_VIEW_ITEM_STATUS_CHECKED:
		AppLog("TABLE_VIEW_ITEM_STATUS_CHECKED");
		break;
	case TABLE_VIEW_ITEM_STATUS_UNCHECKED:
		AppLog("TABLE_VIEW_ITEM_STATUS_UNCHECKED");
		break;
	case TABLE_VIEW_ITEM_STATUS_MORE:
		AppLog("TABLE_VIEW_ITEM_STATUS_MORE");
		break;
	}
}


ArrayList * VKUMessagesListItemProvider::GetMessageElementsN(const JsonObject *pMessageJson, int itemWidth) {
	AppLog("enter VKUMessagesListItemProvider::GetMessageElementsN");
	result r;

	// general
	ArrayList* pResultArray;

	// body stuff
	String messageText;
	MessageTextElement *pMessageTextElement;

	// attachs stuff
	IJsonValue *attachs;
	JsonArray * pAttachArray;

	pResultArray = new ArrayList(SingleObjectDeleter);
	r = pResultArray->Construct(1);
	TryCatch(r == E_SUCCESS, , "pResultArray->Construct");

	r = JsonParseUtils::GetString(*pMessageJson, L"body", messageText);
	TryCatch(r == E_SUCCESS, , "JsonParseUtils::GetString body");

	if (messageText.GetLength() != 0) {
		AppLog("Message has text entry, receiving");
		pMessageTextElement = new MessageTextElement();
		pMessageTextElement->Construct(Rectangle(0, 0, itemWidth-200, 10000));
		pMessageTextElement->SetText(messageText);

		pResultArray->Add(pMessageTextElement);
	}


	static const String attachConst(L"attachments");
	r = pMessageJson->GetValue(&attachConst, attachs);

	if (r != E_SUCCESS)
		return pResultArray;

	pAttachArray = static_cast<JsonArray *>(attachs);

	for (int i=0; i<pAttachArray->GetCount(); i++) {
		AppLog("Message has %d attachments, receiving %d", pAttachArray->GetCount(), i);

		IJsonValue *pAttachValue;
		JsonObject *pAttachObject;
		String attachType;

		MessageElement *pMessageElement;

		pAttachArray->GetAt(i, pAttachValue);

		pAttachObject = static_cast<JsonObject *>(pAttachValue);

		JsonParseUtils::GetString(*pAttachObject, L"type", attachType);

		if (attachType == L"photo") {
			AppLog("Message has photo, receiving");
			String imageUrl;

			IJsonValue *pPhotoValue;
			JsonObject *pPhotoObject;

			Rectangle thumbSize;

			int width = 0, height = 0;

			static const String photoConst(L"photo");

			pAttachObject->GetValue(&photoConst, pPhotoValue);
			pPhotoObject = static_cast<JsonObject *>(pPhotoValue);

			JsonParseUtils::GetString(*pPhotoObject, L"photo_604", imageUrl);
			JsonParseUtils::GetInteger(*pPhotoObject, L"width", width);
			JsonParseUtils::GetInteger(*pPhotoObject, L"height", height);

			if (width != 0 && height != 0) {
				thumbSize = ImageUtils::ScaleTo(320, Rectangle(0, 0, width, height));
			} else {
				thumbSize = Rectangle(0, 0, 320, 240);
			}

			MessagePhotoElement * pPhotoElement = new MessagePhotoElement();
			pPhotoElement->Construct(thumbSize, imageUrl);

			pMessageElement = static_cast<MessageElement *>(pPhotoElement);;

		} else if (attachType == L"video") {
			AppLog("Message has video, receiving");

//			IJsonValue *pVideoValue;
//			JsonObject *pVideoObject;
//
//			static const String videoConst(L"video");
//
//			pAttachObject->GetValue(&videoConst, pVideoValue);
//			pVideoObject = static_cast<JsonObject *>(pVideoValue);

			JsonObject *pVideoObject;
			JsonParseUtils::GetObject(pAttachObject, L"video", pVideoObject);

			MessageVideoElement *pVideoElement = new MessageVideoElement();
			pVideoElement->Construct(Rectangle(0, 0, 320, 240), pVideoObject);

			pMessageElement = static_cast<MessageElement *>(pVideoElement);

		} else if (attachType == L"audio") {
			AppLog("Message has audio, receiving");
			pMessageElement = new MessageAudioElement();
			pMessageElement->Construct(Rectangle(0, 0, 320, 240));

		} else if (attachType == L"doc") {
			AppLog("Message has doc, receiving");
			pMessageElement = new MessageDocElement();
			pMessageElement->Construct(Rectangle(0, 0, 320, 240));

		} else if (attachType == L"wall") {
			AppLog("Message has wall, receiving");
			pMessageElement = new MessageWallElement();
			pMessageElement->Construct(Rectangle(0, 0, 320, 240));

		}

		pResultArray->Add(pMessageElement);
	}

	return pResultArray;

CATCH:
	AppLogException("VKUMessagesListItemProvider::GetMessageElementsN is failed. %s", GetErrorMessage(r));
	return pResultArray;
}

void VKUMessagesListItemProvider::RequestLoadMore(int count) {
	int firstMessageId;
	int userId;
}

void VKUMessagesListItemProvider::RequestNewMessage(int messageId) {
	VKUApi::GetInstance().CreateRequest("messages.getById", this)
		->Put(L"message_ids", Integer::ToString(messageId))
		->Submit(REQUEST_GET_NEW_MESSAGE);
	//RequestNewMessages();
}

void VKUMessagesListItemProvider::RequestNewMessages() {
	int userId;
	int lastMessageId;
	JsonObject *lastMessage;

	JsonParseUtils::GetInteger(*_userJson, L"id", userId);
	if(_messagesJson != null) {
//
//		AppLog("updating messages json: count %d", _messagesJson->GetCount());
//		JsonParseUtils::GetObject(_messagesJson, 0, lastMessage);
//		JsonParseUtils::GetInteger(*lastMessage, L"id", lastMessageId);
//
//		VKUApi::GetInstance().CreateRequest("messages.getHistory", this)
//			->Put(L"count", PRELOAD_MESSAGES)
//			->Put(L"user_id", Integer::ToString(userId))
//			->Put(L"start_message_id", Integer::ToString(lastMessageId))
//			->Submit();
		AppLog("error - messagesJson already exists");
	} else {
		AppLog("request new messages json");
		VKUApi::GetInstance().CreateRequest("messages.getHistory", this)
			->Put(L"count", PRELOAD_MESSAGES)
			->Put(L"user_id", Integer::ToString(userId))
			->Submit(REQUEST_GET_HISTORY);
	}
}


void VKUMessagesListItemProvider::OnResponseN(RequestId requestId, JsonObject *object) {
	result r = E_SUCCESS;

	if(requestId == REQUEST_GET_HISTORY || requestId == REQUEST_GET_NEW_MESSAGE) {
		// save cache
		int userId;
		JsonParseUtils::GetInteger(*_userJson, L"id", userId);
		String cacheFile(VKUApp::GetInstance()->GetCacheDir() + "dialog" + Integer::ToString(userId) + ".json");

		JsonObject *response;
		JsonArray *items;

		AppLog("processing messages json");

		r = JsonParseUtils::GetObject(object, L"response", response);
		TryCatch(r == E_SUCCESS, , "failed get response from object");

		r = JsonParseUtils::GetArray(response, L"items", items);
		TryCatch(r == E_SUCCESS, , "failed get items from response");

		if(_messagesJson == null) {
			AppLog("Assigned %d items", items->GetCount());
			_messagesJson = items->CloneN();
		} else {
			AppLog("added %d items", items->GetCount());
			for(int i = 0; i < items->GetCount(); i++) {
				IJsonValue *value;
				items->GetAt(i, value);
				_messagesJson->InsertAt(static_cast<JsonObject *>(value)->CloneN(), 0);
			}
		}

		_tableView->UpdateTableView();
		TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult() , "Failed pTableView->UpdateTableView");

		_tableView->RequestRedraw(true);
		TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult() , "Failed pTableView->RequestRedraw");

		r = _tableView->ScrollToItem(_tableView->GetItemCount() - 1);
		TryCatch(r == E_SUCCESS, , "Failed pTableView->ScrollToItem");

		JsonWriter::Compose(_messagesJson, cacheFile);
	} else if(requestId == REQUEST_LOAD_MORE) {
		// TODO: implement response processing
	}

	delete object;
	SetLastResult(r);
	return;
CATCH:
	AppLogException("DialogHistoryListener::OnResponseN is failed.", GetErrorMessage(r));
	delete object;
	SetLastResult(r);
	return;
}

