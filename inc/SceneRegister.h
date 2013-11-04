/*
 * SceneRegister.h
 *
 *  Created on: Nov 4, 2013
 *      Author: igorglotov
 */

#ifndef SCENEREGISTER_H_
#define SCENEREGISTER_H_

extern const wchar_t* SCENE_DIALOG;

class SceneRegister {
public:
	static void RegisterAllScenes();

	SceneRegister();
	virtual ~SceneRegister();
};

#endif /* SCENEREGISTER_H_ */
