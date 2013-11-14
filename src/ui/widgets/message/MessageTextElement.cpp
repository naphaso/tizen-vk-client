/*
 * MessageTextElement.cpp
 *
 *  Created on: Nov 14, 2013
 *      Author: igorglotov
 */

#include "MessageTextElement.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;

static const int TEXT_FONT_SIZE = 35;

MessageTextElement::~MessageTextElement() {
//	delete pEnrichedText;
	delete pFont;
}

result MessageTextElement::SetText(const String & text) {
	int width, height, textActualLen;
	result r = E_SUCCESS;
	Dimension textDim;

	TextElement *pTextElement = new TextElement();
	r = pTextElement->Construct(text);
	TryCatch(r == E_SUCCESS, , "Failed TextElement");
	r = pTextElement->SetTextColor(Color::GetColor(COLOR_ID_WHITE));
	TryCatch(r == E_SUCCESS, , "Failed SetTextColor");
	r = pTextElement->SetFont(*pFont);
	TryCatch(r == E_SUCCESS, , "Failed SetFont");

//	if (pEnrichedText->GetTextElementCount() > 0) {
//		r = pEnrichedText->RemoveAll(true);
//		TryCatch(r == E_SUCCESS, , "Failed pEnrichedText->RemoveAllTextElements");
//	}

	r = pEnrichedText->Add(*pTextElement);
	TryCatch(r == E_SUCCESS, , "Failed Add textElement");


	height = pEnrichedText->GetTotalLineHeight();
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed pEnrichedText->GetTotalLineHeight");

	r = pEnrichedText->GetTextExtent(0, text.GetLength(), textDim, textActualLen);
	TryCatch(r == E_SUCCESS, , "Failed GetTextExtent");
	width = GetSize().width < textDim.width ? GetSize().width : textDim.width;
	AppLog("MessageTextElement Size: %d x %d", width, height);

	r = SetSize(width, height);
	TryCatch(r == E_SUCCESS, , "Failed SetSize");

	return r;

CATCH:
	AppLogException("MessageTextElement::SetText is failed.", GetErrorMessage(r));
	return r;
}

result MessageTextElement::Construct(const Rectangle & rect) {
	result r = E_SUCCESS;

	r = Panel::Construct(rect);
	TryCatch(r == E_SUCCESS, , "Failed Panel::Construct");

	pFont = new Font();
	pFont->Construct(FONT_STYLE_PLAIN, TEXT_FONT_SIZE);

	pEnrichedText = new EnrichedText();
	r = pEnrichedText->Construct(Dimension(rect.width, rect.height));
	TryCatch(r == E_SUCCESS, , "Failed pEnrichedText->Construct");

	return r;

CATCH:
	AppLogException("$${Function:Construct} is failed.", GetErrorMessage(r));
	return r;
}

result MessageTextElement::OnDraw(void) {
	result r = E_SUCCESS;
	Canvas * pCanvas = GetCanvasN();

	r = pCanvas->DrawText(Point(0, 0), *pEnrichedText);
	TryCatch(r == E_SUCCESS, , "Failed DrawText");

	delete pCanvas;
	return r;

	CATCH:
	    AppLogException("$${Function:Construct} is failed.", GetErrorMessage(r));
	    return r;
}
