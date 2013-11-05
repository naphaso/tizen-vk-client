#include "AppResourceId.h"
#include "SceneRegister.h"
#include "VKUDialog.h"
#include "VKUDialogPanel.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

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
		userId = String(*static_cast< String* > (pArgs->GetAt(0)));
		AppLog("Received arg %ls", userId.GetPointer());

		VKUDialogPanel* pDialogPanel = static_cast<VKUDialogPanel*>(GetControl(IDC_PANEL_DIALOG));
		pDialogPanel->LoadMessages(userId);
	}
}

void VKUDialog::OnSceneDeactivated(
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		const Tizen::Ui::Scenes::SceneId& nextSceneId) {
	// TODO: Add your implementation codes here

}

void VKUDialog::OnKeyLongPressed(const Tizen::Ui::Control& source,
		Tizen::Ui::KeyCode keyCode) {
	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->GoForward(SceneTransitionId(ID_SCNT_4));

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
	AppLog("Back requested...");

	pSceneManager->GoBackward(BackwardSceneTransition(MainScene));
}
