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
#include "ObjectCounter.h"

using namespace Tizen::Ui::Scenes;

const wchar_t* SCENE_DIALOG = L"VKUDialogScene";
const wchar_t* SCENE_LOGIN = L"VKULoginScene";

const wchar_t* SCENE_MAIN_DIALOGS = L"VKUMainDialogs";
const wchar_t* SCENE_MAIN_CONTACTS = L"VKUMainContacts";
const wchar_t* SCENE_MAIN_SEARCH = L"VKUMainSearch";
const wchar_t* SCENE_MAIN_SETTINGS = L"VKUMainSettings";
const wchar_t* SCENE_GALLERY = L"VKUMainGallery";
const wchar_t* SCENE_VIDEOVIEW = L"VKUVideoView";
const wchar_t* SCENE_USER = L"VKUSceneUser";

SceneRegister::SceneRegister() {
	CONSTRUCT(L"SceneRegister");
}

SceneRegister::~SceneRegister() {
	DESTRUCT(L"SceneRegister");
}

void SceneRegister::RegisterAllScenes() {
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	pSceneManager->RegisterScene(SCENE_DIALOG, IDF_DIALOG, IDC_PANEL_DIALOG);
	pSceneManager->RegisterScene(SCENE_LOGIN, IDF_LOGIN, IDC_PANEL_LOGIN);

	pSceneManager->RegisterScene(SCENE_MAIN_DIALOGS, IDF_MAIN, IDC_PANEL_DIALOGS);
	pSceneManager->RegisterScene(SCENE_MAIN_CONTACTS, IDF_MAIN, IDC_PANEL_CONTACTS);
	pSceneManager->RegisterScene(SCENE_MAIN_SEARCH, IDF_MAIN, IDC_PANEL_SEARCH);
	pSceneManager->RegisterScene(SCENE_MAIN_SETTINGS, IDF_MAIN, IDC_PANEL_SETTINGS);
	pSceneManager->RegisterScene(SCENE_GALLERY, IDF_IMAGEVIEW, IDC_GALLERY);
	pSceneManager->RegisterScene(SCENE_VIDEOVIEW, IDF_VIDEOVIEW, IDC_PANEL_VIDEO);
	pSceneManager->RegisterScene(SCENE_USER, IDF_USER, IDC_PANEL_USER);
}
