#include "AppResourceId.h"
#include "SceneRegister.h"
#include "VKUDialog.h"
#include "VKUDialogPanel.h"
#include "VKUColors.h"
#include "JsonParseUtils.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;

VKUDialog::VKUDialog(void) {
}

VKUDialog::~VKUDialog(void) {
}

bool VKUDialog::Initialize() {
	Form::Construct(IDF_DIALOG);

	return true;
}

result VKUDialog::OnInitializing(void) {
	result r = E_SUCCESS;
	Color headerColor(HEADER_BG_COLOR, false);

	AppLog("Form init");
	// TODO: Add your initialization code here
//	AddKeyEventListener(*this);
	SetFormBackEventListener(this);

	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->AddSceneEventListener(SCENE_DIALOG, *this);

	return r;
}

result VKUDialog::OnTerminating(void) {
	result r = E_SUCCESS;

	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->RemoveSceneEventListener(SCENE_DIALOG, *this);

	// TODO: Add your termination code here

	return r;
}

void VKUDialog::OnSceneActivatedN(
		const Tizen::Ui::Scenes::SceneId& previousSceneId,
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		Tizen::Base::Collection::IList* pArgs) {
	AppLog("Scene activated");

	if (pArgs != null) {
		userJson = static_cast<JsonObject* > (pArgs->GetAt(0));
//		AppLog("Received arg %ls", userJson.GetPointer());

		VKUDialogPanel* pDialogPanel = static_cast<VKUDialogPanel*>(GetControl(IDC_PANEL_DIALOG));
		pDialogPanel->SetUserJson(userJson);
		AppLog("Doing pDialogPanel->LoadMessages");
		pDialogPanel->LoadMessages();
	}

	if (userJson != null) {
		int userId;
		JsonParseUtils::GetInteger(*userJson, L"id", userId);
		VKUApp::GetInstance()->GetService()->SubscribeNotifications(userId);
	}
}

void VKUDialog::OnSceneDeactivated(
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		const Tizen::Ui::Scenes::SceneId& nextSceneId) {

	int userId;
	JsonParseUtils::GetInteger(*userJson, L"id", userId);
	VKUApp::GetInstance()->GetService()->UnsubscribeNotifications(userId);
}

void VKUDialog::OnKeyLongPressed(const Tizen::Ui::Control& source,
		Tizen::Ui::KeyCode keyCode) {
	// TODO: Add your implementation codes here

}

void VKUDialog::OnKeyPressed(const Tizen::Ui::Control& source,
		Tizen::Ui::KeyCode keyCode) {
	// TODO: Add your implementation codes here

}

void VKUDialog::OnKeyReleased(const Tizen::Ui::Control& source,
		Tizen::Ui::KeyCode keyCode) {
	// TODO: Add your implementation codes here

}

// back

void VKUDialog::OnFormBackRequested(Tizen::Ui::Controls::Form& source) {
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	pSceneManager->GoBackward(BackwardSceneTransition(SCENE_MAIN_DIALOGS));
}
