#include "AppResourceId.h"
#include "VKULogin.h"
#include "VKUAuthConfig.h"
#include "SceneRegister.h"
#include "VKU.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::App;


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

	SetFormBackEventListener(this);

//	Button* pButton_login = static_cast<Button*>(GetControl(IDC_BUTTON_LOGIN));
//	if (pButton_login) {
//		pButton_login->SetActionId(ACTION_LOGIN);
//		pButton_login->AddActionEventListener(*this);
//	}
	return r;
}

result VKULogin::OnTerminating(void) {
	result r = E_SUCCESS;

	return r;
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

void VKULogin::OnFormBackRequested(Tizen::Ui::Controls::Form& source) {
//	if (pPopup->GetShowState()) {
//		pPopup->SetShowState(false);
//		return;
//	}

	AppLog("Back requested. Finishing app");
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}

