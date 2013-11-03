
#include "AppResourceId.h"
#include "VKUContactsPanel.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;


VKUContactsPanel::VKUContactsPanel(void)
{
}

VKUContactsPanel::~VKUContactsPanel(void)
{
}

bool
VKUContactsPanel::Initialize()
{
	Panel::Construct(IDC_PANEL_CONTACTS);

	return true;
}

result
VKUContactsPanel::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result
VKUContactsPanel::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}



void
VKUContactsPanel::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO: Add your implementation codes here

}

void
VKUContactsPanel::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO: Add your implementation codes here

}
