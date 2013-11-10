#include "VKUDialogsPanel.h"
#include "AppResourceId.h"

#include "../../api/VKUApi.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Web::Json;
using namespace Tizen::Base;

VKUDialogsPanel::VKUDialogsPanel(void)
{

}

VKUDialogsPanel::~VKUDialogsPanel(void)
{

}

bool
VKUDialogsPanel::Initialize(void)
{
	result r = Construct(IDC_PANEL_DIALOGS);
	if (IsFailed(r))
		return false;

	return true;
}

result
VKUDialogsPanel::OnInitializing(void)
{
	result r = E_SUCCESS;

	// Layout setting
	const Form* pForm = dynamic_cast<Form*>(GetParent());
	RelativeLayout* pRelativeLayout = dynamic_cast<RelativeLayout*>(pForm->GetLandscapeLayoutN());
	pRelativeLayout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
	pRelativeLayout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);
	delete pRelativeLayout;
	pRelativeLayout = dynamic_cast<RelativeLayout*>(pForm->GetPortraitLayoutN());
	pRelativeLayout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
	pRelativeLayout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);
	delete pRelativeLayout;

	ListView* pDialogListView = static_cast<ListView*>(GetControl(IDC_LISTVIEW_DIALOGS));
	pDialogListView->SetItemProvider(provider);
	pDialogListView->AddListViewItemEventListener(provider);


	VKUApi::GetInstance().CreateRequest("messages.getDialogs", this)
			->Put(L"count", L"150")
			->Submit();

	return r;
}

result
VKUDialogsPanel::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
VKUDialogsPanel::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO:
	// Add your scene activate code here
	AppLog("OnSceneActivatedN");
}

void
VKUDialogsPanel::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");
}


void VKUDialogsPanel::OnResponseN(Tizen::Web::Json::JsonObject *object) {

	provider.SetDialogsJson(object);

	ListView* pDialogListView = static_cast<ListView*>(GetControl(IDC_LISTVIEW_DIALOGS));

	pDialogListView->UpdateList();
	pDialogListView->RequestRedraw(true);
}
