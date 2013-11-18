/*
 * MessageVideoElement.h
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGEVIDEOELEMENT_H_
#define MESSAGEVIDEOELEMENT_H_

#include "MessageElement.h"
#include "WebImageView.h"
#include "LocalImageView.h"
#include <FGraphics.h>
#include <FBase.h>
#include <FWeb.h>
#include <FUi.h>

class MessageVideoElement:
	public MessageElement,
	public Tizen::Ui::IPropagatedTouchEventListener {
public:
	MessageVideoElement();
	virtual ~MessageVideoElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect) { return E_SUCCESS; }
	result MessageVideoElement::Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Web::Json::JsonObject * pObject);

	// ITouchEventListener
	virtual bool OnTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo);
	virtual bool OnTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnTouchCanceled(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchPressed(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchReleased(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { return false; }
	virtual bool OnPreviewTouchMoved(Tizen::Ui::Control& source, const Tizen::Ui::TouchEventInfo& touchEventInfo) { AppLog("MOVE"); return false; }

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_VIDEO; }
//	virtual result OnDraw(void);

private:
	Tizen::Base::String thumbUrl;
	Tizen::Web::Json::JsonObject * pVideoObject;

	LocalImageView *pPlayBtn;
	WebImageView *pImageView;
	Tizen::Ui::Controls::Label *pDurationLabel;

	int videoId;
};

#endif /* MESSAGEVIDEOELEMENT_H_ */
