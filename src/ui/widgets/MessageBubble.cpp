/*
 * MessageBubble.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: igorglotov
 */

#include "MessageBubble.h"

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::App;
using namespace Tizen::Base::Collection;

static const int BUBBLE_ITEM_SPACING = 10;

MessageBubble::MessageBubble() {
	result r = E_SUCCESS;
	message = null;

	AppResource* pAppResource = VKUApp::GetInstance()->GetAppResource();

	pBubbleIn = pAppResource->GetBitmapN(L"bubble_in.#.png");
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN bubble_in");

	pBubbleOut = pAppResource->GetBitmapN(L"bubble_out.#.png");
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetBitmapN bubble_out");

	SetLastResult(r);
	return;

CATCH:
	AppLogException("$${Function:MessageBubble} is failed.", GetErrorMessage(r));
	return;
}

MessageBubble::~MessageBubble() {
	delete pBubbleIn;
	delete pBubbleOut;
}

void MessageBubble::SetOut(int out) {
	this->out = out;
}

result MessageBubble::Construct(const Tizen::Graphics::Dimension& dim) {
	result r = E_SUCCESS;
	r = itemLayout.Construct(VERTICAL_DIRECTION_UPWARD);

	placeholderLayout.Construct();
	pPlaceholderPanel = new Panel();
	pPlaceholderPanel->Construct(itemLayout, Rectangle(0, 0, dim.width, dim.height));

	TryCatch(r == E_SUCCESS, , "Failed Construct layout");

	r = Panel::Construct(placeholderLayout, Rectangle(0, 0, dim.width, dim.height), GROUP_STYLE_NONE);
	TryCatch(r == E_SUCCESS, , "Panel::Construct");

	AddControl(pPlaceholderPanel);

	placeholderLayout.SetRelation(*pPlaceholderPanel, *this, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	placeholderLayout.SetRelation(*pPlaceholderPanel, *this, RECT_EDGE_RELATION_RIGHT_TO_RIGHT);
	placeholderLayout.SetRelation(*pPlaceholderPanel, *this, RECT_EDGE_RELATION_TOP_TO_TOP);

	pElements = new ArrayList();
	r = pElements->Construct();
	return r;

CATCH:
	AppLogException("MessageBubble::Construct is failed.", GetErrorMessage(r));
	return r;
}

Dimension MessageBubble::GetPlaceholderSize() {
	int width = 0, height = 0;

	for (int i=0; i<pElements->GetCount(); i++) {
		MessageElement *pElement = static_cast<MessageElement *>(pElements->GetAt(i));

		if (width < pElement->GetWidth())
			width = pElement->GetWidth();

		height += pElement->GetHeight();

		if (i+1 < pElements->GetCount())
			height += BUBBLE_ITEM_SPACING;

	}

	return Dimension(width, height);
}

result MessageBubble::AddElement(MessageElement * pElement) {
	result r = E_SUCCESS;
	Dimension mySize, placeholderSize;

	if (out == 1) {
		r = placeholderLayout.SetMargin(*pPlaceholderPanel, 10, 30, 10, 10);
	} else {
		r = placeholderLayout.SetMargin(*pPlaceholderPanel, 30, 10, 10, 10);
	}
	TryCatch(r == E_SUCCESS, , "Failed placeholderLayout.SetMargin");

	r = pElements->Add(pElement);
	TryCatch(r == E_SUCCESS, , "Failed pElements->Add");


	r = pPlaceholderPanel->AddControl(pElement);
	TryCatch(r == E_SUCCESS, , "pPlaceholderPanel->AddControl");


	itemLayout.SetSpacing(*pElement, BUBBLE_ITEM_SPACING);


//	r = AddControl(pPlaceholderPanel);
//	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	mySize = GetSize();
	placeholderSize = GetPlaceholderSize();
	pPlaceholderPanel->SetSize(placeholderSize);

	SetSize(Dimension(placeholderSize.width+40, placeholderSize.height+20));

	AppLog("pPlaceholderPanel size: %dx%d", pPlaceholderPanel->GetWidth(), pPlaceholderPanel->GetHeight());
	AppLog("Bubble size: %dx%d", GetWidth(), GetHeight());
	return r;

CATCH:
	AppLogException("MessageBubble::AddElement is failed. : %s", GetErrorMessage(r));
	return r;
}

result MessageBubble::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	Dimension screenSize = GetSize();
	Bitmap* pBubble;

	pBubble = (out == 1) ? pBubbleOut : pBubbleIn;

	// TODO: paddigns
	r = pCanvas->DrawNinePatchedBitmap(Rectangle(0, 0, screenSize.width, screenSize.height), *pBubble);
	TryCatch(r == E_SUCCESS, , "Failed DrawNinePatchedBitmap");

	delete pCanvas;
	return r;

CATCH:
	AppLogException("$${Function:OnDraw} is failed.", GetErrorMessage(r));
	delete pCanvas;
	return r;
}
