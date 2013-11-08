/*
 * RoundedAvatar.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: igorglotov
 */

#include "RoundedAvatar.h"

using namespace Tizen::Ui;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;

RoundedAvatar::RoundedAvatar(const AvatarType & type) {
	r = E_SUCCESS;

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

	pAvatarRounding = pAppResource->GetBitmapN(bitmapName);
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN thumbnail_grouped_list");

	SetLastResult(r);
	return;
CATCH:
	SetLastResult(r);
	return;
}

result RoundedAvatar::Construct(Tizen::Graphics::Rectangle & rect, Tizen::Base::String & avatarPath) {
	r = E_SUCCESS;
	rect.width = 108;
	rect.height = 108;

	Panel::Construct(rect, GROUP_STYLE_NONE);

	delete pAvatarRounding;
	return r;
}

RoundedAvatar::~RoundedAvatar() {
	// TODO Auto-generated destructor stub
}

result RoundedAvatar::OnDraw(void) {
	r = E_SUCCESS;
	Canvas * pCanvas = GetCanvasN();

	r = pCanvas->DrawBitmap(Point(0, 0), *pAvatarRounding);
	TryCatch(r == E_SUCCESS, , "Failed DrawBitmap pAvatarRounding");

	delete pCanvas;
	return r;

CATCH:
    AppLogException("$${Function:OnDraw} is failed.", GetErrorMessage(r));
    delete pCanvas;
    return r;
}
