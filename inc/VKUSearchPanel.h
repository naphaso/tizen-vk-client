
#ifndef _VKUSEARCHPANEL_H_
#define _VKUSEARCHPANEL_H_

#include <FBase.h>
#include <FUi.h>



class VKUSearchPanel :
	public Tizen::Ui::Controls::Panel,
 	public Tizen::Ui::IActionEventListener,
 	public Tizen::Ui::Scenes::ISceneEventListener
{

// Construction
public:
	VKUSearchPanel(void);
	virtual ~VKUSearchPanel(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);


	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);
};

#endif
