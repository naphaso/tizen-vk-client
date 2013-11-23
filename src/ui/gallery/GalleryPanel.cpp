/*
 * GalleryPanel.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#include "GalleryPanel.h"
#include "AppResourceId.h"
#include <FUi.h>
#include "ObjectCounter.h"

using namespace Tizen::Ui::Scenes;

GalleryPanel::GalleryPanel() {
	CONSTRUCT(L"GalleryPanel");
}

GalleryPanel::~GalleryPanel() {
	DESTRUCT(L"GalleryPanel");
}

bool GalleryPanel::Initialize() {
	result r = Panel::Construct(IDC_PANEL_GALLERY);
	return r == E_SUCCESS ? true : false;
}

void GalleryPanel::OnActionPerformed(const Control& source, int actionId) {
//	SceneManager* pSceneManager = SceneManager::GetInstance();

	switch(actionId) {

	}

}
