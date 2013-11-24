#ifndef _VKUCONTACTSPANEL_H_
#define _VKUCONTACTSPANEL_H_

#include <FBase.h>
#include <FUi.h>

#include "ContactsRetrieveListener.h"
#include "ContactsTableProvider.h"
#include "VKUAuthConfig.h"
#include "Requests.h"
#include "IUserSelectedListener.h"
#include "UsersPanel.h"

class VKUContactsPanel:
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public IUserSelectedListener {

// Construction
public:
	VKUContactsPanel(void);
	virtual ~VKUContactsPanel(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

	// IUserSelectedListener
	virtual void OnUserSelected(const Tizen::Web::Json::JsonObject * userJson);

protected:

// Generated call-back functions
public:

	void ClearItems();

private:
	UsersPanel *_usersPanel;
//	ContactsRetrieveListener* pContactsRetrieveListener;
//	ContactsTableProvider* pProvider;
};

#endif
