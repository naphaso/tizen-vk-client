/*
 * ContactsTableProvider.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: igorglotov
 */

#include "ContactsTableProvider.h"

using namespace Tizen::Ui;
using namespace Tizen::Base;
using namespace Tizen::Web::Json;
using namespace Tizen::Web;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

ContactsTableProvider::ContactsTableProvider() {
	contactsArray = null;

}

ContactsTableProvider::~ContactsTableProvider() {
	// TODO Auto-generated destructor stub
}

int ContactsTableProvider::GetGroupCount(void) {
	if (contactsArray == null)
		return 0;

	return 1;
}

int ContactsTableProvider::GetItemCount(int groupIndex) {
	if (contactsArray == null)
		return 0;

	return contactsArray->GetCount();
}

TableViewGroupItem* ContactsTableProvider::CreateGroupItem(int groupIndex,
		int itemWidth) {
	result r = E_SUCCESS;
	AppLog("CreateGroupItem %d with %d px", groupIndex, itemWidth);

	TableViewGroupItem* pItem;
	Label * label;
	Integer groupNum = Integer(groupIndex);

	pItem = new TableViewGroupItem();
	r = pItem->Construct(Dimension(itemWidth, GetDefaultGroupItemHeight()));
	TryCatch(r == E_SUCCESS, , "Failed pItem->Construct");

	label = new Label();
	r = label->Construct(Rectangle(0, 0, itemWidth, GetDefaultGroupItemHeight()), groupNum.ToString());
	TryCatch(r == E_SUCCESS, , "Failed pItem->Construct");

	r = pItem->AddControl(label);
	TryCatch(r == E_SUCCESS, , "Failed pItem->AddControl");

	return pItem;
CATCH:
	AppLogException("CreateItem is failed.", GetErrorMessage(r));
	SetLastResult(r);
	return pItem;
}

bool ContactsTableProvider::DeleteGroupItem(int groupIndex,
		TableViewGroupItem* pItem) {
	delete pItem;
	return true;
}

void ContactsTableProvider::UpdateGroupItem(int groupIndex,
		TableViewGroupItem* pItem) {

}

TableViewItem* ContactsTableProvider::CreateItem(int groupIndex, int itemIndex,
		int itemWidth) {
	result r = E_SUCCESS;
	AppLog("CreateItem %d in group %d with %d px", itemIndex, groupIndex, itemWidth);

	TableViewItem* pTableItem;
	Panel* placeholder;
	Label* pUserLabel;
	RoundedAvatar* pRoundedAvatar;
	HorizontalBoxLayout layout;

	layout.Construct(HORIZONTAL_DIRECTION_RIGHTWARD);

	// JSON stuff
	IJsonValue *itemValue;
	IJsonValue *nameValue;
	JsonObject *itemObject;

	static const String bodyConst(L"first_name");
	static const String avatarHardcode(L"no_photo_user.png");
	String userName(L"That Guy");

	pTableItem = new TableViewItem();
	r = pTableItem->Construct(Dimension(itemWidth, GetDefaultItemHeight()), TABLE_VIEW_ANNEX_STYLE_NORMAL);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->Construct");

	placeholder = new Panel();
	r = placeholder->Construct(layout, Rectangle(0, 0, itemWidth, GetDefaultItemHeight()), GROUP_STYLE_NONE);
	TryCatch(r == E_SUCCESS, , "Failed placeholder->Construct");

	pRoundedAvatar = new RoundedAvatar(LIST_BLACK);
	r = pRoundedAvatar->Construct(Rectangle(0, 0, 108, 108), avatarHardcode);
	TryCatch(r == E_SUCCESS, , "Failed pRoundedAvatar->Construct");

	r = placeholder->AddControl(pRoundedAvatar);
	TryCatch(r == E_SUCCESS, , "Failed placeholder->AddControl");

	r = contactsArray->GetAt(itemIndex, itemValue);
	TryCatch(r == E_SUCCESS, , "Failed GetAt");
	itemObject = static_cast<JsonObject *>(itemValue);


	if (itemObject->GetValue(&bodyConst, nameValue) == E_SUCCESS) {
		if (nameValue->GetType() == JSON_TYPE_STRING) {
			userName = *static_cast<JsonString *>(nameValue);
		}
	}

	pUserLabel = new Label();
	r = pUserLabel->Construct(Rectangle(0, 0, itemWidth, GetDefaultItemHeight()), userName);
	TryCatch(r == E_SUCCESS, , "Failed pUserLabel->Construct");

	r = placeholder->AddControl(pUserLabel);
	TryCatch(r == E_SUCCESS, , "Failed placeholder->AddControl");

	r = pTableItem->AddControl(placeholder);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->AddControl");

	return pTableItem;
CATCH:
	AppLogException("$${Function:CreateItem} is failed.", GetErrorMessage(r));
	SetLastResult(r);
	return pTableItem;
}

bool ContactsTableProvider::DeleteItem(int groupIndex, int itemIndex,
		TableViewItem* pItem) {
	delete pItem;
	return true;
}

void ContactsTableProvider::UpdateItem(int groupIndex, int itemIndex,
		TableViewItem* pItem) {

}

int ContactsTableProvider::GetDefaultGroupItemHeight(void) {
	return 50;
}

int ContactsTableProvider::GetDefaultItemHeight(void) {
	return 120;
}

void ContactsTableProvider::SetUsersJson(Tizen::Web::Json::JsonObject *json) {
	result r = E_SUCCESS;

	contactsObject = json;
	AppLog("Setting messaging json");

	IJsonValue *response;
	static const String responseConst(L"response");
	r = contactsObject->GetValue(&responseConst, response);
	TryCatch(r == E_SUCCESS, , "Failed GetValue");


	IJsonValue *items;
	static const String itemsConst(L"items");
	r = (static_cast<JsonObject *>(response))->GetValue(&itemsConst, items);
	TryCatch(r == E_SUCCESS, , "Failed GetValue");

	contactsArray = static_cast<JsonArray *>(items);
	AppLog("Assigned %d items", contactsArray->GetCount());

	SetLastResult(r);
	return;

CATCH:
	AppLogException("$${Function:SetUsersJson} is failed.", GetErrorMessage(r));
	SetLastResult(r);
}
