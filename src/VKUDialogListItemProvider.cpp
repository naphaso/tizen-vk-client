/*
 * VKUDialogListItemProvider.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: Igor Glotov
 */

#include "VKUDialogListItemProvider.h"
#include "SceneRegister.h"

using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui::Scenes;

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

bool VKUDialogListItemProvider::DeleteItem(int index, ListItemBase* pItem,
		int itemWidth) {
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
	if (itemObject->GetValue(&bodyConst, bodyValue) == E_SUCCESS) {
		if (bodyValue->GetType() == JSON_TYPE_STRING) {
			previewText = *static_cast<JsonString *>(bodyValue);
		}
	}

	AppResource *pAppResource = VKUApp::GetInstance()->GetAppResource();

	avatarBm = pAppResource->GetBitmapN(L"no_photo_user.png",
			BITMAP_PIXEL_FORMAT_ARGB8888);

	item->AddElement(
			Rectangle(AVATAR_MARGIN, AVATAR_MARGIN, AVATAR_SIZE, AVATAR_SIZE),
			40, *avatarBm);
	item->AddElement(
			Rectangle(AVATAR_SIZE + 2 * AVATAR_MARGIN, 0, itemWidth,
					LIST_HEIGHT / 2), 41, L"Unnamed User");
	item->AddElement(
			Rectangle(AVATAR_SIZE + 2 * AVATAR_MARGIN, 50, itemWidth,
					LIST_HEIGHT / 2), 42, previewText);

	return item;
}

int VKUDialogListItemProvider::GetItemCount() {
	if (dialogsJson == null) {
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

// view item events

void VKUDialogListItemProvider::OnListViewItemStateChanged(ListView& listView,
		int index, int elementId, ListItemStatus status) {
	AppLog("status changed for item: %d", index);
	if (status == LIST_ITEM_STATUS_SELECTED) {
		SceneManager* pSceneManager = SceneManager::GetInstance();
		AppAssert(pSceneManager);

		IJsonValue *itemValue;

		dialogsJson->GetAt(index, itemValue);

		JsonObject *itemObject = static_cast<JsonObject *>(itemValue);
//		String jsonPath(L"/tmp/itemObject.txt");
//		JsonWriter::Compose(itemValue, jsonPath);

		IJsonValue *userIdValue;
		static const String userIdConst(L"user_id");

		itemObject->GetValue(&userIdConst, userIdValue);

		JsonNumber *userIdNumber = static_cast<JsonNumber *>(userIdValue);
		ArrayList* pList = new (std::nothrow) ArrayList(SingleObjectDeleter);

		String userIdString;
		userIdString.Append(userIdNumber->ToInt());

		AppLog("userIdString %ls", userIdString.GetPointer());

		pList->Construct();
		pList->Add(new (std::nothrow) String(userIdString));

		AppLog("pList item 0: %ls", static_cast<String *>(pList->GetAt(0))->GetPointer());

		pSceneManager->GoForward(ForwardSceneTransition(SCENE_DIALOG), pList);
	}
}

void VKUDialogListItemProvider::OnListViewItemSwept(ListView& listView,
		int index, SweepDirection direction) {

}

void VKUDialogListItemProvider::OnListViewContextItemStateChanged(
		ListView& listView, int index, int elementId,
		ListContextItemStatus state) {

}

void VKUDialogListItemProvider::OnItemReordered(ListView& view, int oldIndex,
		int newIndex) {

}
