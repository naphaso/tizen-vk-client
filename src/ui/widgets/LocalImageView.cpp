/*
 * LocalImageView.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#include "LocalImageView.h"

#include "VKU.h"
#include "ObjectCounter.h"

using namespace Tizen::Ui;
using namespace Tizen::Graphics;
using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui::Controls;

LocalImageView::LocalImageView() {
	CONSTRUCT(L"LocalImageView");
	pNormalBitmap = null;
}

LocalImageView::~LocalImageView() {
	DESTRUCT(L"LocalImageView");
	if (pNormalBitmap)
		delete pNormalBitmap;
}

result LocalImageView::Construct(const Rectangle & rect, const String & resImageName) {
	result r = E_SUCCESS;
	AppResource* pAppResource = VKUApp::GetInstance()->GetAppResource();

	r = Panel::Construct(rect, GROUP_STYLE_NONE);

	if (resImageName.GetLength() == 0)
		return r;

	pNormalBitmap = pAppResource->GetBitmapN(resImageName);
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN %ls", resImageName.GetPointer());

	return r;
CATCH:
	AppLogException("LocalImageView is failed.", GetErrorMessage(r));
	return r;
}

result LocalImageView::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas *pCanvas = GetCanvasN();

	if (pCanvas && pNormalBitmap) {
		r = pCanvas->DrawBitmap(pCanvas->GetBounds(), *pNormalBitmap);
	}

	delete pCanvas;
	return r;
}
