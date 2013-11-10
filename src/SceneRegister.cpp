/*
 * SceneRegister.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: igorglotov
 */

#include "SceneRegister.h"
#include "VKUFormFactory.h"
#include "AppResourceId.h"
#include <FUi.h>

using namespace Tizen::Ui::Scenes;

const wchar_t* SCENE_DIALOG = L"VKUDialogScene";
const wchar_t* SCENE_MAIN = L"VKUMainScene";
const wchar_t* SCENE_LOGIN = L"VKULoginScene";


SceneRegister::SceneRegister() {
	// TODO Auto-generated constructor stub

}

SceneRegister::~SceneRegister() {
	// TODO Auto-generated destructor stub
}

void SceneRegister::RegisterAllScenes() {
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	pSceneManager->RegisterScene(SCENE_DIALOG, IDF_DIALOG, IDC_PANEL_DIALOG);
	pSceneManager->RegisterScene(SCENE_MAIN, IDF_MAIN, IDC_PANEL_DIALOGS);
//	pSceneManager->RegisterScene(SCENE_LOGIN, IDF_DIALOG, );
}
