
#ifndef _VKSETTINGSPANEL_H_
#define _VKSETTINGSPANEL_H_

#include <FBase.h>
#include <FUi.h>
#include <FWebJson.h>

#include "IAPIRequestListener.h"
#include "SettingsSectionTableProvider.h"

class VKSettingsPanel :
	public Tizen::Ui::Controls::Panel,
 	public Tizen::Ui::Scenes::ISceneEventListener,
 	public IAPIRequestListener
{

// Construction
public:
	VKSettingsPanel(void);
	virtual ~VKSettingsPanel(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:


	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

	virtual void OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object);
	virtual void OnError();

private:

	Tizen::Ui::Controls::Label* pLabelName;
	Tizen::Ui::Controls::Panel* pAvatarPanel;

	SettingsSectionTableProvider* pProvider;

};

#endif
