/*
 * VKULoginPopup.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: Igor Glotov
 */

#include "VKULoginPopup.h"
#include "VKU.h"
#include "VKUConfig.h"
#include "VKUUtils.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Controls;
using namespace Tizen::Base::Utility;
using namespace Tizen::Io;
using namespace Tizen::Ui;

result VKULoginPopup::Construct() {
	result r = E_SUCCESS;
	Rectangle rect;
	AppLog("VKULoginPopup::Construct");


	r = Popup::Construct(false, Dimension(600, 800));
	TryCatch(r == E_SUCCESS, , "Failed Construct");


	rect = GetClientAreaBounds();

	pWeb = new (std::nothrow) Web();
	TryCatch(r == GetLastResult(), r = GetLastResult(), "Failed Construct");

	r = pWeb->Construct(rect);
	TryCatch(r == E_SUCCESS, , "Failed Construct");

	pWeb->SetLoadingListener(this);
	r = GetLastResult();
	TryCatch(r == E_SUCCESS, , "Failed SetLoadingListener");

	r = AddControl(pWeb);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	SetPropagatedKeyEventListener(this);

	AppLog("LoginPopup constructed");
	return r;

	CATCH:
	AppLogException("Construct is failed.", GetErrorMessage(r));
	return r;
}

void VKULoginPopup::StartLogin(IAuthListener *listener) {
	result r;
	this->authListener = listener;
	AppLog("VKULoginPopup::StartAuth");

	r = SetShowState(true);
	TryCatch(r == E_SUCCESS, , "Failed SetShowState");
	r = Show();
	TryCatch(r == E_SUCCESS, , "Failed Show");

	pWeb->LoadUrl(VKU_LOGIN_URL);
	r = GetLastResult();
	TryCatch(r == E_SUCCESS, , "Failed LoadUrl");

	AppLog("VKULoginPopup::StartAuth done");

	return;
	CATCH:
	AppLogException("StartAuth is failed.", GetErrorMessage(r));
	return;
}

void VKULoginPopup::StartSignup(IAuthListener *listener) {
	result r;
	this->authListener = listener;
	AppLog("VKULoginPopup::StartAuth");

	r = SetShowState(true);
	TryCatch(r == E_SUCCESS, , "Failed SetShowState");
	r = Show();
	TryCatch(r == E_SUCCESS, , "Failed Show");

	pWeb->LoadUrl(VKU_SIGNUP_URL);
	r = GetLastResult();
	TryCatch(r == E_SUCCESS, , "Failed LoadUrl");

	AppLog("VKULoginPopup::StartAuth done");

	return;
	CATCH:
	AppLogException("StartAuth is failed.", GetErrorMessage(r));
	return;
}

void VKULoginPopup::OnLoadingCompleted() {
	String url = pWeb->GetUrl();

	if (url.StartsWith(L"https://oauth.vk.com/blank.html", 0)) {
		Uri uri;
		uri.SetUri(url);

		String query = uri.GetQuery();
		String fragment = uri.GetFragment();

		if(!fragment.IsEmpty()) {
			IMap *params = ParseQueryStringN(fragment);
			String accessToken(L"access_token");
			String expiresIn(L"expires_in");
			String userId(L"user_id");

			if(params->ContainsKey(accessToken) && params->ContainsKey(expiresIn) && params->ContainsKey(userId)) {
				String accessTokenValue(*static_cast<String*>(params->GetValue(accessToken)));
				String expiresInValue(*static_cast<String*>(params->GetValue(expiresIn)));
				String userIdValue(*static_cast<String*>(params->GetValue(userId)));

				SetShowState(false);

				authListener->OnLoginSuccess(accessTokenValue, expiresInValue, userIdValue);
			} else {
				String errorValue(L"error_unknown");
				String errorDescription(L"Unknown error");

				SetShowState(false);

				authListener->OnLoginError(errorValue, errorDescription);
			}

			delete params;
		} else if(!query.IsEmpty()) {
			IMap *params = ParseQueryStringN(query);
			String error(L"error");
			String error_description(L"error_description");
			if(params->ContainsKey(error) && params->ContainsKey(error_description)) {
				String errorValue(*static_cast<String*>(params->GetValue(error)));
				String errorDescriptionValue(*static_cast<String*>(params->GetValue(error_description)));

				SetShowState(false);

				authListener->OnLoginError(errorValue, errorDescriptionValue);
			} else {
				String errorValue(L"error_unknown");
				String errorDescription(L"Unknown error");

				SetShowState(false);

				authListener->OnLoginError(errorValue, errorDescription);
			}

			delete params;
		}
	}
}

bool VKULoginPopup::OnKeyReleased(Control& source, const KeyEventInfo& keyEventInfo) {
   KeyCode key = keyEventInfo.GetKeyCode();
   if (key == KEY_BACK || key == KEY_ESC)
   {
      Popup* pPopup = static_cast< Popup * >(&source);
      pPopup->SetShowState(false);
      pPopup->Invalidate(true);
   }

   return false;
}
