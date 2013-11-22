/*
 * UserForm.cpp
 *
 *  Created on: Nov 22, 2013
 *      Author: Igor Glotov
 */

#include "UserForm.h"
#include "AppResourceId.h"
#include "SceneRegister.h"
#include "JsonParseUtils.h"
#include "WebImageView.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Base;
using namespace Tizen::Web::Json;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;

static const int ACTION_ID_WRITE = 321;
static const int ACTION_ID_CALL = 322;

UserForm::UserForm() {
	// TODO Auto-generated constructor stub

}

UserForm::~UserForm() {
	// TODO Auto-generated destructor stub
}

bool UserForm::Initialize() {
	Form::Construct(IDF_USER);

	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->AddSceneEventListener(SCENE_USER, *this);

	SetFormBackEventListener(this);

	return true;
}

result UserForm::InitScene() {
	result r = E_SUCCESS;

	Panel * pImagePlaceholder = dynamic_cast<Panel *>(GetControl(IDC_PANEL_USER_AVATAR, true));

	String avatarPath;
	r = JsonParseUtils::GetString(*_pUserJson, L"photo_200", avatarPath);

	if (r != E_SUCCESS) {
		r = JsonParseUtils::GetString(*_pUserJson, L"photo_100", avatarPath);
	}

	int hasMobile;
	JsonParseUtils::GetInteger(*_pUserJson, L"has_mobile", hasMobile);

	WebImageView * pAvatar = new WebImageView();
	pAvatar->Construct(Rectangle(0, 0, 300, 300), avatarPath);
	pImagePlaceholder->AddControl(pAvatar);

	Button * pWriteButton = dynamic_cast<Button *>(GetControl(IDC_BUTTON_USER_WRITETO, true));
	pWriteButton->SetActionId(ACTION_ID_WRITE);
	pWriteButton->AddActionEventListener(*this);

	Button * pCallButton = dynamic_cast<Button *>(GetControl(IDC_BUTTON_USER_CALLTO, true));
	pCallButton->SetShowState(hasMobile == 1);

	pCallButton->AddActionEventListener(*this);

	String name, nextName;
	JsonParseUtils::GetString(*_pUserJson, L"first_name", name);
	name += L" ";
	JsonParseUtils::GetString(*_pUserJson, L"last_name", nextName);
	name += nextName;

	GetHeader()->SetTitleText(name);
//	GetHeader()->

	if (hasMobile == 1) {
		String phone;
		JsonParseUtils::GetString(*_pUserJson, L"mobile_phone", phone);
		if (phone.GetLength() == 0) {
			pCallButton->SetShowState(false);
		} else {
			pCallButton->SetText(L"Call " + phone);
			pCallButton->SetActionId(ACTION_ID_CALL);
		}
	}

	pCallButton->Invalidate(true);

	return r;
}

// ISceneEventListener
void UserForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
							   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs) {
	AppLog("User scene activated");

	if (pArgs != null) {
		_pUserJson = static_cast<JsonObject* > (pArgs->GetAt(0));
		InitScene();
	}
}

void UserForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId) {
	AppLog("User scene deactivated");
	delete _pUserJson;
}

// IFormBackEventListener
void UserForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source) {
	AppLog("You can't leave Omsk");
	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->GoBackward(BackwardSceneTransition(SCENE_TRANSITION_ANIMATION_TYPE_RIGHT));
}

result UserForm::OnInitializing(void) {
	result r = E_SUCCESS;
	AppLog("UserForm::OnInitializing");

	return r;
}

result UserForm::OnTerminating(void) {
	result r = E_SUCCESS;
	AppLog("UserForm::OnInitializing");

	return r;
}

void UserForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId) {
	switch (actionId) {
	case ACTION_ID_CALL:
		MakeCall();
		break;

	case ACTION_ID_WRITE:
		OpenDialog();
		break;
	}
}

void UserForm::OpenDialog() {
	ArrayList* pList = new (std::nothrow) ArrayList(SingleObjectDeleter);

	JsonObject *dialogJson = new JsonObject();
	dialogJson->Construct();

	int uid;
	JsonParseUtils::GetInteger(*_pUserJson, L"id", uid);

	const String * userId = new String(L"user_id");
	JsonNumber *const userIdNumber = new JsonNumber(uid);
	dialogJson->Add(userId, userIdNumber);

	const String * userJson = new String(L"user_json");
	JsonObject *const constPtr = _pUserJson->CloneN();
	dialogJson->Add(userJson, constPtr);

	pList->Construct(1);
	pList->Add(dialogJson);

	SceneManager* pSceneManager = SceneManager::GetInstance();
	pSceneManager->GoForward(ForwardSceneTransition(SCENE_DIALOG, SCENE_TRANSITION_ANIMATION_TYPE_RIGHT), pList);
}

void UserForm::MakeCall() {

}
