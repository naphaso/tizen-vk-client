
#include "AppResourceId.h"
#include "VKUSearchPanel.h"
#include "ObjectCounter.h"
#include "VKU.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

static const int ACTION_ID_SYNC = 123445;
VKUSearchPanel::VKUSearchPanel(void) {
	CONSTRUCT(L"VKUSearchPanel");
}

VKUSearchPanel::~VKUSearchPanel(void) {
	DESTRUCT(L"VKUSearchPanel");
}

bool
VKUSearchPanel::Initialize()
{
	Panel::Construct(IDC_PANEL_SEARCH);

	return true;
}

result
VKUSearchPanel::OnInitializing(void)
{
	result r = E_SUCCESS;

	Button *syncButton = dynamic_cast<Button *>(GetControl(IDC_BUTTON_SYNC, true));
	syncButton->SetActionId(ACTION_ID_SYNC);
	syncButton->AddActionEventListener(*this);

	return r;
}

void VKUSearchPanel::OnActionPerformed(const Tizen::Ui::Control& source, int actionId) {
	if (ACTION_ID_SYNC) {
		VKUApp::GetInstance()->GetService()->ContactsSync();
		Button *syncButton = dynamic_cast<Button *>(GetControl(IDC_BUTTON_SYNC, true));
		syncButton->SetActionId(0);
		syncButton->SetText("In progress. Check your addressbook.");
	}
}

result
VKUSearchPanel::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}



void
VKUSearchPanel::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO: Add your implementation codes here

}

void
VKUSearchPanel::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO: Add your implementation codes here

}
