/*
 * MessageDocElement.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "MessageDocElement.h"
#include "JsonParseUtils.h"
#include "VKU.h"
#include "ObjectCounter.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base;
using namespace Tizen::Web::Json;
using namespace Tizen::App;

MessageDocElement::MessageDocElement() {
	CONSTRUCT(L"MessageDocElement");
	_pBitmap = null;
	_pDocObject = null;
}

MessageDocElement::~MessageDocElement() {
	DESTRUCT(L"MessageDocElement");
	delete _pBitmap;

//	if (_pDocObject)
//		delete _pDocObject;
}

String MessageDocElement::GetSizeString(int size) {
	String sizeStr, postfix = " Bytes";

	if (size > 1000) {
		size = size / 1000;
		postfix = " KB";
	}

	if (size > 1000) {
		size = size / 1000;
		postfix = " MB";
	}

	sizeStr = Integer::ToString(size);
	sizeStr.Append(postfix);

	return sizeStr;
}

result MessageDocElement::Construct(const Tizen::Graphics::Rectangle & rect, JsonObject * docObject, int out) {
	result r = E_SUCCESS;

	_pDocObject = docObject->CloneN();

	RelativeLayout layout;
	layout.Construct();

	AppResource* pAppResource = VKUApp::GetInstance()->GetAppResource();

	String docName;
	JsonParseUtils::GetString(*docObject, L"title", docName);

	int size;
	JsonParseUtils::GetInteger(*docObject, L"size", size);

	r = Panel::Construct(layout, rect);
	r = SetSize(Dimension(rect.width, rect.height));

	const String filename = (out == 1) ? L"doc_out.#.png" : L"doc_in.#.png";

	_pBitmap = pAppResource->GetBitmapN(filename);
//	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed pAppResource->GetBitmapN");

	_pIcon = new LocalImageView();
	_pIcon->Construct(Rectangle(0, 0, 72, 72), L"icon_document.png");

	r = AddControl(_pIcon);

	Label *docLabel = new Label();
	docLabel->Construct(Rectangle(0, 0, rect.width-72, 35), docName);
	docLabel->SetMargin(0, 0);
	docLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	docLabel->SetTextConfig(30, LABEL_TEXT_STYLE_BOLD);

	r = AddControl(docLabel);

	Label *sizeLabel = new Label();
	sizeLabel->Construct(Rectangle(0, 0, rect.width-72, 30), GetSizeString(size));
	sizeLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	sizeLabel->SetTextConfig(25, LABEL_TEXT_STYLE_NORMAL);
	sizeLabel->SetMargin(0, 0);

	r = AddControl(sizeLabel);

	layout.SetRelation(*_pIcon, this, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	layout.SetCenterAligned(*_pIcon, CENTER_ALIGN_VERTICAL);
	layout.SetMargin(*_pIcon, 0, 0, 0, 0);

	layout.SetRelation(*docLabel, this, RECT_EDGE_RELATION_TOP_TO_TOP);
	layout.SetRelation(*docLabel, this, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	layout.SetRelation(*docLabel, _pIcon, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	layout.SetMargin(*docLabel, 0, 10, 10, 0);
	layout.SetHorizontalFitPolicy(*docLabel, FIT_POLICY_CONTENT);

	layout.SetRelation(*sizeLabel, docLabel, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
	layout.SetRelation(*sizeLabel, _pIcon, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	layout.SetMargin(*sizeLabel, 0, 10, 5, 0);
	layout.SetHorizontalFitPolicy(*sizeLabel, FIT_POLICY_CONTENT);

	SetSize(Dimension(rect.width, 90));

	SetPropagatedTouchEventListener(this);

	return r;
}

result MessageDocElement::OnDraw() {
	Canvas *pCanvas = GetCanvasN();

	if (pCanvas) {
		pCanvas->DrawNinePatchedBitmap(pCanvas->GetBounds(), *_pBitmap);

		delete pCanvas;
	}

	return E_SUCCESS;
}

bool MessageDocElement::OnTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	touchAllowed = true;
	return true;
}

bool MessageDocElement::OnTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	if (!touchAllowed)
		return false;

	String url;
	JsonParseUtils::GetString(*_pDocObject, L"url", url);

	AppControl* pAc = AppManager::FindAppControlN(L"tizen.internet",
							 L"http://tizen.org/appcontrol/operation/view");
	if (pAc) {
		pAc->Start(&url, null, null, null);
		delete pAc;
	}

	return true;
}

bool MessageDocElement::OnTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	touchAllowed = false;
	return false;
}
