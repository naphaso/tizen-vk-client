/*
 * UserPanel.cpp
 *
 *  Created on: Nov 22, 2013
 *      Author: Igor Glotov
 */

#include "UserPanel.h"
#include "AppResourceId.h"
#include "ObjectCounter.h"

UserPanel::UserPanel() {
	CONSTRUCT(L"UserPanel");
}

UserPanel::~UserPanel() {
	DESTRUCT(L"UserPanel");
}

bool UserPanel::Initialize() {
	Panel::Construct(IDC_PANEL_USER);

	return true;
}
