/*
 * DialogsTableProvider.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: igorglotov
 */

#include "DialogsTableProvider.h"
#include "../api/VKUApi.h"
#include "JsonParseUtils.h"
#include "../api/VKUAuthConfig.h"
#include "SceneRegister.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Web::Json;
using namespace Tizen::Web;
using namespace Tizen::Base;
using namespace Tizen::Graphics;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui::Scenes;

static const int CONFIRM_DELETION = 142;

static const int DIALOGS_ITEM_HEIGHT = 130;
static const int PREVIEW_BACKGROUND_COLOR = 0x191f25;
static const int PREVIEW_TEXT_COLOR = 0x6d6e75;
static const int UNREAD_BACKGROUND_COLOR = 0x191f25;
static const int HIGHLIGHTED_COLOR = 0x213f63;

static const String userJsonConst(L"user_json");

DialogsTableProvider::DialogsTableProvider() {
	dialogsJson = null;
	filteredDialogsJson = null;
}

result DialogsTableProvider::Construct(TableView* tableView) {
	pDialogTableView = tableView;
	IJsonValue *dialogs = JsonParser::ParseN(VKUApp::GetInstance()->GetCacheDir() + "dialogs.json");
	if(GetLastResult() == E_SUCCESS) {
		dialogsJson = static_cast<JsonArray *>(dialogs);
	}

	return E_SUCCESS;
}

DialogsTableProvider::~DialogsTableProvider() {
	// TODO Auto-generated destructor stub
}

int DialogsTableProvider::GetItemCount(void) {
	if(filteredDialogsJson != null) {
		return filteredDialogsJson->GetCount();
	}

	if (dialogsJson == null) {
		return 0;
	}

	return dialogsJson->GetCount();
}

