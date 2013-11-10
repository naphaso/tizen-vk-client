
#include "AppResourceId.h"
#include "VKSettingsPanel.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;


VKSettingsPanel::VKSettingsPanel(void)
{
}

VKSettingsPanel::~VKSettingsPanel(void)
{
}

bool
VKSettingsPanel::Initialize()
{
	Panel::Construct(IDC_PANEL_SETTINGS);

	return true;
}

result
VKSettingsPanel::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result
VKSettingsPanel::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}



void
VKSettingsPanel::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO: Add your implementation codes here

}

void
VKSettingsPanel::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO: Add your implementation codes here

}
