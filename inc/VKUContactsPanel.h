#ifndef _VKUCONTACTSPANEL_H_
#define _VKUCONTACTSPANEL_H_

#include <FBase.h>
#include <FUi.h>

#include "ContactsRetrieveListener.h"
#include "ContactsTableProvider.h"
#include "../src/api/VKUAuthConfig.h"

class VKUContactsPanel: public Tizen::Ui::Controls::Panel,
		public Tizen::Ui::Scenes::ISceneEventListener {

// Construction
public:
	VKUContactsPanel(void);
	virtual ~VKUContactsPanel(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:

	virtual void OnSceneActivatedN(
			const Tizen::Ui::Scenes::SceneId& previousSceneId,
			const Tizen::Ui::Scenes::SceneId& currentSceneId,
			Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(
			const Tizen::Ui::Scenes::SceneId& currentSceneId,
			const Tizen::Ui::Scenes::SceneId& nextSceneId);

private:
	ContactsRetrieveListener* pContactsRetrieveListener;
	ContactsTableProvider* pProvider;
};

#endif
