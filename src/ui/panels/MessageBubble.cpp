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

MessageBubble::MessageBubble() {
	message = null;
}

MessageBubble::~MessageBubble() {

}

void MessageBubble::setMessage(const String & msg, const int aOut = 0) {
	message = new String(msg);
	out = aOut;
}

result MessageBubble::Construct(const Tizen::Graphics::Dimension& dim) {
	result r = E_SUCCESS;
	VerticalBoxLayout layout;
	RichTextPanel* pRtPanel;
	Dimension baseDim(0, 0);

	r = layout.Construct(VERTICAL_DIRECTION_UPWARD);
	TryCatch(r == E_SUCCESS, , "Failed Construct layout");

	r = Panel::Construct(layout, Rectangle(0, 0, dim.width, dim.height), GROUP_STYLE_NONE);
	TryCatch(r == E_SUCCESS, , "Failed Construct MessageBubble parent");

	if (message != null) {
		pRtPanel = new RichTextPanel();
		pRtPanel->Construct(dim, &message);

		baseDim = pRtPanel->GetSize();
		TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed SetBackgroundColor");

		r = AddControl(pRtPanel);
		TryCatch(r == E_SUCCESS, , "Failed Add message text to MessageBubble");
	}

	r = SetSize(baseDim);
	TryCatch(r == E_SUCCESS, , "Failed SetSize");

	return r;

CATCH:
	AppLogException("$${Function:Construct} is failed.", GetErrorMessage(r));
	return r;
}
result MessageBubble::OnDraw(void) {
	result r = E_SUCCESS;

	if (out == 1) {

	} else {

	}

	return r;

CATCH:
	AppLogException("$${Function:OnDraw} is failed.", GetErrorMessage(r));
	return r;
}
