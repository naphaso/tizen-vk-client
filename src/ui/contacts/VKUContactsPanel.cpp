#include "AppResourceId.h"
#include "VKUContactsPanel.h"
#include "VKUApi.h"
#include "UsersPanel.h"
#include "SceneRegister.h"
#include "ObjectCounter.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Json;

VKUContactsPanel::VKUContactsPanel(void) {
	CONSTRUCT(L"VKUContactsPanel");
//	pProvider = new ContactsTableProvider();
}

VKUContactsPanel::~VKUContactsPanel(void) {
	DESTRUCT(L"VKUContactsPanel");
//	delete pProvider;
}

bool VKUContactsPanel::Initialize() {
	Panel::Construct(IDC_PANEL_CONTACTS);

	return true;
}

result VKUContactsPanel::OnInitializing(void) {
	result r = E_SUCCESS;

	Integer userIdInt = Integer(VKUAuthConfig::GetUserId());

	UsersPanel *pUsersPanel = new UsersPanel();
	pUsersPanel->Construct(GetBounds());
	r = AddControl(pUsersPanel);
	pUsersPanel->AddUserSelectedListener(this);

	Form * form = dynamic_cast<Form *>(GetParent());
	RelativeLayout * layout = dynamic_cast<RelativeLayout *>(form->GetLayoutN());
	layout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);

	pUsersPanel->RequestModel(MODEL_TYPE_FRIENDS_ALPHA);

	return r;
}

result VKUContactsPanel::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void VKUContactsPanel::ClearItems() {
	AppLog("CONTACTSEVENT: scene deactivated");
//	GroupedTableView* pTable = static_cast<GroupedTableView*>(GetControl(IDC_GROUPEDTABLEVIEW1));
//	pTable->Invalidate(true);
}

void VKUContactsPanel::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
							   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs) {

}

void VKUContactsPanel::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId) {

}

void VKUContactsPanel::OnUserSelected(const Tizen::Web::Json::JsonObject * userJson) {
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	ArrayList* pList = new (std::nothrow) ArrayList(SingleObjectDeleter);

	pList->Construct(1);
	pList->Add(userJson->CloneN());

	pSceneManager->GoForward(ForwardSceneTransition(SCENE_USER, SCENE_TRANSITION_ANIMATION_TYPE_LEFT, SCENE_HISTORY_OPTION_ADD_HISTORY), pList);

}
