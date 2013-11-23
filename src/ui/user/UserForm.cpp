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
#include "Requests.h"
#include "VKUApi.h"
#include "ObjectCounter.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Base;
using namespace Tizen::Web::Json;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::App;

static const int ACTION_ID_WRITE = 321;
static const int ACTION_ID_CALL = 322;
static const int ACTION_ID_DELETE = 666;
static const int ACTION_ID_ACCEPT = 667;

UserForm::UserForm() {
	CONSTRUCT(L"UserForm");
}

UserForm::~UserForm() {
	DESTRUCT(L"UserForm");
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
	GetFooter()->SetItemEnabled(0, false);
	GetFooter()->AddActionEventListener(*this);
	GetFooter()->SetShowState(false);
	GetFooter()->Invalidate(true);

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

	CheckIsFriends();

	return r;
}

void UserForm::CheckIsFriends() {
	int userId;
	JsonParseUtils::GetInteger(*_pUserJson, L"id", userId);

	VKUApi::GetInstance().CreateRequest("friends.areFriends", this)
		->Put(L"user_ids", Integer::ToString(userId))
		->Submit(REQUEST_CHECK_FRIENDS);
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
	Leave();
}

void UserForm::Leave() {
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

	case ACTION_ID_DELETE:
		AppLog("ACTION_ID_DELETE");
		DeleteFriend();
		break;

	case ACTION_ID_ACCEPT:
		AppLog("ACTION_ID_ACCEPT");
		AddFriend();
		break;
	}
}

void UserForm::AddFriend() {
	int userId;
	JsonParseUtils::GetInteger(*_pUserJson, L"id", userId);

	VKUApi::GetInstance().CreateRequest("friends.add", this)
		->Put(L"user_id", Integer::ToString(userId))
		->Submit(REQUEST_ADD_FRIEND);
}

void UserForm::DeleteFriend() {
	MessageBox messageBox;
	String message;

	String name, nextName;
	JsonParseUtils::GetString(*_pUserJson, L"first_name", name);
	name += L" ";
	JsonParseUtils::GetString(*_pUserJson, L"last_name", nextName);
	name += nextName;

	int result = 0, userId;

	JsonParseUtils::GetInteger(*_pUserJson, L"id", userId);

	message = L"Remove " + name + " from friends?";
	messageBox.Construct(L"Confirm", message, MSGBOX_STYLE_OKCANCEL, 10000);
	messageBox.ShowAndWait(result);

	switch (result) {
	case 0:
		return;
		break;
	case MSGBOX_RESULT_OK: {
		VKUApi::GetInstance().CreateRequest("friends.delete", this)
			->Put(L"user_id", Integer::ToString(userId))
			->Submit(REQUEST_DELETE_FRIEND);
	}
	break;
	}
}

void UserForm::OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object) {
	if (requestId == REQUEST_DELETE_FRIEND) {
		AppLog("REQUEST_DELETE_FRIEND");
		CheckIsFriends();
	} else if (requestId == REQUEST_CHECK_FRIENDS) {
		AppLog("REQUEST_CHECK_FRIENDS");
		EnableAction(object);
	} else if (requestId == REQUEST_ADD_FRIEND) {
		AppLog("REQUEST_CHECK_FRIENDS");
		CheckIsFriends();
	}
}

void UserForm::EnableAction(Tizen::Web::Json::JsonObject * jsonObject) {
	result r = E_SUCCESS;
	JsonArray * response;
	JsonObject * status;
	String name;
	int friendStatus;
	String actionStr = L"Remove from friends";

	r = JsonParseUtils::GetArray(jsonObject, L"response", response);
	TryCatch(r == E_SUCCESS, , "Failed JsonParseUtils::GetArray");

	r = JsonParseUtils::GetObject(response, 0, status);
	TryCatch(r == E_SUCCESS, , "Failed JsonParseUtils::GetObject");

	r = JsonParseUtils::GetInteger(*status, L"friend_status", friendStatus);
	TryCatch(r == E_SUCCESS, , "Failed JsonParseUtils::GetObject");

	r = JsonParseUtils::GetString(*_pUserJson, L"first_name", name);

	GetFooter()->RemoveAllItems();

	switch (friendStatus) {
	case 1: {

		GetFooter()->SetShowState(false);
	} break;
	case 0: {
		FooterItem item1;
		item1.Construct(ACTION_ID_ACCEPT);
		item1.SetText(L"Add Friend");
		GetFooter()->AddItem(item1);

		GetFooter()->SetShowState(true);
	} break;
	case 2:
	{

		String str = L"Add " + name + L" back";
		FooterItem item1;
		item1.Construct(ACTION_ID_ACCEPT);
		item1.SetText(str);
		GetFooter()->AddItem(item1);


		GetFooter()->SetShowState(true);
	}	break;

	case 3: {
		FooterItem item2;
		item2.Construct(ACTION_ID_DELETE);
		item2.SetText( L"Remove from friends");
		GetFooter()->AddItem(item2);

		GetFooter()->SetShowState(true);
	}	break;
	}


	GetFooter()->Invalidate(true);

	return;
CATCH:
	AppLogException("EnableAction is failed. %s", GetErrorMessage(r));
	SetLastResult(r);
	return;
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
	String userPhone;
	JsonParseUtils::GetString(*_pUserJson, L"mobile_phone", userPhone);

	String uri = L"tel:" + userPhone;

	AppControl* pAc = AppManager::FindAppControlN(L"tizen.phone",
	                                                 L"http://tizen.org/appcontrol/operation/dial");
	if (pAc) {
		pAc->Start(&uri, null, null, null);
		delete pAc;
	}
}
