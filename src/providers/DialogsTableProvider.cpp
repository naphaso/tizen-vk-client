/*
 * DialogsTableProvider.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: igorglotov
 */

#include "DialogsTableProvider.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Web::Json;
using namespace Tizen::Web;
using namespace Tizen::Base;
using namespace Tizen::Graphics;

static const int DIALOGS_ITEM_HEIGHT = 130;
static const int PREVIEW_BACKGROUND_COLOR = 0x191f25;
static const int PREVIEW_TEXT_COLOR = 0x6d6e75;

DialogsTableProvider::DialogsTableProvider() {
	dialogsJson = null;
}

DialogsTableProvider::~DialogsTableProvider() {
	// TODO Auto-generated destructor stub
}

int DialogsTableProvider::GetItemCount(void) {
	if (dialogsJson == null)
		return 0;

	return dialogsJson->GetCount();
}

// FIXME: leaks
TableViewItem* DialogsTableProvider::CreateItem(int itemIndex, int itemWidth) {
	result r;

	TableViewItem* pItem;
	RoundedAvatar* pAvatar;
	RelativeLayout pItemlayout;
	Label* pNameLabel, *pPreviewTextLabel, *pTimestampLabel;
	Font nameFont, previewFont;
	Color nameColor, previewColor;

	IJsonValue *pJsonValue;
	JsonObject *pObject;

	String nameText = String("User Name");
	String previewText, timestampText;
	int timeInSec;

	r = dialogsJson->GetAt(itemIndex, pJsonValue);
	TryCatch(r == E_SUCCESS, , "Failed dialogsJson->GetAt");
	pObject = static_cast<JsonObject *>(pJsonValue);

	r = JsonParseUtils::GetString(*pObject, L"body", previewText);
	TryCatch(r == E_SUCCESS, , "Failed JsonParseUtils::GetString");
	r = JsonParseUtils::GetInteger(*pObject, L"date", timeInSec);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = TimeUtils::GetDialogsTime(timeInSec, timestampText);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	pItemlayout.Construct();

	pItem = new TableViewItem();
	r = pItem->Construct(pItemlayout, Dimension(itemWidth, GetDefaultItemHeight()));
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	pAvatar = new RoundedAvatar(LIST_BLACK);
	r  =pAvatar->Construct(Rectangle(0, 0, 108, 108), L"no_photo_user.png");
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	r = nameFont.Construct(FONT_STYLE_PLAIN, 40);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = previewFont.Construct(FONT_STYLE_PLAIN, 30);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	nameColor = Color::GetColor(COLOR_ID_WHITE);
	previewColor = Color(PREVIEW_TEXT_COLOR, false);

	pNameLabel = new Label();
	r = pNameLabel->Construct(Rectangle(0, 0, 300, 50), nameText);
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
	pPreviewTextLabel->SetBackgroundColor(Color(PREVIEW_BACKGROUND_COLOR, false));
	r = pPreviewTextLabel->SetMargin(0, 10);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	pTimestampLabel = new Label();
	r = pTimestampLabel->Construct(Rectangle(0, 0, 32, 40), timestampText);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	pTimestampLabel->SetTextConfig(previewFont.GetSize(), LABEL_TEXT_STYLE_NORMAL);
	pTimestampLabel->SetTextColor(previewColor);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pTimestampLabel->SetMargin(0, 16);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	/* ADDING CONTROLS */

	r = pItem->AddControl(pAvatar);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItem->AddControl(pNameLabel);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItem->AddControl(pPreviewTextLabel);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItem->AddControl(pTimestampLabel);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	/* LAYOUT */

	// avatar layout
	r = pItemlayout.SetRelation(*pAvatar, *pItem, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetRelation(*pAvatar, *pItem, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetMargin(*pAvatar, 20, 0, 11, 0);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	r = pItemlayout.SetRelation(*pNameLabel, *pAvatar, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetRelation(*pNameLabel, *pItem, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetMargin(*pNameLabel, 4, 0, 15, 0);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetHorizontalFitPolicy(*pNameLabel, FIT_POLICY_CONTENT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	r = pItemlayout.SetRelation(*pPreviewTextLabel, *pNameLabel, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetRelation(*pPreviewTextLabel, *pAvatar, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetRelation(*pPreviewTextLabel, *pItem, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetHorizontalFitPolicy(*pPreviewTextLabel, FIT_POLICY_CONTENT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetMargin(*pPreviewTextLabel, 20, 20, 5, 0); // TODO: top padding?
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	r = pItemlayout.SetRelation(*pTimestampLabel, *pItem, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetRelation(*pTimestampLabel, *pItem, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetMargin(*pTimestampLabel, 0, 0, 20, 0);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");
	r = pItemlayout.SetHorizontalFitPolicy(*pTimestampLabel, FIT_POLICY_CONTENT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	r = pItemlayout.SetRelation(*pNameLabel, *pTimestampLabel, RECT_EDGE_RELATION_RIGHT_TO_LEFT);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	return pItem;

CATCH:
	AppLogException("CreateItem is failed.", GetErrorMessage(r));
	SetLastResult(r);
	return pItem;
}

bool DialogsTableProvider::DeleteItem(int itemIndex, TableViewItem* pItem) {
	delete pItem;
	return true;
}

void DialogsTableProvider::UpdateItem(int itemIndex, TableViewItem* pItem) {

}

int DialogsTableProvider::GetDefaultItemHeight(void) {
	return DIALOGS_ITEM_HEIGHT;
}

void DialogsTableProvider::SetDialogsJson(JsonObject* json) {
	responseJson = json;

	IJsonValue *response;
	static const String responseConst(L"response");
	responseJson->GetValue(&responseConst, response);

	IJsonValue *items;
	static const String itemsConst(L"items");
	(static_cast<JsonObject *>(response))->GetValue(&itemsConst, items);

	dialogsJson = static_cast<JsonArray *>(items);
}
