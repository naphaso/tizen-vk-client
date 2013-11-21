/*
 * PullToRefreshTrait.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: wolong
 */

#include "PullToRefreshTrait.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

PullToRefreshTrait::PullToRefreshTrait() {
	// TODO Auto-generated constructor stub

}

PullToRefreshTrait::~PullToRefreshTrait() {
	// TODO Auto-generated destructor stub
}

result PullToRefreshTrait::Construct(TableView *tableView, Control *progressControl, IRefreshable *refreshable) {
	result r = E_SUCCESS;

	_tableView = tableView;
	_progressControl = progressControl;
	_refreshable = refreshable;

	return r;
}

// IPropagatedTouchEventListener
bool PullToRefreshTrait::OnPreviewTouchPressed(Control& source, const TouchEventInfo& touchEventInfo) {
	_touchDownPoint = touchEventInfo.GetCurrentPosition();
	_captured = _tableView->GetCurrentScrollPosition() == 0;
	return false;
}

bool PullToRefreshTrait::OnPreviewTouchReleased(Control& source, const TouchEventInfo& touchEventInfo) {
	if(_captured) {
		if((touchEventInfo.GetCurrentPosition() - _touchDownPoint).y > PULL_TO_REFRESH_OFFSET_LIMIT) {
			_refreshable->OnRefresh();
		}

		_progressControl->RequestRedraw(true);
	}

	return false;
}

bool PullToRefreshTrait::OnPreviewTouchMoved(Control& source, const TouchEventInfo& touchEventInfo) {
	if(_captured) {
		int offset = (touchEventInfo.GetCurrentPosition() - _touchDownPoint).y; // > PULL_TO_REFRESH_OFFSET_LIMIT) {
		float progress = (float)offset / (float)PULL_TO_REFRESH_OFFSET_LIMIT;
		if(progress > 1.0f) {
			progress = 1.0f;
		}
		Canvas *canvas = _progressControl->GetCanvasN();
		int doneSize = (int)(canvas->GetBoundsF().width * progress);
		int undoneSize = canvas->GetBounds().width - doneSize;

		if(undoneSize < 0) {
			undoneSize = 0;
		}

		Rectangle progressRectangle = canvas->GetBounds();
		progressRectangle.width -= undoneSize;
		progressRectangle.x += undoneSize / 2;

		canvas->SetCompositeMode(COMPOSITE_MODE_OVERLAY);
		canvas->FillRectangle(Color(0, 0, 255), progressRectangle);
		delete canvas;

	}
	return false;
}
