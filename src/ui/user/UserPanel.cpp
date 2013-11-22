/*
 * UserPanel.cpp
 *
 *  Created on: Nov 22, 2013
 *      Author: Igor Glotov
 */

#include "UserPanel.h"
#include "AppResourceId.h"

UserPanel::UserPanel() {
	// TODO Auto-generated constructor stub

}

UserPanel::~UserPanel() {
	// TODO Auto-generated destructor stub
}

bool UserPanel::Initialize() {
	Panel::Construct(IDC_PANEL_USER);

	return true;
}
