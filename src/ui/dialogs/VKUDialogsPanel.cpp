#include "VKUDialogsPanel.h"
#include "AppResourceId.h"

#include "VKUApi.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Web::Json;
using namespace Tizen::Base;

VKUDialogsPanel::VKUDialogsPanel(void) {
	pProvider = new DialogsTableProvider();
}

VKUDialogsPanel::~VKUDialogsPanel(void) {

}

bool VKUDialogsPanel::Initialize(void) {
	result r = Construct(IDC_PANEL_DIALOGS);
	if (IsFailed(r))
		return false;

	return true;
}

result VKUDialogsPanel::OnInitializing(void) {
	result r = E_SUCCESS;

	// Layout setting
	const Form* pForm = dynamic_cast<Form*>(GetParent());
	RelativeLayout* pRelativeLayout =
			dynamic_cast<RelativeLayout*>(pForm->GetLandscapeLayoutN());
	pRelativeLayout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
	pRelativeLayout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);
	delete pRelativeLayout;
	pRelativeLayout =
			dynamic_cast<RelativeLayout*>(pForm->GetPortraitLayoutN());
	pRelativeLayout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
	pRelativeLayout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);
	delete pRelativeLayout;

	pDialogTableView = static_cast<TableView*>(GetControl(
			IDC_TABLEVIEW_DIALOGS));

	_searchBar = static_cast<SearchBar*>(GetControl(IDC_SEARCHBAR1));
	_searchBar->AddSearchBarEventListener(*pProvider);
	_searchBar->AddTextEventListener(*pProvider);


	pProvider->Construct(pDialogTableView);
	pDialogTableView->SetItemProvider(pProvider);
	pDialogTableView->AddTableViewItemEventListener(*pProvider);

	pProvider->LoadData();

	return r;
}

result VKUDialogsPanel::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void VKUDialogsPanel::OnSceneActivatedN(
		const Tizen::Ui::Scenes::SceneId& previousSceneId,
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		Tizen::Base::Collection::IList* pArgs) {
	// TODO:
	// Add your scene activate code here
	AppLog("OnSceneActivatedN");
}

void VKUDialogsPanel::OnSceneDeactivated(
		const Tizen::Ui::Scenes::SceneId& currentSceneId,
		const Tizen::Ui::Scenes::SceneId& nextSceneId) {
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");
}


