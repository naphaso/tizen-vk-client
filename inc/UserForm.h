/*
 * UserForm.h
 *
 *  Created on: Nov 22, 2013
 *      Author: Igor Glotov
 */

#ifndef USERFORM_H_
#define USERFORM_H_

#include <FUi.h>
#include <FBase.h>
#include <FWebJson.h>

class UserForm:
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public Tizen::Ui::Controls::IFormBackEventListener,
	public Tizen::Ui::IActionEventListener {
public:
	UserForm();
	virtual ~UserForm();
	bool Initialize();

	void OpenDialog();
	void MakeCall();
	result InitScene();

	// Form
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	// ISceneEventListener
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

	// IFormBackEventListener
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	// IActionEventListener
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
private:
	Tizen::Web::Json::JsonObject * _pUserJson;

};

#endif /* USERFORM_H_ */
