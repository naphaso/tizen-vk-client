#include "AppResourceId.h"
#include "VKSettingsPanel.h"
#include "VKUAuthConfig.h"
#include "JsonParseUtils.h"
#include "WebImageView.h"
#include "VKUApi.h"
#include "Requests.h"
#include "ObjectCounter.h"
#include "VKU.h"
#include <FSystem.h>
#include <FShell.h>

using namespace Tizen::System;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Web::Json;
using namespace Tizen::Io;
using namespace Tizen::Shell;

static const int ACTION_ID_SIGNOUT = 223;

VKSettingsPanel::VKSettingsPanel(void) {
	CONSTRUCT(L"VKSettingsPanel");
	pProvider = new SettingsSectionTableProvider();
}

VKSettingsPanel::~VKSettingsPanel(void) {
	DESTRUCT(L"VKSettingsPanel");
}

bool VKSettingsPanel::Initialize() {
	Panel::Construct(IDC_PANEL_SETTINGS);

	return true;
}

result VKSettingsPanel::OnInitializing(void) {
	result r = E_SUCCESS;

	SectionTableView* pSettingsTable = static_cast<SectionTableView *>(GetControl(IDC_SECTIONTABLEVIEW_SETTINGS, true));
	pSettingsTable->SetItemProvider(pProvider);
	pSettingsTable->AddSectionTableViewItemEventListener(*pProvider);
	pAvatarPanel = static_cast<Panel *>(GetControl(IDC_PANEL_SETTINGS_AVATAR, true));
	pLabelName = static_cast<Label *>(GetControl(IDC_LABEL_SETTINGS_NAME, true));

	Button * signout = dynamic_cast<Button *>(GetControl(IDC_BUTTON_SETTINGS_SIGNOUT, true));
	signout->SetActionId(ACTION_ID_SIGNOUT);
	signout->AddActionEventListener(*this);

	String signoutText;
	VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_SIGN_OUT", signoutText);
	signout->SetText(signoutText);

	VKUApi::GetInstance().CreateRequest("users.get", this)->Put(L"fields", "photo_max")->Submit(REQUEST_GET_MYSELF);

	return r;
}

void VKSettingsPanel::OnActionPerformed(const Tizen::Ui::Control& source, int actionId) {
	if (actionId == ACTION_ID_SIGNOUT) {
		String regPath(VKUApp::GetInstance()->GetAppDataPath() + L"auth.ini");
		File::Remove(regPath);

		NotificationRequest request;
		request.SetBadgeNumber(0);

		NotificationManager notificationManager;
		notificationManager.Construct();
		notificationManager.NotifyByAppId(L"iEl2RaVlnG.VKU", request);

		VKUApp::GetInstance()->Terminate();
	}
}

result VKSettingsPanel::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void VKSettingsPanel::OnSceneActivatedN(
		const Tizen::Ui::Scenes::SceneId& previousSceneId,
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		Tizen::Base::Collection::IList* pArgs) {
	AppLog("Settings Scene activated");

}

void VKSettingsPanel::OnSceneDeactivated(
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		const Tizen::Ui::Scenes::SceneId& nextSceneId) {
	AppLog("Settings Scene deactivated");

}

void VKSettingsPanel::OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object) {
	if (requestId == REQUEST_GET_MYSELF) {
		JsonArray* resp;

		JsonParseUtils::GetArray(object, L"response", resp);

		WebImageView *pWebImage;

		JsonObject* item;

		IJsonValue *itemValue;
		resp->GetAt(0, itemValue);
		item = static_cast<JsonObject *>(itemValue);

		String firstName, lastName, photoMax;

		JsonParseUtils::GetString(*item, L"first_name", firstName);
		JsonParseUtils::GetString(*item, L"last_name", lastName);
		JsonParseUtils::GetString(*item, L"photo_max", photoMax);

		AppLog("Avatar URL %ls", photoMax.GetPointer());

		pWebImage = new WebImageView();
		pWebImage->Construct(Tizen::Graphics::Rectangle(0, 0, 200, 200), photoMax);

		pAvatarPanel->AddControl(pWebImage);
		pAvatarPanel->RequestRedraw(true);

		pLabelName->SetText(firstName + L" " + lastName);
	}
}

void VKSettingsPanel::OnError() {

}
