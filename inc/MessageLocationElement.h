/*
 * MessageLocationElement.h
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#ifndef MESSAGELOCATIONELEMENT_H_
#define MESSAGELOCATIONELEMENT_H_

#include "MessageElement.h"

#include <FWebJson.h>
#include <FUi.h>
#include <FBase.h>
#include <FGraphics.h>
#include "BrowserPopup.h"

class MessageLocationElement:
	public MessageElement,
	public Tizen::Ui::IPropagatedTouchEventListener {
public:
	MessageLocationElement();
	virtual ~MessageLocationElement();

	result Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Web::Json::JsonObject * location);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_LOCATION; }

	// IPropagatedTouchEventListener
	virtual bool OnTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchCanceled(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
private:
	bool touchAllowed;
	Tizen::Base::String baseUrl;
	Tizen::Base::String browserUrl;
	BrowserPopup * popup;

};

#endif /* MESSAGELOCATIONELEMENT_H_ */
