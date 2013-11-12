/*
 * RoundedAvatar.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: igorglotov
 */

#include "RoundedAvatar.h"
#include "VKU.h"

using namespace Tizen::Ui;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base::Collection;

static const RequestId AVATAR_LOAD_REQUEST = 1;

RoundedAvatar::RoundedAvatar(const AvatarType & type) {
	result r = E_SUCCESS;

	AppResource* pAppResource = VKUApp::GetInstance()->GetAppResource();
	String bitmapName;

	switch (type) {
	case LIST_BLACK:
		bitmapName = L"thumbnail_grouped_list.png";
		break;
	case HEADER_BLUE:
		bitmapName = L"thumbnail_header.png";
		break;
	}

	pAvatarRounding = pAppResource->GetBitmapN(bitmapName, BITMAP_PIXEL_FORMAT_ARGB8888);
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN thumbnail_grouped_list");

	SetLastResult(r);
	return;
CATCH:
	AppLogException("RoundedAvatar is failed.", GetErrorMessage(r));
	SetLastResult(r);
	return;
}

result RoundedAvatar::Construct(const Tizen::Graphics::Rectangle & rect, const Tizen::Base::String &avatarPath) {
	result r = E_SUCCESS;
	Rectangle newRect(0, 0, 108, 108);

	imageUrl = avatarPath;
	AppLog("construct rounded avatar based on url: %ls", avatarPath.GetPointer());
	VKUApp::GetInstance()->GetBitmapCache()->TakeBitmap(imageUrl, AVATAR_LOAD_REQUEST, this, BITMAP_PIXEL_FORMAT_RGB565, 100, 100);

	Panel::Construct(newRect, GROUP_STYLE_NONE);

	return r;
}

RoundedAvatar::~RoundedAvatar() {
	AppLog("rounded avatar destructor");
	//delete pAvatarRounding;
}

result RoundedAvatar::OnDraw(void) {
	result r = E_SUCCESS;
	AppLog("RoundedAvatar::OnDraw start");
	Canvas * pCanvas = GetCanvasN();

	if (pCanvas != null) {
		AppLog("RoundedAvatar::OnDraw do");
		AppLog("Canvas bounds %d.%d %dx%d", pCanvas->GetBounds().x, pCanvas->GetBounds().y, pCanvas->GetBounds().width, pCanvas->GetBounds().height);

		AppLog("Bitmap size %dx%d", pAvatarRounding->GetWidth(), pAvatarRounding->GetHeight());

		r = pCanvas->DrawBitmap(pCanvas->GetBounds(), *pAvatarRounding);
		TryCatch(r == E_SUCCESS, , "Failed DrawBitmap pAvatarRounding");

		AppLog("RoundedAvatar::OnDraw end");
		delete pCanvas;
	}

	return r;

CATCH:
    AppLogException("$${Function:OnDraw} is failed.", GetErrorMessage(r));
    delete pCanvas;
    return r;
}

void RoundedAvatar::OnUserEventReceivedN(RequestId requestId, IList* pArgs) {
	AppLog("rounded avatar event received");
	if(requestId == AVATAR_LOAD_REQUEST) {
		AppLog("rounded avatar new bitmap received: list size %d", pArgs->GetCount());
		pAvatarRounding = VKUApp::GetInstance()->GetBitmapCache()->Take(imageUrl);
		AppLog("bitmap pointer: %x", pAvatarRounding);
		AppLog("Bitmap size %dx%d", pAvatarRounding->GetWidth(), pAvatarRounding->GetHeight());
		RequestRedraw();
	}
}
