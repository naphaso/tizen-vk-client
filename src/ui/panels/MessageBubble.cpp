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

void MessageBubble::SetMessage(const String & msg, const int aOut = 0) {
	message = new String(msg);
	out = aOut;
}

result MessageBubble::Construct(const Tizen::Graphics::Dimension& dim) {
	result r = E_SUCCESS;
	VerticalBoxLayout layout;
	RichTextPanel* pRtPanel;
	Dimension baseDim(dim);
	Dimension textDim(0, 0);

	baseDim.width -= BUBBLE_HORIZONTAL_SIDE_MARGIN;

	RelativeLayout textWrapLayout;
	textWrapLayout.Construct();
	Panel* textWrapPanel = new Panel();
	textWrapPanel->Construct(textWrapLayout, Rectangle(0, 0, baseDim.width, baseDim.height), GROUP_STYLE_NONE);

	int textPadL = BUBBLE_TRIANGLE_SIZE + BUBBLE_PADDING,
			textPadR = BUBBLE_PADDING,
			textPadT = BUBBLE_PADDING,
			textPadB = BUBBLE_PADDING;

	r = layout.Construct(VERTICAL_DIRECTION_UPWARD);
	TryCatch(r == E_SUCCESS, , "Failed Construct layout");

	r = Panel::Construct(layout, Rectangle(0, 0, baseDim.width, baseDim.height), GROUP_STYLE_NONE);
	TryCatch(r == E_SUCCESS, , "Failed Construct MessageBubble parent");

	if (message != null) {
		pRtPanel = new RichTextPanel();

		textDim = Dimension(baseDim.width-2*BUBBLE_PADDING-BUBBLE_TRIANGLE_SIZE, baseDim.height-2*BUBBLE_VERTICAL_PADDING);
		pRtPanel->Construct(textDim, *message);
		textDim = pRtPanel->GetSize();

		textWrapPanel->AddControl(pRtPanel);
		textWrapPanel->SetSize(textDim.width + 2*BUBBLE_PADDING+BUBBLE_TRIANGLE_SIZE+BUBBLE_TRIANGLE_EXTRA, textDim.height + 2*BUBBLE_VERTICAL_PADDING);
		textWrapLayout.SetMargin(*pRtPanel, BUBBLE_PADDING, BUBBLE_PADDING, BUBBLE_VERTICAL_PADDING, BUBBLE_VERTICAL_PADDING);

		textWrapLayout.SetCenterAligned(*pRtPanel, CENTER_ALIGN_HORIZONTAL);
		textWrapLayout.SetCenterAligned(*pRtPanel, CENTER_ALIGN_VERTICAL);

		baseDim = textWrapPanel->GetSize();
		TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed SetBackgroundColor");

		r = AddControl(textWrapPanel);
		TryCatch(r == E_SUCCESS, , "Failed Add message text to MessageBubble");

//		r = layout.SetHorizontalAlignment(*textWrapPanel, LAYOUT_HORIZONTAL_ALIGN_RIGHT);
//		TryCatch(r == E_SUCCESS, , "Failed SetHorizontalAlignment");
//		layout.SetHorizontalMargin(*textWrapPanel, BUBBLE_PADDING, BUBBLE_PADDING);
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
