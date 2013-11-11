#include "VKUMainForm.h"
#include "AppResourceId.h"
#include "SceneRegister.h"
#include "VKUColors.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Graphics;

VKUMainForm::VKUMainForm(void) {
}

VKUMainForm::~VKUMainForm(void) {
}

bool VKUMainForm::Initialize(void) {
	Construct(IDF_MAIN);

	return true;
}

result VKUMainForm::OnInitializing(void) {
	result r = E_SUCCESS;
	Color headerColor(HEADER_BG_COLOR, false);

	// TODO:
	// Add your initialization code here
	Header* pHeader = GetHeader();
	if (pHeader) {
		pHeader->AddActionEventListener(*this);
		pHeader->SetColor(headerColor);
	}

	// Setup back event listener
	SetFormBackEventListener(this);

	return r;
}

result VKUMainForm::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO:
	// Add your termination code here
	return r;
}

void VKUMainForm::OnActionPerformed(const Tizen::Ui::Control& source,
		int actionId) {
	SceneManager* pSceneManager = SceneManager::GetInstance();

	AppAssert(pSceneManager);

	switch (actionId) {
	case ID_HEADER_MESSAGES:
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_MAIN_DIALOGS));
		break;
	case ID_HEADER_CONTACTS:
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_MAIN_CONTACTS));
		break;
	case ID_HEADER_SEARCH:
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_MAIN_SEARCH));
		break;
	case ID_HEADER_SETTINGS:
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_MAIN_SETTINGS));
		break;
	default:
		break;
	}
}

void VKUMainForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source) {
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}

void VKUMainForm::OnSceneActivatedN(
		const Tizen::Ui::Scenes::SceneId& previousSceneId,
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		Tizen::Base::Collection::IList* pArgs) {
	// TODO: Add your implementation codes here

}

void VKUMainForm::OnSceneDeactivated(
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		const Tizen::Ui::Scenes::SceneId& nextSceneId) {
	// TODO: Add your implementation codes here

}
