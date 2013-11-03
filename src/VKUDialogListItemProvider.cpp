/*
 * VKUDialogListItemProvider.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: Igor Glotov
 */

#include "VKUDialogListItemProvider.h"

using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

static const int LIST_HEIGHT = 100;

VKUDialogListItemProvider::VKUDialogListItemProvider() {
	// TODO Auto-generated constructor stub

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

	item->AddElement(Rectangle(0, 0, itemWidth, LIST_HEIGHT/2), 41, L"Ololo");
	item->AddElement(Rectangle(0, 50, itemWidth, LIST_HEIGHT/2), 42, L"previewText");

	return item;
}

int VKUDialogListItemProvider::GetItemCount() {
	return 3;
}
