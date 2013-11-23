/*
 * RoundedAvatar.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: igorglotov
 */

#include "RoundedAvatar.h"
#include "VKU.h"
#include "SceneRegister.h"
#include "ObjectCounter.h"

using namespace Tizen::Ui;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui::Scenes;

RoundedAvatar::RoundedAvatar(const AvatarType & type, const PlaceholderType & placeholderType) {
	CONSTRUCT(L"RoundedAvatar");
	result r = E_SUCCESS;

	_pUserJson = null;
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
	case BUBBLE_IN:
		bitmapName = L"thumbnail_bubble_in.png";
		break;
	case BUBBLE_OUT:
		bitmapName = L"thumbnail_bubble_out.png";
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

RoundedAvatar::~RoundedAvatar() {
	DESTRUCT(L"RoundedAvatar");
	if (imageUrl.GetLength() != 0)
		VKUApp::GetInstance()->GetBitmapCache()->ReleaseBitmap(imageUrl, this);

	if (_pUserJson)
		delete _pUserJson;
}

result RoundedAvatar::Construct(const Tizen::Graphics::Rectangle & rect, const Tizen::Base::String &avatarPath) {
	result r = E_SUCCESS;

	imageUrl = avatarPath;
	AppLog("construct rounded avatar based on url: %ls", avatarPath.GetPointer());

	Panel::Construct(rect, GROUP_STYLE_NONE);

	if (imageUrl.GetLength() != 0) {
		Bitmap *bitmap = VKUApp::GetInstance()->GetBitmapCache()->TakeBitmap(imageUrl, this);
		if(bitmap != null) {
			pAvatar = bitmap;
		}
	}

	return r;
}

void RoundedAvatar::SetUrl(const Tizen::Base::String & str) {
	imageUrl = str;
	if (str.GetLength() != 0)
		VKUApp::GetInstance()->GetBitmapCache()->TakeBitmap(imageUrl, this);
}

void RoundedAvatar::SetUserJson(Tizen::Web::Json::JsonObject * json) {
	_pUserJson = json->CloneN();

	SetPropagatedTouchEventListener(this);
}

bool RoundedAvatar::OnTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	pressAllowed = true;

	return true;
}

bool RoundedAvatar::OnTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	if (!pressAllowed)
		return false;

	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	ArrayList* pList = new (std::nothrow) ArrayList(SingleObjectDeleter);

	pList->Construct(1);
	pList->Add(_pUserJson->CloneN());

	pSceneManager->GoForward(ForwardSceneTransition(SCENE_USER, SCENE_TRANSITION_ANIMATION_TYPE_LEFT, SCENE_HISTORY_OPTION_ADD_HISTORY), pList);

	return true;
}

bool RoundedAvatar::OnTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) {
	pressAllowed = false;
	return false;
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

	if(requestId == BITMAP_LOADED) {
		AppLog("bitmap loaded event");
		pAvatar = static_cast<Bitmap *>(pArgs->GetAt(0));
		RequestRedraw();
	}

	delete pArgs;
}
