/*
 * MessageAudioElement.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "MessageAudioElement.h"

using namespace Tizen::Graphics;

MessageAudioElement::MessageAudioElement() {
	// TODO Auto-generated constructor stub

}

MessageAudioElement::~MessageAudioElement() {
	// TODO Auto-generated destructor stub
}

result MessageAudioElement::Construct(const Tizen::Graphics::Rectangle & rect) {
	result r = E_SUCCESS;
	r = Panel::Construct(rect);
	r = SetSize(Dimension(rect.width, rect.height));

	return r;
}

result MessageAudioElement::OnDraw() {
	Canvas *pCanvas = GetCanvasN();

	if (pCanvas) {
		pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_YELLOW));
		pCanvas->DrawRectangle(pCanvas->GetBounds());

		delete pCanvas;
	}

	return E_SUCCESS;
}
