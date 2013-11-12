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

static const int DIALOGS_ITEM_HEIGHT = 120;

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

TableViewItem* DialogsTableProvider::CreateItem(int itemIndex, int itemWidth) {
	result r;

	TableViewItem* pItem;
	RoundedAvatar* pAvatar;
	Panel* pVerticalTextPanel;
	RelativeLayout textLayout;
	Label* pNameLabel, *pPreviewTextLabel;
	Font font;

	textLayout.Construct();

	pItem = new TableViewItem();
	r = pItem->Construct(tableItemLayout, Dimension(itemWidth, GetDefaultItemHeight()));

	pAvatar = new RoundedAvatar(LIST_BLACK);
	pAvatar->Construct(Rectangle(0, 0, 108, 108), L"no_photo_user.png");

	pVerticalTextPanel = new Panel();
	pVerticalTextPanel->Construct(textLayout);

	font.Construct(FONT_STYLE_PLAIN, 30);

	pNameLabel = new Label();
	pNameLabel->Construct(Rectangle(0, 0, 50, 300));
	pNameLabel->SetFont()

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
