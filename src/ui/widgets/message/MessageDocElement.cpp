/*
 * MessageDocElement.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "MessageDocElement.h"

using namespace Tizen::Graphics;

MessageDocElement::MessageDocElement() {
	// TODO Auto-generated constructor stub

}

MessageDocElement::~MessageDocElement() {
	// TODO Auto-generated destructor stub
}

result MessageDocElement::Construct(const Tizen::Graphics::Rectangle & rect) {
	result r = E_SUCCESS;
	r = Panel::Construct(rect);
	r = SetSize(Dimension(rect.width, rect.height));

	return r;
}

result MessageDocElement::OnDraw() {
	Canvas *pCanvas = GetCanvasN();

	if (pCanvas) {
		pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_BLUE));
		pCanvas->DrawRectangle(pCanvas->GetBounds());

		delete pCanvas;
	}

	return E_SUCCESS;
}
