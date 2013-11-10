/*
 * SceneRegister.h
 *
 *  Created on: Nov 4, 2013
 *      Author: igorglotov
 */

#ifndef SCENEREGISTER_H_
#define SCENEREGISTER_H_

extern const wchar_t* SCENE_DIALOG;
extern const wchar_t* SCENE_MAIN;
extern const wchar_t* SCENE_LOGIN;

class SceneRegister {
public:
	static void RegisterAllScenes();

	SceneRegister();
	virtual ~SceneRegister();
};

#endif /* SCENEREGISTER_H_ */
