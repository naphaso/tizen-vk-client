/*
 * VKUDialogListItemProvider.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: Igor Glotov
 */

#include "VKUDialogListItemProvider.h"

using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;
using namespace Tizen::Base;
using namespace Tizen::App;

static const int LIST_HEIGHT = 100;

static const int AVATAR_MARGIN = 10;
static const int AVATAR_SIZE = 80;

VKUDialogListItemProvider::VKUDialogListItemProvider() {
	dialogsJson = null;
	responseJson = null;
}

VKUDialogListItemProvider::~VKUDialogListItemProvider() {
	// TODO Auto-generated destructor stub
}

bool VKUDialogListItemProvider::DeleteItem(int index, ListItemBase* pItem, int itemWidth) {
	delete pItem;
	return true;
}

ListItemBase* VKUDialogListItemProvider::CreateItem(int index, int itemWidth) {
//	VKUDialogItem* dialogItem = new VKUDialogItem();
//	dialogItem->Construct(Rectangle(0, 0, 50, 50));

	CustomItem* item = new CustomItem();
	item->Construct(Dimension(itemWidth, LIST_HEIGHT), LIST_ANNEX_STYLE_NORMAL);

//	EnrichedText* senderName = new EnrichedText();
//	senderName->Construct(Dimension(itemWidth, LIST_HEIGHT/2));

//	EnrichedText* previewText = new EnrichedText();
//	previewText->Construct(Dimension(itemWidth, LIST_HEIGHT/2));

	IJsonValue *itemValue;
	dialogsJson->GetAt(index, itemValue);
	JsonObject *itemObject = static_cast<JsonObject *>(itemValue);

	String previewText(L"unknown");

	IJsonValue *bodyValue;
	static const String bodyConst(L"body");
	if(itemObject->GetValue(&bodyConst, bodyValue) == E_SUCCESS) {
		if(bodyValue->GetType() == JSON_TYPE_STRING) {
			previewText = *static_cast<JsonString *>(bodyValue);
		}
	}

	AppResource *pAppResource = VKUApp::GetInstance()->GetAppResource();

	avatarBm = pAppResource->GetBitmapN(L"no_photo_user.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	item->AddElement(Rectangle(AVATAR_MARGIN, AVATAR_MARGIN, AVATAR_SIZE, AVATAR_SIZE), 40, *avatarBm);
	item->AddElement(Rectangle(AVATAR_SIZE + 2*AVATAR_MARGIN, 0, itemWidth, LIST_HEIGHT/2), 41, L"Unnamed User");
	item->AddElement(Rectangle(AVATAR_SIZE + 2*AVATAR_MARGIN, 50, itemWidth, LIST_HEIGHT/2), 42, previewText);

	return item;
}

int VKUDialogListItemProvider::GetItemCount() {
	if(dialogsJson == null) {
		return 0;
	} else {
		return dialogsJson->GetCount();
	}
}

void VKUDialogListItemProvider::SetDialogsJson(JsonObject *json) {
	responseJson = json;

	IJsonValue *response;
	static const String responseConst(L"response");
	responseJson->GetValue(&responseConst, response);

	IJsonValue *items;
	static const String itemsConst(L"items");
	(static_cast<JsonObject *>(response))->GetValue(&itemsConst, items);

	dialogsJson = static_cast<JsonArray *>(items);
}
