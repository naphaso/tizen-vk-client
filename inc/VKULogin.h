
#ifndef _VKULOGIN_H_
#define _VKULOGIN_H_

#include <FBase.h>
#include <FUi.h>

class VLULogin;

#include "IAuthListener.h"

class VKULogin :
	public Tizen::Ui::Controls::Form,
 	public Tizen::Ui::Scenes::ISceneEventListener,
 	public Tizen::Ui::Controls::IFormBackEventListener {

// Construction
public:
	VKULogin(void);
	virtual ~VKULogin(void);
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

	// back
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

private:

};

#endif
