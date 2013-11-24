/*
 * MessageWallElement.h
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGEWALLELEMENT_H_
#define MESSAGEWALLELEMENT_H_

#include "MessageElement.h"
#include <FGraphics.h>
#include <FWeb.h>
#include <FUi.h>

class MessageWallElement:
	public MessageElement,
	public Tizen::Ui::IPropagatedTouchEventListener {
public:
	MessageWallElement();
	virtual ~MessageWallElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Web::Json::JsonObject * wallObject, int out);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_WALL; }
	virtual result OnDraw(void);

	// ITouchEventListener
	virtual bool OnTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchCanceled(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }

private:
	Tizen::Graphics::Bitmap * _pBitmap;
	Tizen::Base::String baseUrl;

	bool touchAllowed;
};

#endif /* MESSAGEWALLELEMENT_H_ */
