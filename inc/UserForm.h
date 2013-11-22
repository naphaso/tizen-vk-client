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

#include "IAPIRequestListener.h"

class UserForm:
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public Tizen::Ui::Controls::IFormBackEventListener,
	public Tizen::Ui::IActionEventListener,
	public IAPIRequestListener {
public:
	UserForm();
	virtual ~UserForm();
	bool Initialize();

	void OpenDialog();
	void MakeCall();
	void DeleteFriend();
	void AddFriend();
	void Leave();
	void CheckIsFriends();
	void EnableAction(Tizen::Web::Json::JsonObject * jsonObject);

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

	// IAPIRequestListener
	virtual void OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object);

private:
	Tizen::Web::Json::JsonObject * _pUserJson;

};

#endif /* USERFORM_H_ */
