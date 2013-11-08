/*
 * ContactsTableProvider.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: igorglotov
 */

#include "ContactsTableProvider.h"

using namespace Tizen::Ui;
using namespace Tizen::Base;
using namespace Tizen::Web;
using namespace Tizen::Web::Json;
using namespace Tizen::Ui::Controls;

ContactsTableProvider::ContactsTableProvider() {
	// TODO Auto-generated constructor stub

}

ContactsTableProvider::~ContactsTableProvider() {
	// TODO Auto-generated destructor stub
}

int ContactsTableProvider::GetItemCount(int groupIndex) {

}

TableViewGroupItem* ContactsTableProvider::CreateGroupItem(int groupIndex,
		int itemWidth) {
	result r = E_SUCCESS;

	TableViewGroupItem* pItem;
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

	TableViewItem* pTableItem;
	Panel* placeholder;
	RoundedAvatar* pRoundedAvatar;
	HorizontalBoxLayout layout;

	pTableItem = new TableViewItem();
	r = pTableItem->Construct(Dimension(itemWidth, GetDefaultItemHeight()), LIST_ANNEX_STYLE_NORMAL);
	TryCatch(r == E_SUCCESS, , "Failed pTableItem->Construct");

	placeholder = new Panel();
	r = placeholder->Construct(layout, Rectangle(0, 0, GetDefaultItemHeight(), itemWidth), GROUP_STYLE_NONE);
	TryCatch(r == E_SUCCESS, , "Failed placeholder->Construct");

	pRoundedAvatar = new RoundedAvatar(LIST_BLACK);
	r = pRoundedAvatar->Construct(Rectangle(0, 0, 108, 108), L"no_photo_user.png");
	TryCatch(r == E_SUCCESS, , "Failed pRoundedAvatar->Construct");

	r = placeholder->AddControl(pRoundedAvatar);
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
	return 200;
}

int ContactsTableProvider::GetDefaultItemHeight(void) {
	return 100;
}