// FIXME: leaks
TableViewItem* DialogsTableProvider::CreateItem(int itemIndex, int itemWidth) {
	result r;

	AppLog("DialogsTableProvider::CreateItem");

	TableViewItem* pItem;
	RoundedAvatar* pAvatar;
	RelativeLayout* pItemlayout;
	Label* pNameLabel, *pPreviewTextLabel, *pTimestampLabel;
	Font nameFont, previewFont;
	Color nameColor, previewColor;
	Panel *pPlaceholderPanel;

	TableViewContextItem *pContextItem;
	RelativeLayout contextPlaceholderLayout;
	Panel* pContextPlaceholder;
	Button* pContextConfirmButton;

	IJsonValue *pJsonValue, *pUserInfoValue;
	JsonObject *pObject, *pUserInfoObject;

	String firstName, lastName, fullName;
	String previewText, timestampText, avatarUrl;
	int timeInSec, readState, myUserId, out;
	AvatarType avType = AVATAR_NORMAL;

	myUserId = VKUAuthConfig::GetUserId();

	if(filteredDialogsJson != null) {
		r = filteredDialogsJson->GetAt(itemIndex, pJsonValue);
		TryCatch(r == E_SUCCESS, , "Failed dialogsJson->GetAt");
	} else {
		r = dialogsJson->GetAt(itemIndex, pJsonValue);
		TryCatch(r == E_SUCCESS, , "Failed dialogsJson->GetAt");
	}

	pObject = static_cast<JsonObject *>(pJsonValue);
	pObject->GetValue(&userJsonConst, pUserInfoValue);
	pUserInfoObject = static_cast<JsonObject *>(pUserInfoValue);
	JsonParseUtils::GetString(*pUserInfoObject, L"first_name", firstName);
	JsonParseUtils::GetString(*pUserInfoObject, L"last_name", lastName);
	JsonParseUtils::GetString(*pUserInfoObject, L"photo_100", avatarUrl);

	firstName.Append(L" ");
	firstName.Append(lastName);

	JsonParseUtils::GetInteger(*pObject, "read_state", readState);
	JsonParseUtils::GetInteger(*pObject, "out", out);

	r = JsonParseUtils::GetString(*pObject, L"body", previewText);
	TryCatch(r == E_SUCCESS, , "Failed JsonParseUtils::GetString");
	r = JsonParseUtils::GetInteger(*pObject, L"date", timeInSec);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = TimeUtils::GetDialogsTime(timeInSec, timestampText);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	pItemlayout = new RelativeLayout();
	pItemlayout->Construct();

	pItem = new TableViewItem();
	r = pItem->Construct(Dimension(itemWidth, GetDefaultItemHeight()));
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	pItem->SetBackgroundColor(Color(HIGHLIGHTED_COLOR, false), TABLE_VIEW_ITEM_DRAWING_STATUS_PRESSED);
	pItem->SetBackgroundColor(Color(HIGHLIGHTED_COLOR, false), TABLE_VIEW_ITEM_DRAWING_STATUS_HIGHLIGHTED);

//	pItemlayout = static_cast<RelativeLayout *>(pItem->GetLayoutN());

	if (out == 0 && readState == 0) {
		pItem->SetBackgroundColor(Color(UNREAD_BACKGROUND_COLOR, false), TABLE_VIEW_ITEM_DRAWING_STATUS_NORMAL);
		avType = AVATAR_UNREAD;
	}

	pAvatar = new RoundedAvatar(avType);
	r = pAvatar->Construct(Rectangle(0, 0, 108, 108), avatarUrl);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	r = nameFont.Construct(FONT_STYLE_PLAIN, 40);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = previewFont.Construct(FONT_STYLE_PLAIN, 30);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	nameColor = Color::GetColor(COLOR_ID_WHITE);
	previewColor = Color(PREVIEW_TEXT_COLOR, false);

	pNameLabel = new Label();
	r = pNameLabel->Construct(Rectangle(0, 0, 300, 50), firstName);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	pNameLabel->SetTextConfig(nameFont.GetSize(), LABEL_TEXT_STYLE_NORMAL);
	r = pNameLabel->SetMargin(0, 16);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	pPreviewTextLabel = new Label();
	r = pPreviewTextLabel->Construct(Rectangle(0, 0, 300, 50), previewText);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	pPreviewTextLabel->SetTextConfig(previewFont.GetSize(), LABEL_TEXT_STYLE_NORMAL);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	pPreviewTextLabel->SetTextColor(previewColor);

	if (out == 1 && readState == 0) {
		pPreviewTextLabel->SetBackgroundColor(Color(PREVIEW_BACKGROUND_COLOR, false));
		r = pPreviewTextLabel->SetMargin(0, 10);
		TryCatch(r == E_SUCCESS, , "Failed pPreviewTextLabel->SetMargin");
	} else {
		r = pPreviewTextLabel->SetMargin(0, 0);
	}

	pTimestampLabel = new Label();
	r = pTimestampLabel->Construct(Rectangle(0, 0, 32, 40), timestampText);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	pTimestampLabel->SetTextConfig(previewFont.GetSize(), LABEL_TEXT_STYLE_NORMAL);
	pTimestampLabel->SetTextColor(previewColor);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pTimestampLabel->SetMargin(0, 16);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	pPlaceholderPanel = new Panel();
	pPlaceholderPanel->Construct(*pItemlayout, Rectangle(0, 0, itemWidth, GetDefaultItemHeight()));

	/* ADDING CONTROLS */

	r = pPlaceholderPanel->AddControl(pAvatar);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pPlaceholderPanel->AddControl(pNameLabel);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pPlaceholderPanel->AddControl(pPreviewTextLabel);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pPlaceholderPanel->AddControl(pTimestampLabel);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");


//	/* LAYOUT */
//
	AppLog("DialogsTableProvider::CreateItem - avatar layout");

	// avatar layout
	r = pItemlayout->SetRelation(*pAvatar, pPlaceholderPanel, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetRelation(*pAvatar, pPlaceholderPanel, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetMargin(*pAvatar, 20, 0, 11, 0);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	AppLog("DialogsTableProvider::CreateItem - name layout");

	r = pItemlayout->SetRelation(*pNameLabel, pAvatar, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetRelation(*pNameLabel, pPlaceholderPanel, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetMargin(*pNameLabel, 4, 0, 15, 0);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetHorizontalFitPolicy(*pNameLabel, FIT_POLICY_CONTENT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	AppLog("DialogsTableProvider::CreateItem - preview layout");

	r = pItemlayout->SetRelation(*pPreviewTextLabel, pNameLabel, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetRelation(*pPreviewTextLabel, pAvatar, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetRelation(*pPreviewTextLabel, pPlaceholderPanel, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetHorizontalFitPolicy(*pPreviewTextLabel, FIT_POLICY_CONTENT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetMargin(*pPreviewTextLabel, 20, 20, 5, 0); // TODO: top padding?
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	AppLog("DialogsTableProvider::CreateItem - timestamp layout");

	r = pItemlayout->SetRelation(*pTimestampLabel, pPlaceholderPanel, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetRelation(*pTimestampLabel, pPlaceholderPanel, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetMargin(*pTimestampLabel, 0, 0, 20, 0);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout->SetHorizontalFitPolicy(*pTimestampLabel, FIT_POLICY_CONTENT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	r = pItemlayout->SetRelation(*pNameLabel, pTimestampLabel, RECT_EDGE_RELATION_RIGHT_TO_LEFT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	AppLog("DialogsTableProvider::CreateItem - after timestamp");

	r = pItem->AddControl(pPlaceholderPanel);
	TryCatch(r == E_SUCCESS, , "Failed pItem->AddControl");

	contextPlaceholderLayout.Construct();

	pContextPlaceholder = new Panel();
	pContextPlaceholder->Construct(contextPlaceholderLayout, Rectangle(0, 0, itemWidth, GetDefaultItemHeight()));

	pContextItem = new TableViewContextItem();
	pContextItem->Construct(pItem->GetSize());

	pContextConfirmButton = new Button();
	pContextConfirmButton->Construct(Rectangle(0, 0, 200, 90), L"Remove");
	pContextConfirmButton->SetColor(BUTTON_STATUS_NORMAL, Color::GetColor(COLOR_ID_RED));
	pContextConfirmButton->SetActionId(CONFIRM_DELETION);
	pContextConfirmButton->AddActionEventListener(*this);

	pContextPlaceholder->AddControl(pContextConfirmButton);

	contextPlaceholderLayout.SetCenterAligned(*pContextConfirmButton, CENTER_ALIGN_HORIZONTAL);
	contextPlaceholderLayout.SetCenterAligned(*pContextConfirmButton, CENTER_ALIGN_VERTICAL);

	pContextItem->AddControl(pContextPlaceholder);

	pItem->SetContextItem(pContextItem);


	pItem->RequestRedraw(true);

	return pItem;

CATCH:
	AppLogException("CreateItem is failed. %s", GetErrorMessage(r));
	SetLastResult(r);
	return pItem;
}

bool DialogsTableProvider::DeleteItem(int itemIndex, TableViewItem* pItem) {
	AppLog("DialogsTableProvider::DeleteItem");

	pItem->Destroy();
	//delete pItem;
	return true;
}

void DialogsTableProvider::UpdateItem(int itemIndex, TableViewItem* pItem) {
	AppLog("DialogsTableProvider::UpdateItem %d", itemIndex);
}

int DialogsTableProvider::GetDefaultItemHeight(void) {
	return DIALOGS_ITEM_HEIGHT;
}

void DialogsTableProvider::SetDialogsJson(JsonObject* json) {
	AppLog("DialogsTableProvider::SetDialogsJson");

	IJsonValue *items;
	static const String itemsConst(L"items");
	json->GetValue(&itemsConst, items);

	dialogsJson = static_cast<JsonArray *>(items);

	String cacheFilePath(VKUApp::GetInstance()->GetCacheDir() + L"dialogs.json");
	JsonWriter::Compose(dialogsJson, cacheFilePath);
}

void DialogsTableProvider::ProcessJson(Tizen::Web::Json::JsonObject* obj) {
	result r;

//	ByteBuffer bb;
//	bb.Construct(65535);
//	String filePath(L"/tmp/execute.txt");
//	JsonWriter::Compose(obj, filePath);
//	AppLog("RESULT: %s", bb.GetPointer());

	IJsonValue *response;
	const String responseConst(L"response");
	obj->GetValue(&responseConst, response);

	AppLog("casting response to json");
	JsonObject *responseJson = static_cast<JsonObject *>(response);

	IJsonValue *dialogs;
	const String dialogsConst(L"dialogs");
	r = responseJson->GetValue(&dialogsConst, dialogs);

	IJsonValue *dialogItemsVal;
	const String dialogsItems(L"items");
	(static_cast<JsonObject *>(dialogs))->GetValue(&dialogsItems, dialogItemsVal);
	AppLog("dialogs items received");

	JsonArray* dialogsJsonArray = static_cast<JsonArray *>(dialogItemsVal);

	IJsonValue *users;
	const String usersConst(L"users");
	r = responseJson->GetValue(&usersConst, users);
	AppLog("users received");

	HashMap usersMap(SingleObjectDeleter);
	usersMap.Construct(); // FIXME: we know map size!

	JsonArray *usersJsonArray = static_cast<JsonArray *>(users);
	AppLog("constructing map");

	for (int i=0; i<usersJsonArray->GetCount(); i++) {
		IJsonValue* user;
		usersJsonArray->GetAt(i, user);

		JsonObject* userJson = static_cast<JsonObject *>(user);

		int userId;
		JsonParseUtils::GetInteger(*userJson, L"id", userId);

		usersMap.Add(new Integer(userId), userJson->CloneN());
	}

	AppLog("building new json");
	for (int i=0; i<dialogsJsonArray->GetCount(); i++) {
		IJsonValue* dialog;
		dialogsJsonArray->GetAt(i, dialog);

		JsonObject* dialogJson = static_cast<JsonObject *>(dialog);

		int userId;
		JsonParseUtils::GetInteger(*dialogJson, L"user_id", userId);

		JsonObject* userJson = static_cast<JsonObject *>(usersMap.GetValue(Integer(userId)));
		dialogJson->Add(new String(L"user_json"), userJson->CloneN());
	}

	AppLog("SetDialogsJson");
	SetDialogsJson((static_cast<JsonObject *>(dialogs))->CloneN());
	delete obj;
}

void DialogsTableProvider::OnResponseN(Tizen::Web::Json::JsonObject *object) {
	ProcessJson(object);

	pDialogTableView->UpdateTableView();
	//pDialogTableView->RequestRedraw(true);
}

void DialogsTableProvider::LoadData() {
	VKUApi::GetInstance().CreateRequest("execute.getDialogsWithUsers", this)->Submit();
}

void DialogsTableProvider::OnTableViewItemStateChanged(
		Tizen::Ui::Controls::TableView& tableView, int itemIndex,
		Tizen::Ui::Controls::TableViewItem* pItem,
		Tizen::Ui::Controls::TableViewItemStatus status) {

	AppLog("Item state changed");

	switch(status) {
	case TABLE_VIEW_ITEM_STATUS_SELECTED:
		OpenDialog(itemIndex);
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

void DialogsTableProvider::OnTableViewContextItemActivationStateChanged(
		Tizen::Ui::Controls::TableView& tableView, int itemIndex,
		Tizen::Ui::Controls::TableViewContextItem* pContextItem,
		bool activated) {
	if (!activated)
		return;


	IJsonValue *itemValue;
	dialogsJson->GetAt(itemIndex, itemValue);
	JsonObject *itemObject = static_cast<JsonObject *>(itemValue);

	JsonParseUtils::GetInteger(*itemObject, L"user_id", pendingRemoveId);
}

void DialogsTableProvider::OnActionPerformed(const Tizen::Ui::Control& source, int actionId) {
	if (actionId == CONFIRM_DELETION) {
		VKUApi::GetInstance().CreateRequest("messages.deleteDialog", this)->Put(L"user_id", Integer::ToString(pendingRemoveId))->Submit();
	}
}

void DialogsTableProvider::OpenDialog(int index) {
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	IJsonValue *itemValue;
	dialogsJson->GetAt(index, itemValue);
	JsonObject *itemObject = static_cast<JsonObject *>(itemValue);

	static const String userJsonConst(L"user_json");
	IJsonValue *userJsonValue;
	itemObject->GetValue(&userJsonConst, userJsonValue);

	JsonObject *userJsonObject = static_cast<JsonObject *>(userJsonValue);

	ArrayList* pList = new (std::nothrow) ArrayList(SingleObjectDeleter);

	pList->Construct(1);
	pList->Add(userJsonObject);

	pSceneManager->GoForward(ForwardSceneTransition(SCENE_DIALOG), pList);
}

// ITextEventListener
void DialogsTableProvider::OnTextValueChanged(const Tizen::Ui::Control& source) {
	String filter1 = static_cast<const SearchBar*>(&source)->GetText();
	String filter;
	filter1.ToLowerCase(filter);

	if(!filter.IsEmpty()) {
		JsonArray *newDialogs = new JsonArray();
		newDialogs->Construct();

		for(int i = 0; i < dialogsJson->GetCount(); i++) {
			IJsonValue *dialog;
			JsonObject *dialogObject;
			IJsonValue *userInfoValue;
			JsonObject *userInfo;
			String firstName;
			String lastName;
			String messageText;
			String firstNameL;
			String lastNameL;
			String messageTextL;

			dialogsJson->GetAt(i, dialog);
			dialogObject = static_cast<JsonObject *> (dialog);

			dialogObject->GetValue(&userJsonConst, userInfoValue);
			userInfo = static_cast<JsonObject *>(userInfoValue);
			JsonParseUtils::GetString(*userInfo, L"first_name", firstName);
			JsonParseUtils::GetString(*userInfo, L"last_name", lastName);
			JsonParseUtils::GetString(*dialogObject, L"body", messageText);

			firstName.ToLowerCase(firstNameL);
			lastName.ToLowerCase(lastNameL);
			messageText.ToLowerCase(messageTextL);

			if(firstNameL.Contains(filter) || lastNameL.Contains(filter) || messageTextL.Contains(filter)) {
				newDialogs->Add(dialogObject->CloneN());
			}
		}

		filteredDialogsJson = newDialogs;
		pDialogTableView->UpdateTableView();
		pDialogTableView->RequestRedraw();
	} else {
		if(filteredDialogsJson != null) {
			delete filteredDialogsJson;
			filteredDialogsJson = null;
			pDialogTableView->UpdateTableView();
			pDialogTableView->RequestRedraw();
		}
	}
}

void DialogsTableProvider::OnTextValueChangeCanceled(const Tizen::Ui::Control& source) {
	if(filteredDialogsJson != null) {
		delete filteredDialogsJson;
		filteredDialogsJson = null;
		pDialogTableView->UpdateTableView();
		pDialogTableView->RequestRedraw();
	}
}

// ISearchBarEventListener
void DialogsTableProvider::OnSearchBarModeChanged(Tizen::Ui::Controls::SearchBar& source, SearchBarMode mode) {
	if(mode == SEARCH_BAR_MODE_NORMAL) {
		if(filteredDialogsJson != null) {
			delete filteredDialogsJson;
			filteredDialogsJson = null;
			pDialogTableView->UpdateTableView();
			pDialogTableView->RequestRedraw();
		}
	}
}
