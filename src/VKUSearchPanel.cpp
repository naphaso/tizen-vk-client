
#include "AppResourceId.h"
#include "VKUSearchPanel.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;


VKUSearchPanel::VKUSearchPanel(void)
{
}

VKUSearchPanel::~VKUSearchPanel(void)
{
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

	// TODO: Add your initialization code here

	return r;
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
