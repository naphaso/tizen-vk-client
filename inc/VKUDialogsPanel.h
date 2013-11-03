#ifndef _VKU_TAB1_H_
#define _VKU_TAB1_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FUiIme.h>
#include <FGraphics.h>
#include <FWebJson.h>
#include <gl.h>
#include "VKUDialogListItemProvider.h"
#include "IAPIRequestListener.h"

class VKUDialogsPanel
	: public Tizen::Ui::Controls::Panel
	, public Tizen::Ui::Scenes::ISceneEventListener
	, public IAPIRequestListener
{
public:
	VKUDialogsPanel(void);
	virtual ~VKUDialogsPanel(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

	// IAPIRequestListener
	virtual void OnResponseN(Tizen::Web::Json::JsonObject *object);

private:
	VKUDialogListItemProvider provider;
};

#endif // _VKU_TAB1_H_
