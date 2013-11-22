/*
 * MessageDocElement.h
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGEDOCELEMENT_H_
#define MESSAGEDOCELEMENT_H_

#include <FGraphics.h>
#include <FWebJson.h>

#include "MessageElement.h"
#include "LocalImageView.h"

class MessageDocElement:
	public MessageElement,
	public Tizen::Ui::IPropagatedTouchEventListener {
public:
	MessageDocElement();
	virtual ~MessageDocElement();

	result Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Web::Json::JsonObject * docObject, int out);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_DOC; }
	virtual result OnDraw(void);

	Tizen::Base::String GetSizeString(int size);

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
	LocalImageView * _pIcon;

	Tizen::Web::Json::JsonObject * _pDocObject;

	bool touchAllowed;
};

#endif /* MESSAGEDOCELEMENT_H_ */
