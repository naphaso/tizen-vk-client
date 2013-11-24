/*
 * SettingsSectionTableProvider.cpp
 *
 *  Created on: Nov 19, 2013
 *      Author: igorglotov
 */

#include "SettingsSectionTableProvider.h"
#include "ObjectCounter.h"
#include "VKU.h"
#include "Settings.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

SettingsSectionTableProvider::SettingsSectionTableProvider() {
	CONSTRUCT(L"SettingsSectionTableProvider");
}

SettingsSectionTableProvider::~SettingsSectionTableProvider() {
	DESTRUCT(L"SettingsSectionTableProvider");
}

void SettingsSectionTableProvider::OnSectionTableViewContextItemActivationStateChanged(
		Tizen::Ui::Controls::SectionTableView& tableView, int sectionIndex,
		int itemIndex, Tizen::Ui::Controls::TableViewContextItem* pContextItem,
		bool activated) {


}

void SettingsSectionTableProvider::OnSectionTableViewItemStateChanged(
		Tizen::Ui::Controls::SectionTableView& tableView, int sectionIndex,
		int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem,
		Tizen::Ui::Controls::TableViewItemStatus status) {

	String texts[2][3];

	texts[0][0] = L"sound";
	texts[0][1] = L"vibe";
	texts[0][2] = L"notify";

	texts[1][0] = L"resize";
	texts[1][1] = L"reserved1";
	texts[1][2] = L"reserved2";

	AppLog("Item state changed");

	switch(status) {
	case TABLE_VIEW_ITEM_STATUS_SELECTED:
		AppLog("TABLE_VIEW_ITEM_STATUS_SELECTED");
		break;
	case TABLE_VIEW_ITEM_STATUS_HIGHLIGHTED:
		AppLog("TABLE_VIEW_ITEM_STATUS_HIGHLIGHTED");
		break;
	case TABLE_VIEW_ITEM_STATUS_CHECKED:
		AppLog("TABLE_VIEW_ITEM_STATUS_CHECKED");
		Settings::SetSetting(texts[sectionIndex][itemIndex], 1);
		break;
	case TABLE_VIEW_ITEM_STATUS_UNCHECKED:
		AppLog("TABLE_VIEW_ITEM_STATUS_UNCHECKED");
		Settings::SetSetting(texts[sectionIndex][itemIndex], 0);
		break;
	case TABLE_VIEW_ITEM_STATUS_MORE:
		AppLog("TABLE_VIEW_ITEM_STATUS_MORE");
		break;
	}
}

int SettingsSectionTableProvider::GetSectionCount(void) {
	return 2;
}

int SettingsSectionTableProvider::GetItemCount(int sectionIndex) {
	if (sectionIndex == 0)
		return 3;
	else
		return 1;
}

bool SettingsSectionTableProvider::HasSectionHeader(int sectionIndex) {
	return true;
}

bool SettingsSectionTableProvider::HasSectionFooter(int sectionIndex) {
	return false;
}

Tizen::Base::String SettingsSectionTableProvider::GetSectionHeader(
		int sectionIndex) {
	String header;
	if (sectionIndex == 0)
		VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_NEW_MESSAGES", header);
		//header = L"New messages";
	else
		VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_PHOTO_PROCESSING", header);
		//header = L"Photo processing";

	return header;
}

Tizen::Base::String SettingsSectionTableProvider::GetSectionFooter(
		int sectionIndex) {
	return String(L"");
}

int SettingsSectionTableProvider::GetDefaultItemHeight(void) {
	return 120;
}

Tizen::Ui::Controls::TableViewItem* SettingsSectionTableProvider::CreateItem(
		int sectionIndex, int itemIndex, int itemWidth) {
	TableViewItem* pItem;
	Label *pLabel;

	Color itemBgColor(0x0e151c, false);

	RelativeLayout itemLayout;
	itemLayout.Construct();

	pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, GetDefaultItemHeight()), GetSectionText(sectionIndex, itemIndex));
	pLabel->SetTextConfig(40, LABEL_TEXT_STYLE_NORMAL);

	pItem = new TableViewItem();
	pItem->Construct(itemLayout, Dimension(itemWidth, GetDefaultItemHeight()), GetSectionStyle(sectionIndex, itemIndex));
	pItem->SetBackgroundColor(itemBgColor, TABLE_VIEW_ITEM_DRAWING_STATUS_NORMAL);
	pItem->SetBackgroundColor(itemBgColor, TABLE_VIEW_ITEM_DRAWING_STATUS_PRESSED);
	pItem->SetBackgroundColor(itemBgColor, TABLE_VIEW_ITEM_DRAWING_STATUS_HIGHLIGHTED);

	pItem->AddControl(pLabel);

	itemLayout.SetHorizontalFitPolicy(*pLabel, FIT_POLICY_CONTENT);
	itemLayout.SetRelation(*pLabel, pItem, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	itemLayout.SetMargin(*pLabel, 20, 0, 0, 0);
	itemLayout.SetCenterAligned(*pLabel, CENTER_ALIGN_VERTICAL);

	return pItem;
}

bool SettingsSectionTableProvider::DeleteItem(int sectionIndex, int itemIndex,
		Tizen::Ui::Controls::TableViewItem* pItem) {
	pItem->Destroy();
	return true;
}

void SettingsSectionTableProvider::UpdateItem(int sectionIndex, int itemIndex,
		Tizen::Ui::Controls::TableViewItem* pItem) {

}

String SettingsSectionTableProvider::GetSectionText(int section, int index) {
	if (section > 1 || index > 2)
		return L"INCORRECT";

	String texts[2][3];

	VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_SOUND", texts[0][0]);
	VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_VIBRATION", texts[0][1]);
	VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_NOTIFICATION", texts[0][2]);

	VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_RESIZE_BEFORE_UPLOAD", texts[1][0]);
	VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_UNKNOWN", texts[1][1]);
	VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_UNKNOWN", texts[1][2]);
	/*
	texts[0][0] = L"Sound";
	texts[0][1] = L"Vibration";
	texts[0][2] = L"Notification";

	texts[1][0] = L"Resize before upload";
	texts[1][1] = L"UNKNOWN";
	texts[1][2] = L"UNKNOWN";
*/
	return texts[section][index];
}

TableViewAnnexStyle SettingsSectionTableProvider::GetSectionStyle(int section, int index) {
	if (section > 1 || index > 2)
		return TABLE_VIEW_ANNEX_STYLE_NORMAL;

	TableViewAnnexStyle styles[2][3];

	styles[0][0] = TABLE_VIEW_ANNEX_STYLE_ONOFF_SLIDING;
	styles[0][1] = TABLE_VIEW_ANNEX_STYLE_ONOFF_SLIDING;
	styles[0][2] = TABLE_VIEW_ANNEX_STYLE_DETAILED;

	styles[1][0] = TABLE_VIEW_ANNEX_STYLE_ONOFF_SLIDING;
	styles[1][1] = TABLE_VIEW_ANNEX_STYLE_ONOFF_SLIDING;
	styles[1][2] = TABLE_VIEW_ANNEX_STYLE_ONOFF_SLIDING;

	return styles[section][index];
}
