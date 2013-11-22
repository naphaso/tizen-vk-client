/*
 * PullToRefreshTrait.h
 *
 *  Created on: Nov 21, 2013
 *      Author: wolong
 */

#ifndef PULLTOREFRESHTRAIT_H_
#define PULLTOREFRESHTRAIT_H_

#include <FBase.h>
#include <FUi.h>

class PullToRefreshTrait;

#include "IRefreshable.h"

#define PULL_TO_REFRESH_OFFSET_LIMIT 400

typedef enum {
	PULL_TO_REFRESH_DIRECTION_TOP,
	PULL_TO_REFRESH_DIRECTION_BOTTOM
} PullToRefreshDirection;

class PullToRefreshTrait : public Tizen::Ui::IPropagatedTouchEventListener {
public:
	PullToRefreshTrait();
	virtual ~PullToRefreshTrait();

	result Construct(Tizen::Ui::Controls::TableView *tableView, Tizen::Ui::Control *progressControl, IRefreshable *refreshable, PullToRefreshDirection direction);

	// IPropagatedTouchEventListener
	virtual bool OnTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; };
	virtual bool OnTouchCanceled(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; };
	virtual bool OnPreviewTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnPreviewTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnPreviewTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);

private:
	PullToRefreshDirection _direction;
	Tizen::Graphics::Point _touchDownPoint;
	bool _captured;

	Tizen::Ui::Controls::TableView *_tableView;
	Tizen::Ui::Control *_progressControl;

	IRefreshable *_refreshable;
};

#endif /* PULLTOREFRESHTRAIT_H_ */
