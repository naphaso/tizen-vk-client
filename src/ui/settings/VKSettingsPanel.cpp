#include "AppResourceId.h"
#include "VKSettingsPanel.h"
#include "../../api/VKUAuthConfig.h"
#include "JsonParseUtils.h"
#include "WebImageView.h"
#include "../../api/VKUApi.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Web::Json;

VKSettingsPanel::VKSettingsPanel(void) {
	pProvider = new SettingsSectionTableProvider();
}

VKSettingsPanel::~VKSettingsPanel(void) {
}

bool VKSettingsPanel::Initialize() {
	Panel::Construct(IDC_PANEL_SETTINGS);

	return true;
}

result VKSettingsPanel::OnInitializing(void) {
	result r = E_SUCCESS;

	SectionTableView* pSettingsTable = static_cast<SectionTableView *>(GetControl(IDC_SECTIONTABLEVIEW_SETTINGS, true));
	pSettingsTable->SetItemProvider(pProvider);
	pAvatarPanel = static_cast<Panel *>(GetControl(IDC_PANEL_SETTINGS_AVATAR, true));
	pLabelName = static_cast<Label *>(GetControl(IDC_LABEL_SETTINGS_NAME, true));

	VKUApi::GetInstance().CreateRequest("users.get", this)->Put(L"fields", "photo_max")->Submit();

	return r;
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

void VKSettingsPanel::OnResponseN(Tizen::Web::Json::JsonObject *object) {
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

void VKSettingsPanel::OnError() {

}
