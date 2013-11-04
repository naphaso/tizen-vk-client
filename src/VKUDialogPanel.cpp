
#include "AppResourceId.h"
#include "VKUDialogPanel.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;


VKUDialogPanel::VKUDialogPanel(void)
{
}

VKUDialogPanel::~VKUDialogPanel(void)
{
}

bool
VKUDialogPanel::Initialize()
{
	Panel::Construct(IDC_PANEL_DIALOG);

	return true;
}

result
VKUDialogPanel::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result
VKUDialogPanel::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}


