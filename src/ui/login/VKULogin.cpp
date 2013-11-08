#include "AppResourceId.h"
#include "VKULogin.h"
#include "VKULoginPopup.h"
#include "api/VKUAuthConfig.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;


VKULogin::VKULogin(void) {
}

VKULogin::~VKULogin(void) {
}

bool VKULogin::Initialize() {
	Form::Construct(IDF_LOGIN);

	return true;
}

result VKULogin::OnInitializing(void) {
	result r = E_SUCCESS;

	Button* pButton_login = static_cast<Button*>(GetControl(IDC_BUTTON_LOGIN));
	if (pButton_login) {
		pButton_login->SetActionId(ACTION_LOGIN);
		pButton_login->AddActionEventListener(*this);
	}
	return r;
}

result VKULogin::OnTerminating(void) {
	result r = E_SUCCESS;

	return r;
}

void VKULogin::OnActionPerformed(const Control& source, int actionId) {
	SceneManager* pSceneManager = SceneManager::GetInstance();


	switch(actionId) {
	case ACTION_LOGIN: {
		
		VKULoginPopup* pPopup = new (std::nothrow) VKULoginPopup();
		pPopup->Construct();
		pPopup->StartAuth(this); // FIXME: free memory
	}; break;
	case ACTION_SIGNUP: {

	}; break;
	}

	//pSceneManager->GoForward(SceneTransitionId(ID_SCNT_4));

}

void VKULogin::OnSceneActivatedN(
		const SceneId& previousSceneId,
		const SceneId& currentSceneId,
		Tizen::Base::Collection::IList* pArgs) {


}

void VKULogin::OnSceneDeactivated(
		const SceneId& currentSceneId,
		const SceneId& nextSceneId) {


}

void VKULogin::OnSuccess(const String &accessToken, const String &expiresIn, const String &userId) {
	AppLog("login success: authToken %ls, expiresIn %ls, userId %ls", accessToken.GetPointer(), expiresIn.GetPointer(), userId.GetPointer());
	VKUAuthConfig::Replace(accessToken, expiresIn, userId);

	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->GoForward(SceneTransitionId(ID_SCNT_LOGIN_SUCCESS));
}

void VKULogin::OnError(const String &error, const String &description) {
	AppLog("login error: %ls:%ls", error.GetPointer(), description.GetPointer());
}
