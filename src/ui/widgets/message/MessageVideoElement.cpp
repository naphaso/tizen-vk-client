/*
 * MessageVideoElement.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "MessageVideoElement.h"

using namespace Tizen::Graphics;

MessageVideoElement::MessageVideoElement() {
	// TODO Auto-generated constructor stub

}

MessageVideoElement::~MessageVideoElement() {
	// TODO Auto-generated destructor stub
}

result MessageVideoElement::Construct(const Tizen::Graphics::Rectangle & rect) {
	result r = E_SUCCESS;
	r = Panel::Construct(rect);
	r = SetSize(Dimension(rect.width, rect.height));

	return r;
}

result MessageVideoElement::OnDraw() {
	Canvas *pCanvas = GetCanvasN();

	if (pCanvas) {
		pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_RED));
		pCanvas->DrawRectangle(pCanvas->GetBounds());

		delete pCanvas;
	}

	return E_SUCCESS;
}
