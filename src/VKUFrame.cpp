#include "VKUFrame.h"
#include "VKUFormFactory.h"
#include "VKUPanelFactory.h"
#include "AppResourceId.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

VKUFrame::VKUFrame(void) {
}

VKUFrame::~VKUFrame(void) {
}

result VKUFrame::OnInitializing(void) {
	result r = E_SUCCESS;

	SceneManager* pSceneManager = SceneManager::GetInstance();
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed SceneManager::GetInstance");

	static VKUFormFactory formFactory;
	static VKUPanelFactory panelFactory;

	r = pSceneManager->RegisterFormFactory(formFactory);
	TryCatch(r == E_SUCCESS, , "Failed RegisterFormFactory");
	r = pSceneManager->RegisterPanelFactory(panelFactory);
	TryCatch(r == E_SUCCESS, , "Failed RegisterPanelFactory");
	r = pSceneManager->RegisterScene(L"workflow");
	TryCatch(r == E_SUCCESS, , "Failed RegisterScene");

	r = pSceneManager->GoForward(SceneTransitionId(ID_SCNT_START));
	TryCatch(r == E_SUCCESS, , "Failed GoForward");

	return r;

	CATCH:

	AppLogException("OnInitializing is failed.", GetErrorMessage(r));
	return r;

}

result VKUFrame::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO:
	// Add your termination code here
	return r;
}
