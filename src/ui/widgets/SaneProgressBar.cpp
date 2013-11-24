/*
 * SaneProgressBar.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: Igor Glotov
 */

#include "SaneProgressBar.h"

using namespace Tizen::Ui;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;

SaneProgressBar::SaneProgressBar() {
	// TODO Auto-generated constructor stub

}

SaneProgressBar::~SaneProgressBar() {
	// TODO Auto-generated destructor stub
}

result SaneProgressBar::Construct(const Tizen::Graphics::Rectangle & rect, int minn, int maxx) {
	result r = Panel::Construct(rect, GROUP_STYLE_NONE);

	max = maxx;
	min = minn;
	current = 0;



	return r;
}

result SaneProgressBar::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	Dimension screenSize = GetSize();

	double ratio = (double) current / (double) max;

	// TODO: paddigns
	r = pCanvas->FillRoundRectangle(Color::GetColor(COLOR_ID_BLACK), Rectangle(Point(0, 0), screenSize), Dimension(5, 5));
	TryCatch(r == E_SUCCESS, , "Failed DrawRoundRectangle");

	r = pCanvas->FillRoundRectangle(Color(0x569cdb, false), Rectangle(0, 0, (int) (ratio*screenSize.width), screenSize.height), Dimension(5, 5));
	TryCatch(r == E_SUCCESS, , "Failed DrawRoundRectangle");

	delete pCanvas;
	return r;

CATCH:
	AppLogException("AttachElement::OnDraw is failed. %s", GetErrorMessage(r));
	delete pCanvas;
	return r;
}
