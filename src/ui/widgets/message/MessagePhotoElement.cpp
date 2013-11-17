/*
 * MessagePhotoElement.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#include "MessagePhotoElement.h"

using namespace Tizen::Graphics;

MessagePhotoElement::MessagePhotoElement() {
	pImageView = null;
}

MessagePhotoElement::~MessagePhotoElement() {
	delete pImageView;
}

result MessagePhotoElement::Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Base::String & imageUrl) {
	result r = E_SUCCESS;
	r = Panel::Construct(rect);
	r = SetSize(Dimension(rect.width, rect.height));

	url = imageUrl;
	pImageView = new WebImageView();
	r = pImageView->Construct(rect, imageUrl);

	r = AddControl(pImageView);

	return r;
}

void MessagePhotoElement::SetUrl(Tizen::Base::String & aurl) {
	url = aurl;
}

result MessagePhotoElement::OnDraw() {
	result r = Panel::OnDraw();

	Canvas *pCanvas = GetCanvasN();

	if (pCanvas) {
		pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_GREEN));
		pCanvas->DrawRectangle(pCanvas->GetBounds());

		delete pCanvas;
	}

	return E_SUCCESS;
}
