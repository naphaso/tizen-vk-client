/*
 * VideoviewPanel.cpp
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#include "VideoviewPanel.h"
#include "AppResourceId.h"
#include "ObjectCounter.h"

VideoviewPanel::VideoviewPanel() {
	CONSTRUCT(L"VideoviewPanel");
}

VideoviewPanel::~VideoviewPanel() {
	DESTRUCT(L"VideoviewPanel");
}

bool VideoviewPanel::Initialize() {
	result r = Panel::Construct(IDC_PANEL_VIDEO);
	return r == E_SUCCESS ? true : false;
}
