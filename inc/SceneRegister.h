/*
 * SceneRegister.h
 *
 *  Created on: Nov 4, 2013
 *      Author: igorglotov
 */

#ifndef SCENEREGISTER_H_
#define SCENEREGISTER_H_

extern const wchar_t* SCENE_DIALOG;
extern const wchar_t* SCENE_LOGIN;

extern const wchar_t* SCENE_MAIN_DIALOGS;
extern const wchar_t* SCENE_MAIN_CONTACTS;
extern const wchar_t* SCENE_MAIN_SEARCH;
extern const wchar_t* SCENE_MAIN_SETTINGS;
extern const wchar_t* SCENE_GALLERY;
extern const wchar_t* SCENE_VIDEOVIEW;
extern const wchar_t* SCENE_USER;

class SceneRegister {
public:
	static void RegisterAllScenes();

	SceneRegister();
	virtual ~SceneRegister();
};

#endif /* SCENEREGISTER_H_ */
