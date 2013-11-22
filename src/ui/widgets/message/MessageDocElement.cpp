/*
 * MessageDocElement.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "MessageDocElement.h"
#include "JsonParseUtils.h"
#include "VKU.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base;
using namespace Tizen::Web::Json;
using namespace Tizen::App;

MessageDocElement::MessageDocElement() {
	_pBitmap = null;
}

MessageDocElement::~MessageDocElement() {
	delete _pBitmap;
}

result MessageDocElement::Construct(const Tizen::Graphics::Rectangle & rect, JsonObject * docObject, int out) {
	result r = E_SUCCESS;

	RelativeLayout layout;
	layout.Construct();

	AppResource* pAppResource = VKUApp::GetInstance()->GetAppResource();

	String docName;
	JsonParseUtils::GetString(*docObject, L"title", docName);

	r = Panel::Construct(layout, rect);
	r = SetSize(Dimension(rect.width, rect.height));

	const String filename = (out == 1) ? L"doc_out.#.png" : L"doc_in.#.png";

	_pBitmap = pAppResource->GetBitmapN(filename);
//	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed pAppResource->GetBitmapN");

	_pIcon = new LocalImageView();
	_pIcon->Construct(Rectangle(0, 0, 72, 72), L"icon_document.png");

	r = AddControl(_pIcon);

	Label *docLabel = new Label();
	docLabel->Construct(Rectangle(0, 0, rect.width-72, 72), docName);
	docLabel->SetMargin(0, 0);
	docLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	r = AddControl(docLabel);

	layout.SetRelation(*_pIcon, this, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	layout.SetCenterAligned(*_pIcon, CENTER_ALIGN_VERTICAL);
	layout.SetMargin(*_pIcon, 0, 0, 0, 0);

//	layout.SetRelation(*docLabel, this, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	layout.SetRelation(*docLabel, _pIcon, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	layout.SetCenterAligned(*docLabel, CENTER_ALIGN_VERTICAL);
//	layout.SetMargin(*docLabel, 0, 20, 0, 0);
	layout.SetHorizontalFitPolicy(*docLabel, FIT_POLICY_PARENT);

	SetSize(Dimension(rect.width, 90));

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
