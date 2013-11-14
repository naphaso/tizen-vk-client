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


RoundedAvatar::RoundedAvatar(const AvatarType & type, const PlaceholderType & placeholderType) {
	result r = E_SUCCESS;

	pAvatar = null;
	AppResource* pAppResource = VKUApp::GetInstance()->GetAppResource();
	String bitmapName = L"thumbnail_list.png", placeholderBitmapName;

	switch (type) {
	case AVATAR_NORMAL:
		bitmapName = L"thumbnail_list.png";
		break;
	case AVATAR_UNREAD:
		bitmapName = L"thumbnail_list_unread.png";
		break;
	case HEADER_BLUE:
		bitmapName = L"thumbnail_header.png";
		break;
	}

	switch (placeholderType) {
	case PLACEHOLDER_USER:
		placeholderBitmapName = L"no_photo_user.png";
		break;

	case PLACEHOLDER_CHAT:
		placeholderBitmapName = L"no_photo_group.png";
		break;
	}

	pAvatarRounding = pAppResource->GetBitmapN(bitmapName, BITMAP_PIXEL_FORMAT_ARGB8888);
	pAvatarPlaceholder = pAppResource->GetBitmapN(placeholderBitmapName, BITMAP_PIXEL_FORMAT_ARGB8888);

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
//	Rectangle newRect(0, 0, 108, 108);

	imageUrl = avatarPath;
	AppLog("construct rounded avatar based on url: %ls", avatarPath.GetPointer());

	Panel::Construct(rect, GROUP_STYLE_NONE);

//	VKUApp::GetInstance()->GetBitmapCache()->TakeBitmap(imageUrl, this);

	return r;
}

RoundedAvatar::~RoundedAvatar() {
	AppLog("rounded avatar destructor");
//	VKUApp::GetInstance()->GetBitmapCache()->ReleaseBitmap(imageUrl, this);

//	if (pAvatarPlaceholder)
//		delete pAvatarPlaceholder;

//	if (pAvatarRounding)
//		delete pAvatarRounding;
	//delete pAvatarRounding;
}

result RoundedAvatar::OnDraw(void) {
	result r = E_SUCCESS;
	Canvas * pCanvas = GetCanvasN();

	if (pCanvas != null) {

		if (pAvatar != null) {
			r = pCanvas->DrawBitmap(pCanvas->GetBounds(), *pAvatar);
		} else {
			r = pCanvas->DrawBitmap(pCanvas->GetBounds(), *pAvatarPlaceholder);
		}

		r = pCanvas->DrawBitmap(pCanvas->GetBounds(), *pAvatarRounding);

		TryCatch(r == E_SUCCESS, , "Failed DrawBitmap pAvatarRounding");

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
//	if(requestId == AVATAR_LOAD_REQUEST) {
//		if (pArgs->GetAt(0) == null)
//			return;
//
//		AppLog("rounded avatar new bitmap received: list size %d", pArgs->GetCount());
//		pAvatar = static_cast<Bitmap *>(pArgs->GetAt(0));
//		AppLog("bitmap pointer: %x", pAvatar);
//		AppLog("Bitmap size %dx%d", pAvatar->GetWidth(), pAvatar->GetHeight());
//		RequestRedraw();
//		delete pAvatarPlaceholder;
//	}

	if(requestId == BITMAP_LOADED) {
		AppLog("bitmap loaded event");
		pAvatar = static_cast<Bitmap *>(pArgs->GetAt(0));
		RequestRedraw();
	}

	delete pArgs;
}
