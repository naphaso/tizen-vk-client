/*
 * MessageWallElement.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "MessageWallElement.h"
#include "LocalImageView.h"
#include "JsonParseUtils.h"
#include "VKU.h"
#include "ObjectCounter.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base;
using namespace Tizen::Web::Json;
using namespace Tizen::App;

MessageWallElement::MessageWallElement() {
	_pBitmap = null;
	CONSTRUCT(L"MessageWallElement");
}

MessageWallElement::~MessageWallElement() {
	delete _pBitmap;

	DESTRUCT(L"MessageWallElement");
}

result MessageWallElement::Construct(const Tizen::Graphics::Rectangle & rect, JsonObject * wallObject, int out) {
	result r = E_SUCCESS;

	baseUrl = L"https://vk.com/feed?w=wall{FROM_ID}_{ID}";

	RelativeLayout layout;
	LocalImageView *_pIcon;
	Label *nameLabel;
	String filename, postIdStr, fromIdStr;
	int postid, fromid;

	JsonParseUtils::GetInteger(*wallObject, L"id", postid);
	JsonParseUtils::GetInteger(*wallObject, L"from_id", fromid);

	postIdStr = Integer::ToString(postid);
	fromIdStr = Integer::ToString(fromid);

	baseUrl.Replace(L"{FROM_ID}", fromIdStr);
	baseUrl.Replace(L"{ID}", 	  postIdStr);

	AppResource* pAppResource = VKUApp::GetInstance()->GetAppResource();

	r = layout.Construct();
	r = Panel::Construct(layout, rect);
	r = SetSize(Dimension(rect.width, rect.height));

	filename = (out == 1) ? L"doc_out.#.png" : L"doc_in.#.png";
	_pBitmap = pAppResource->GetBitmapN(filename);

	_pIcon = new LocalImageView();
	_pIcon->Construct(Rectangle(0, 0, 72, 72), L"icon_document.png");

	r = AddControl(_pIcon);

	nameLabel = new Label();
	nameLabel->Construct(Rectangle(0, 0, rect.width-72, 35), L"Wall Post");
	nameLabel->SetMargin(0, 0);
	nameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	nameLabel->SetTextConfig(40, LABEL_TEXT_STYLE_BOLD);

	r = AddControl(nameLabel);

	layout.SetRelation(*_pIcon, this, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	layout.SetCenterAligned(*_pIcon, CENTER_ALIGN_VERTICAL);
	layout.SetMargin(*_pIcon, 0, 0, 0, 0);

	layout.SetRelation(*nameLabel, this, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	layout.SetRelation(*nameLabel, _pIcon, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	layout.SetMargin(*nameLabel, 0, 10, 0, 0);
	layout.SetCenterAligned(*nameLabel, CENTER_ALIGN_VERTICAL);
	layout.SetHorizontalFitPolicy(*nameLabel, FIT_POLICY_CONTENT);

	SetSize(Dimension(rect.width, 90));
	SetPropagatedTouchEventListener(this);

	return r;
}

bool MessageWallElement::OnTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	touchAllowed = true;
	return true;
}

bool MessageWallElement::OnTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	if (!touchAllowed)
		return false;

	AppControl* pAc = AppManager::FindAppControlN(L"tizen.internet",
							 L"http://tizen.org/appcontrol/operation/view");
	if (pAc) {
		pAc->Start(&baseUrl, null, null, null);
		delete pAc;
	}

	return true;
}

bool MessageWallElement::OnTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	touchAllowed = false;
	return false;
}

result MessageWallElement::OnDraw() {
	Canvas *pCanvas = GetCanvasN();

	if (pCanvas) {
		pCanvas->DrawNinePatchedBitmap(pCanvas->GetBounds(), *_pBitmap);

		delete pCanvas;
	}

	return E_SUCCESS;
}
