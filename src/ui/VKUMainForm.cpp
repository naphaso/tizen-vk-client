#include "VKUMainForm.h"
#include "AppResourceId.h"
#include "SceneRegister.h"
#include "VKUColors.h"
#include "VKUContactsPanel.h"
#include "VKUApi.h"
#include "JsonParseUtils.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;

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

	UpdateCounters();
	switch (actionId) {
	case ID_HEADER_MESSAGES:
		ClearContacts();
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_MAIN_DIALOGS));
		break;
	case ID_HEADER_CONTACTS:
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_MAIN_CONTACTS));
		break;
	case ID_HEADER_SEARCH:
		ClearContacts();
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_MAIN_SEARCH));
		break;
	case ID_HEADER_SETTINGS:
		ClearContacts();
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_MAIN_SETTINGS));
		break;
	default:
		break;
	}
}

void VKUMainForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source) {
	AppLog("Back requested. Finishing app");
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}

void VKUMainForm::OnSceneActivatedN(
		const Tizen::Ui::Scenes::SceneId& previousSceneId,
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		Tizen::Base::Collection::IList* pArgs) {
	// TODO: Add your implementation codes here
	UpdateCounters();
}

void VKUMainForm::OnSceneDeactivated(
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		const Tizen::Ui::Scenes::SceneId& nextSceneId) {
	// TODO: Add your implementation codes here

}

void VKUMainForm::ClearContacts() {
	//Frame* frame = VKUApp::GetInstance()->GetFrame(FRAME_NAME);
	//Form* form = frame->GetCurrentForm();
	//if (form->GetName() == IDF_MAIN) {
	VKUContactsPanel* contactsPanel = static_cast<VKUContactsPanel*>(GetControl(IDC_PANEL_CONTACTS));
	if (contactsPanel != null) {
		contactsPanel->ClearItems();
	}
	//}
}

void VKUMainForm::UpdateCounters() {
	VKUApi::GetInstance().CreateRequest("account.getCounters", this)->Put(L"filter", L"messages,friends")->Submit(REQUEST_COUNTERS);
}

void VKUMainForm::OnResponseN(RequestId requestId, JsonObject *object) {
	result r;
	if(requestId != REQUEST_COUNTERS) {
		return;
	}

	JsonObject *response;
	int messages, friends;
	Header *header = GetHeader();

	r = JsonParseUtils::GetObject(object, L"response", response);
	if(r != E_SUCCESS) { return; }



	r = JsonParseUtils::GetInteger(*response, L"messages", messages);
	if(r == E_SUCCESS) {
		header->SetItemNumberedBadgeIcon(0, messages);
	}

	r = JsonParseUtils::GetInteger(*response, L"friends", friends);
	if(r == E_SUCCESS) {
		header->SetItemNumberedBadgeIcon(2, friends);
	}
}
