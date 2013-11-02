/*
 * VKULoginPopup.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: Igor Glotov
 */

#include "VKULoginPopup.h"
#include "VKU.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Web::Controls;
using namespace Tizen::Base::Utility;
using namespace Tizen::Io;

result VKULoginPopup::Construct()
{
    result r = E_SUCCESS;

    Popup::Construct(true, Dimension(600,800));

    pWeb = new (std::nothrow) Web();
    Rectangle rect = GetClientAreaBounds();
    pWeb->Construct(rect);
    pWeb->SetLoadingListener(this);

    AddControl(pWeb);


	SetTitleText(L"Popup Test");
	return r;

CATCH:
    AppLogException("Construct is failed.", GetErrorMessage(r));
	return r;
}

void VKULoginPopup::ShowPopup() {
	SetShowState(true);
	Show();
	String url = L"https://oauth.vk.com/authorize?client_id=3966496&scope=notify"\
		 ",friends,photos,audio,video,docs,notes,pages,status,wall,groups,messages,"\
		 "notifications,stats,ads,offline,nohttps,questions,offers"\
		 "&redirect_uri=https://oauth.vk.com/blank.html"\
		 "&display=touch"\
		 "&response_type=token";
	pWeb->LoadUrl(url);
}

void VKULoginPopup::HidePopup() {
	SetShowState(false);
}

bool VKULoginPopup::OnLoadingRequested(const String& url, WebNavigationType type) {
	AppLog("load url: %ls", url.GetPointer());
	return false;
}

void VKULoginPopup::OnLoadingCompleted() {
	String url = pWeb->GetUrl();

	if (url.StartsWith(L"https://oauth.vk.com/blank.html", 0)) {
		Uri uri;
		uri.SetUri(url);
		String params = uri.GetFragment(), section(L"auth"), authToken;
		StringTokenizer strTok(params, L"&");

		Registry reg;
		String regPath(VKUApp::GetInstance()->GetAppDataPath() + L"auth.ini");

		if (File::IsFileExist(regPath)) {
			File::Remove(regPath);
		}

		reg.Construct(regPath, true); // Create a new registry if not exist
		reg.AddSection(section);

		while (strTok.HasMoreTokens()) {
			String currentToken;
			strTok.GetNextToken(currentToken);
			StringTokenizer eqTok(currentToken, L"=");
			AppLog("currentToken=%ls", currentToken.GetPointer());

			if (eqTok.GetTokenCount() == 2) {
				String name, value;
				eqTok.GetNextToken(name);
				eqTok.GetNextToken(value);
				AppLog("name=%ls value=%ls", name.GetPointer(), value.GetPointer());
				reg.AddValue(section, name, value);
			}
		}

		result r = reg.GetValue(section, L"auth_token", authToken);
		if (r == E_SUCCESS) {
			AppLog("token successfully received");
		} else {

		}

		reg.Flush();
	}

	AppLog("completed url: %ls", pWeb->GetUrl().GetPointer());
}
