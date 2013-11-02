
#include "AppResourceId.h"
#include "VKULogin.h"
#include "VKULoginPopup.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;


VKULogin::VKULogin(void)
{
}

VKULogin::~VKULogin(void)
{
}

bool
VKULogin::Initialize()
{
	Form::Construct(IDF_LOGIN);

	return true;
}

result
VKULogin::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	Button* pButton_login = static_cast<Button*>(GetControl(IDC_BUTTON_LOGIN));  
	if(pButton_login)
	{
		pButton_login->SetActionId(101);
		pButton_login->AddActionEventListener(*this);
	}
	return r;
}

result
VKULogin::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}



void
VKULogin::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	VKULoginPopup* pPopup = new VKULoginPopup();
	pPopup->Construct();
	pPopup->ShowPopup();
	//pSceneManager->GoForward(SceneTransitionId(ID_SCNT_4));
	// TODO: Add your implementation codes here

}

void
VKULogin::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO: Add your implementation codes here

}

void
VKULogin::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO: Add your implementation codes here

}
