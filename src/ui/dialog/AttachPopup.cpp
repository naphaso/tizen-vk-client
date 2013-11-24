/*
 * AttachPopup.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Igor Glotov
 */

#include "AttachPopup.h"
#include "LocalImageView.h"
#include "AttachLocationElement.h"
#include "AttachPhotoElement.h"

#include <FLocations.h>
#include <FApp.h>
#include "VKU.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::App;
using namespace Tizen::Base::Collection;
using namespace Tizen::Locations;

//using namespace Tizen::Web::Json;

Tizen::Ui::Controls::Popup *AttachPopup::_popup = null;

AttachPopup::AttachPopup(AttachControl * ctl) {
	_attachControl = ctl;
}

AttachPopup::~AttachPopup() {
	// TODO Auto-generated destructor stub
}

void AttachPopup::Show(AttachControl * ctl) {
	AttachPopup *popup = new AttachPopup(ctl);
	popup->Start();
}

void AttachPopup::Start() {
	if(_popup == null) {
		RelativeLayout popupLayout;
		popupLayout.Construct();

		_popup = new Popup();
		_popup->Construct(popupLayout, true, Dimension(600, 580));
		_popup->SetTitleText(L"Attach");
	}

	_popup->SetPropagatedKeyEventListener(this);

	TableView * attachTable = new TableView();
	attachTable->Construct(Rectangle(0, 0, 600, 600), true, TABLE_VIEW_SCROLL_BAR_STYLE_NONE);
	attachTable->SetItemProvider(this);
	attachTable->SetItemDividerColor(Color(0x1b2b38, false));
	attachTable->SetBackgroundColor(Color(0x1f3447, false));
	attachTable->AddTableViewItemEventListener(*this);

	_popup->AddControl(attachTable);
	_popup->SetShowState(true);
	_popup->Show();
}

bool AttachPopup::OnKeyReleased(Control& source, const KeyEventInfo& keyEventInfo) {
   KeyCode key = keyEventInfo.GetKeyCode();
   if (key == KEY_BACK || key == KEY_ESC) {
	   HideAndDie();
   }

   return false;
}

void AttachPopup::HideAndDie() {
    _popup->SetShowState(false);
    _popup->RemoveAllControls();
    _popup->Invalidate(true);
    delete this;

}

