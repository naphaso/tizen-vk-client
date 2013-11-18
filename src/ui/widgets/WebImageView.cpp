/*
 * WebImageView.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "WebImageView.h"
#include "VKU.h"

using namespace Tizen::Ui;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base::Collection;

WebImageView::WebImageView() {
	pImageBitmap = null;
}

WebImageView::~WebImageView() {
	VKUApp::GetInstance()->GetBitmapCache()->ReleaseBitmap(imageUrl, this);
//	if (pImageBitmap)
//		delete pImageBitmap;
}

result WebImageView::Construct(const Tizen::Graphics::Rectangle & rect, const Tizen::Base::String &bitmapPath) {
	result r = E_SUCCESS;

	imageUrl = bitmapPath;
	AppLog("WebImageView url: %ls", bitmapPath.GetPointer());

	Panel::Construct(rect, GROUP_STYLE_NONE);

	VKUApp::GetInstance()->GetBitmapCache()->TakeBitmap(imageUrl, this);

	return r;


}

void WebImageView::OnUserEventReceivedN(RequestId requestId, IList* pArgs) {
	AppLog("WebImageView::OnUserEventReceivedN");

	if(requestId == BITMAP_LOADED) {
		AppLog("bitmap loaded event");
		pImageBitmap = static_cast<Bitmap *>(pArgs->GetAt(0));
		RequestRedraw();
	}

	delete pArgs;
}

result WebImageView::OnDraw(void) {
	result r = E_SUCCESS;
	Canvas * pCanvas = GetCanvasN();

	if (pCanvas != null) {

		if (pImageBitmap != null) {
			r = pCanvas->DrawBitmap(pCanvas->GetBounds(), *pImageBitmap);
			TryCatch(r == E_SUCCESS, , "Failed pCanvas->DrawBitmap");
		} else {
			pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_BLACK));
			pCanvas->SetBackgroundColor(Color::GetColor(COLOR_ID_BLACK));
			r = pCanvas->DrawRectangle(pCanvas->GetBounds());
			TryCatch(r == E_SUCCESS, , "Failed pCanvas->DrawBitmap");
		}

		delete pCanvas;
	}

	return r;

CATCH:
    AppLogException("WebImageView::OnDraw is failed. %s", GetErrorMessage(r));
    delete pCanvas;
    return r;
}
