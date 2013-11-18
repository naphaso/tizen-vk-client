/*
 * VideoviewPanel.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#include "VideoviewPanel.h"
#include "AppResourceId.h"

VideoviewPanel::VideoviewPanel() {
	// TODO Auto-generated constructor stub

}

VideoviewPanel::~VideoviewPanel() {
	// TODO Auto-generated destructor stub
}

bool VideoviewPanel::Initialize() {
	result r = Panel::Construct(IDC_PANEL_VIDEO);
	return r == E_SUCCESS ? true : false;
}
