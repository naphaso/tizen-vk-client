/*
 * AttachControl.cpp
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#include "AttachControl.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base::Collection;

AttachControl::AttachControl() {
	_listener = null;

}

AttachControl::~AttachControl() {
	_listener = null;
}

result AttachControl::Construct(const Tizen::Graphics::Rectangle & rect) {
	result r = E_SUCCESS;

	RelativeLayout layout;
	Panel *pixelPanel;

	_itemLayout = new HorizontalBoxLayout();
	_scrollPanel = new ScrollPanel();

	layout.Construct();
	r = Panel::Construct(layout, rect);
	SetBackgroundColor(Color(0x171e26, false));

	r = _itemLayout->Construct(HORIZONTAL_DIRECTION_RIGHTWARD);
	TryCatch(r == E_SUCCESS, , "Failed DrawNinePatchedBitmap");

	r = _scrollPanel->Construct(*_itemLayout, Rectangle(10, 0, rect.width-10, rect.height-20), SCROLL_PANEL_SCROLL_DIRECTION_HORIZONTAL, true);
	TryCatch(r == E_SUCCESS, , "Failed DrawNinePatchedBitmap");
	_scrollPanel->SetScrollBarVisible(false);

	r = AddControl(_scrollPanel);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	pixelPanel = new Panel();
	pixelPanel->Construct(Rectangle(0, 0, rect.width, 1));
	pixelPanel->SetBackgroundColor(Color(0x383e45, false));

	r = AddControl(pixelPanel);
	TryCatch(r == E_SUCCESS, , "Failed AddControl");

	r = layout.SetCenterAligned(*_scrollPanel, CENTER_ALIGN_VERTICAL);
//	r = layout.SetMargin(*_scrollPanel, 10, 0, 0, 0);
	r = layout.SetRelation(*pixelPanel, this, RECT_EDGE_RELATION_TOP_TO_TOP);
	return r;
CATCH:
	AppLogException("AttachElement::Construct is failed. %s", GetErrorMessage(r));
	return r;
}

result AttachControl::AddElement(AttachElement * element) {
	result r = E_SUCCESS;

	if (element == null)
		return E_INVALID_ARG;

	r = _scrollPanel->AddControl(element);
	TryCatch(r == E_SUCCESS, , "Failed DrawNinePatchedBitmap");

	r = _itemLayout->SetSpacing(*element, 10);
	TryCatch(r == E_SUCCESS, , "Failed DrawNinePatchedBitmap");

	element->SetElementActionListener(this);
//	_scrollPanel->GetCo
	Invalidate(true);

	return r;

CATCH:
	AppLogException("AttachElement::Construct is failed. %s", GetErrorMessage(r));
	return r;
}

void AttachControl::OnElementRemoveRequest(AttachElement * source) {
	_scrollPanel->RemoveControl(*source);
	Invalidate(true);

	AppLog("Control count %d", _scrollPanel->GetControlCount());
	if (_scrollPanel->GetControlCount() != 0)
		return;

	AppLog("Preparing to remove...");

	// Notify that all items have been removed
	if (_listener == null)
		return;

	_listener->OnAllItemsRemoved();
}

void AttachControl::SetItemsRemovedListener(IItemsRemovedListener * listener) {
	AppLog("AttachControl::AddItemsRemovedListener");

	_listener = listener;
}
