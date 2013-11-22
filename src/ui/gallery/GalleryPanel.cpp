/*
 * GalleryPanel.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#include "GalleryPanel.h"
#include "AppResourceId.h"
#include <FUi.h>

using namespace Tizen::Ui::Scenes;

GalleryPanel::GalleryPanel() {
	// TODO Auto-generated constructor stub

}

GalleryPanel::~GalleryPanel() {
	// TODO Auto-generated destructor stub
}

bool GalleryPanel::Initialize() {
	result r = Panel::Construct(IDC_PANEL_GALLERY);
	return r == E_SUCCESS ? true : false;
}

void GalleryPanel::OnActionPerformed(const Control& source, int actionId) {
	SceneManager* pSceneManager = SceneManager::GetInstance();

	switch(actionId) {

	}

}
