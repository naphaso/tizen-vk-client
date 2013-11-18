#include "VKUPanelFactory.h"
#include "AppResourceId.h"

#include "VKUDialogsPanel.h"
#include "VKUContactsPanel.h"
#include "VKSettingsPanel.h"
#include "VKUSearchPanel.h"
#include "VKUDialogPanel.h"
#include "LoginPanel.h"
#include "GalleryPanel.h"
#include "VideoviewPanel.h"

using namespace Tizen::Ui::Scenes;

VKUPanelFactory::VKUPanelFactory(void) {

}

VKUPanelFactory::~VKUPanelFactory(void) {

}

Tizen::Ui::Controls::Panel*
VKUPanelFactory::CreatePanelN(const Tizen::Base::String& panelId,
		const Tizen::Ui::Scenes::SceneId& sceneId) {
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Panel* pNewPanel = null;

	if (panelId == IDC_PANEL_DIALOGS) {
		VKUDialogsPanel* pPanel = new VKUDialogsPanel();
		pPanel->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pPanel);
		pNewPanel = pPanel;
	} else if (panelId == IDC_PANEL_CONTACTS) {
		VKUContactsPanel* pPanel = new VKUContactsPanel();
		pPanel->Initialize();
		pNewPanel = pPanel;
	} else if (panelId == IDC_PANEL_SETTINGS) {
		VKSettingsPanel* pPanel = new VKSettingsPanel();
		pPanel->Initialize();
		pNewPanel = pPanel;
	} else if (panelId == IDC_PANEL_SEARCH) {
		VKUSearchPanel* pPanel = new VKUSearchPanel();
		pPanel->Initialize();
		pNewPanel = pPanel;
	} else if (panelId == IDC_PANEL_DIALOG) {
		VKUDialogPanel* pPanel = new VKUDialogPanel();
		pPanel->Initialize();
		pNewPanel = pPanel;
	} else if (panelId == IDC_PANEL_LOGIN) {
		LoginPanel* pPanel = new LoginPanel();
		pPanel->Initialize();
		pNewPanel = pPanel;
	} else if (panelId == IDC_GALLERY) {
		GalleryPanel* pPanel = new GalleryPanel();
		pPanel->Initialize();
		pNewPanel = pPanel;
	} else if (panelId == IDC_PANEL_VIDEO) {
		VideoviewPanel* pPanel = new VideoviewPanel();
		pPanel->Initialize();
		pNewPanel = pPanel;
	}

	return pNewPanel;
}
