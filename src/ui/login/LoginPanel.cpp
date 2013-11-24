/*
 * LoginPanel.cpp
 *
 *  Created on: Nov 14, 2013
 *      Author: igorglotov
 */

#include "LoginPanel.h"
#include "AppResourceId.h"
#include "VKUAuthConfig.h"
#include "SceneRegister.h"
#include "ObjectCounter.h"

static const int ACTION_LOGIN = 101;
static const int ACTION_SIGNUP = 102;

using namespace Tizen::Ui;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

LoginPanel::LoginPanel() {
	CONSTRUCT(L"LoginPanel");
}

LoginPanel::~LoginPanel() {
	DESTRUCT(L"LoginPanel");
	delete pPopup;
}

bool LoginPanel::Initialize() {
	result r = Panel::Construct(IDC_PANEL_LOGIN);
	return r == E_SUCCESS ? true : false;
}

result LoginPanel::OnInitializing(void) {
	result r = E_SUCCESS;

	pPopup = new (std::nothrow) VKULoginPopup();
	pPopup->Construct();
	pPopup->SetShowState(false);

	Button* pLoginBtn = static_cast<Button*>(GetControl(IDC_BUTTON_LOGIN));

	if (pLoginBtn) {
		pLoginBtn->SetActionId(ACTION_LOGIN);
		pLoginBtn->AddActionEventListener(*this);
	}

	// IDC_BUTTON_REGISTER
	Button* pSignupBtn = static_cast<Button*>(GetControl(IDC_BUTTON_REGISTER));
	if (pSignupBtn) {
		pSignupBtn->SetActionId(ACTION_SIGNUP);
		pSignupBtn->AddActionEventListener(*this);
	}
	return r;
}

void LoginPanel::OnActionPerformed(const Control& source, int actionId) {
	switch(actionId) {
	case ACTION_LOGIN:
		AppLog("Logging in in");
		pPopup->StartLogin(this); // FIXME: free memory
	break;
	case ACTION_SIGNUP:
		pPopup->StartSignup(this);
	break;
	}

}

result LoginPanel::OnTerminating(void) {
	result r = E_SUCCESS;

	return r;
}

void LoginPanel::OnLoginSuccess(const String &accessToken, const String &expiresIn, const String &userId) {
	AppLog("login success: authToken %ls, expiresIn %ls, userId %ls", accessToken.GetPointer(), expiresIn.GetPointer(), userId.GetPointer());
	VKUAuthConfig::Replace(accessToken, expiresIn, userId);

	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->GoForward(ForwardSceneTransition(SCENE_MAIN_DIALOGS));
}

void LoginPanel::OnLoginError(const String &error, const String &description) {
	AppLog("login error: %ls:%ls", error.GetPointer(), description.GetPointer());
}

void LoginPanel::OnSignupSuccess(const String &accessToken, const String &expiresIn, const String &userId) {
	pPopup->SetShowState(false);
}

void LoginPanel::OnSignupError(const String &error, const String &description) {
	AppLog("signup error: %ls:%ls", error.GetPointer(), description.GetPointer());
}
