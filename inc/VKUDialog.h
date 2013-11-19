
#ifndef _VKUDIALOG_H_
#define _VKUDIALOG_H_

#include <FBase.h>
#include <FUi.h>
#include <FWebJson.h>

class VKUDialog :
	public Tizen::Ui::Controls::Form,
 	public Tizen::Ui::Scenes::ISceneEventListener,
 	public Tizen::Ui::IKeyEventListener,
	public Tizen::Ui::Controls::IFormBackEventListener
{

// Construction
public:
	VKUDialog(void);
	virtual ~VKUDialog(void);
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

	virtual void OnKeyLongPressed(const Tizen::Ui::Control& source, Tizen::Ui::KeyCode keyCode);
	virtual void OnKeyPressed(const Tizen::Ui::Control& source, Tizen::Ui::KeyCode keyCode);
	virtual void OnKeyReleased(const Tizen::Ui::Control& source, Tizen::Ui::KeyCode keyCode);

	// back
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

private:
	Tizen::Web::Json::JsonObject* dialogJson;
};

#endif
