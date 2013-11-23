/*
 * AttachElement.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#include "AttachElement.h"
#include "VKU.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::App;
using namespace Tizen::Base::Collection;

static const int ACTION_ID_CLOSE = 444;

AttachElement::AttachElement() {
	_loadedBg = null;
	_loadingBg = null;
	_loading = false;
	_listener = null;
}

AttachElement::~AttachElement() {
	if (_loadedBg)
		delete _loadedBg;

	if (_loadingBg)
		delete _loadingBg;
}

result AttachElement::Construct(const Tizen::Graphics::Rectangle & rect) {
	result r = E_SUCCESS;

	RelativeLayout layout;
	Button * closeBtn;
	AppResource* pAppResource = VKUApp::GetInstance()->GetAppResource();

	r = layout.Construct();
	TryCatch(r == E_SUCCESS, , "Failed layout.Construct");

	Panel::Construct(layout, rect);

	_loadedBg = pAppResource->GetBitmapN(L"file_loaded.#.png");
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN file_loaded");

	_loadingBg = pAppResource->GetBitmapN(L"file_loading.#.png");
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN file_loading");

	_closeNormalBmp = pAppResource->GetBitmapN(L"keyboard_close_normal.png");
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN keyboard_close_normal");

	_closePressedBmp = pAppResource->GetBitmapN(L"keyboard_close_press.png");
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN keyboard_close_press");

	closeBtn = new Button();
	r = closeBtn->Construct(Rectangle(0, 0, 45, 45), L"");
	TryCatch(r == E_SUCCESS, , "Failed closeBtn->Construct");

	closeBtn->SetNormalBackgroundBitmap(*_closeNormalBmp);
	closeBtn->SetPressedBackgroundBitmap(*_closePressedBmp);
	closeBtn->SetActionId(ACTION_ID_CLOSE);
	closeBtn->AddActionEventListener(*this);

	r = AddControl(closeBtn);
	TryCatch(r == E_SUCCESS, , "Failed closeBtn->Construct");

	r = layout.SetRelation(*closeBtn, this, RECT_EDGE_RELATION_TOP_TO_TOP);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetRelation(*closeBtn, this, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetRelation");
	r = layout.SetMargin(*closeBtn, 0, 10, 10, 0);
	TryCatch(r == E_SUCCESS, , "Failed layout.SetMargin");

	SetLastResult(r);
	return r;

CATCH:
	AppLogException("AttachElement::Construct is failed. %s", GetErrorMessage(r));
	return r;
}

result AttachElement::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	Dimension screenSize = GetSize();
	Bitmap* pBmp;

	pBmp = (_loading) ? _loadingBg : _loadedBg;

	// TODO: paddigns
	r = pCanvas->DrawNinePatchedBitmap(Rectangle(0, 0, screenSize.width, screenSize.height), *pBmp);
	TryCatch(r == E_SUCCESS, , "Failed DrawNinePatchedBitmap");

	delete pCanvas;
	return r;

CATCH:
	AppLogException("AttachElement::OnDraw is failed. %s", GetErrorMessage(r));
	delete pCanvas;
	return r;
}

void AttachElement::OnActionPerformed(const Tizen::Ui::Control& source, int actionId) {
	if (_listener == null)
		return;

	if (actionId == ACTION_ID_CLOSE) {
		_listener->OnElementRemoveRequest(this);
	}
}