void AttachPopup::OnTableViewItemStateChanged(
		Tizen::Ui::Controls::TableView& tableView, int itemIndex,
		Tizen::Ui::Controls::TableViewItem* pItem,
		Tizen::Ui::Controls::TableViewItemStatus status) {
	AppLog("AttachPopup Item state changed");

	switch(status) {
	case TABLE_VIEW_ITEM_STATUS_SELECTED:
		CreateAttachment(AttachmentTypeIndexed(itemIndex));
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



int AttachPopup::GetItemCount(void) {
	return 5;
}

void AttachPopup::OnAppControlCompleteResponseReceived(const Tizen::App::AppId& appId,
						 const Tizen::Base::String& operationId,
						 const Tizen::App::AppCtrlResult appControlResult,
						 const Tizen::Base::Collection::IMap* pExtraData)
{	if (appId.Equals(String(L"tizen.gallery")) &&
	       operationId.Equals(String(L"http://tizen.org/appcontrol/operation/pick")))
	   {
	      if (appControlResult  == APP_CTRL_RESULT_SUCCEEDED)
	      {
	         AppLog("Media list retrieving succeeded.");
	         // Use the selected media paths
	         if (pExtraData)
	         {
	            IList* pValueList = const_cast< IList* >(dynamic_cast< const IList* >
	                                                     (pExtraData->GetValue(String(L"http://tizen.org/appcontrol/data/selected"))));
	            if (pValueList)
	            {
	               for (int i = 0; i < pValueList->GetCount(); i++)
	               {
	                  String* pValue = dynamic_cast< String* >(pValueList->GetAt(i));
	                  // Use the file path
	                  AttachPhotoElement * photoElement = new AttachPhotoElement();
	                  photoElement->Construct(Rectangle(0, 0, 200, 200), *pValue);
	                  _attachControl->AddElement(photoElement);
	               }

	               HideAndDie();
	            }
	         }
	      }
	      else if (appControlResult  == APP_CTRL_RESULT_FAILED)
	      {
	         AppLog("Media list retrieving failed.");
	      }
	      else if (appControlResult  == APP_CTRL_RESULT_CANCELED)
	      {
	         AppLog("Media list retrieving was canceled.");
	      }
	      else if (appControlResult == APP_CTRL_RESULT_TERMINATED)
	      {
	         AppLog("Media list retrieving was terminated.");
	      }
	      else if (appControlResult == APP_CTRL_RESULT_ABORTED)
	      {
	         AppLog("Media list retrieving was is aborted.");
	      }
	   }
}

void AttachPopup::CreateAttachment(AttachmentTypeIndexed item) {
	AttachElement * pElement;
	Rectangle defaultSizeRect(0, 0, 200, 200);
	if (item == ATI_LOCATION) {
		if (!LocationProvider::GetLastKnownLocation().IsValid()) {
			HideAndDie();
			return;
		}

		AttachLocationElement * pLocationElement = new AttachLocationElement();
		pLocationElement->Construct(defaultSizeRect);

		pElement = dynamic_cast<AttachElement *>(pLocationElement);
		_attachControl->AddElement(pElement);
		HideAndDie();
	} else if (item == ATI_PHOTO || item == ATI_VIDEO) {
//		AppControlProviderManager::GetInstance()->SetApp(this);

		String mime = (item == ATI_PHOTO) ? L"image/*" : L"video/*";
		HashMap extraData;
		extraData.Construct();

		String selectKey = L"http://tizen.org/appcontrol/data/selection_mode";
		String selectVal = L"multiple";
		extraData.Add(&selectKey, &selectVal);

		AppControl* pAc = AppManager::FindAppControlN(L"tizen.gallery",
											 L"http://tizen.org/appcontrol/operation/pick");
		if (pAc) {
			pAc->Start(null, &mime, &extraData, this);
			delete pAc;
		}
	}
//	 else {
//		pElement = new AttachElement();
//		pElement->Construct(defaultSizeRect);
//	}

}

Tizen::Ui::Controls::TableViewItem* AttachPopup::CreateItem(int itemIndex, int itemWidth) {
	TableViewItem *pItem;
	RelativeLayout itemLayout;

	LocalImageView * pIcon;
	Label *pLabel;
	String name, icon;


	switch (itemIndex) {
	case 0:
		//name = L"Photo";
		VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_NAME_PHOTO", name);
		icon = L"icon_photo.png";
		break;
	case 1:
		//name = L"Video";
		VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_NAME_VIDEO", name);
		//icon = L"icon_video.png";
		break;
	case 2:
		//name = L"Audio";
		VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_NAME_AUDIO", name);
		icon = L"icon_audio.png";
		break;
	case 3:
		//name = L"Document";
		VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_NAME_DOC", name);
		icon = L"icon_document.png";
		break;
	case 4:
		//name = L"Location";
		VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_NAME_LOCATION", name);
		icon = L"icon_location.png";
		{
			Location location = LocationProvider::GetLastKnownLocation();
			bool valid = location.IsValid();

			if (!valid) {
				name += " (no GPS info)";
			}

		}
		break;
	}

	itemLayout.Construct();

	pItem = new TableViewItem();
	pItem->Construct(itemLayout, Dimension(itemWidth, 100), TABLE_VIEW_ANNEX_STYLE_NORMAL);
	pItem->SetBackgroundColor(Color(0x213f63, false), TABLE_VIEW_ITEM_DRAWING_STATUS_HIGHLIGHTED);
	pItem->SetBackgroundColor(Color(0x213f63, false), TABLE_VIEW_ITEM_DRAWING_STATUS_PRESSED);

	pIcon = new LocalImageView();
	pIcon->Construct(Rectangle(0, 0, 72, 72), icon);

	pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth-72, 40), name);
	pLabel->SetMargin(0, 0);
	pLabel->SetTextConfig(40, LABEL_TEXT_STYLE_NORMAL);
	pLabel->SetTextVerticalAlignment(ALIGNMENT_MIDDLE);
	pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	pItem->AddControl(pIcon);
	pItem->AddControl(pLabel);

	itemLayout.SetRelation(*pIcon, pItem, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	itemLayout.SetMargin(*pIcon, 10, 0, 0, 0);
	itemLayout.SetRelation(*pLabel, pIcon, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	itemLayout.SetMargin(*pLabel, 20, 0, 0, 0);

	itemLayout.SetCenterAligned(*pIcon, CENTER_ALIGN_VERTICAL);
	itemLayout.SetCenterAligned(*pLabel, CENTER_ALIGN_VERTICAL);

	return pItem;
}

bool AttachPopup::DeleteItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem) {
	pItem->Destroy();
	return true;
}

void AttachPopup::UpdateItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem) {

}

int AttachPopup::GetDefaultItemHeight(void) {
	return 80;
}
