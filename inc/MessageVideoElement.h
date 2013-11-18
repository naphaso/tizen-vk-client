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

class MessageVideoElement: public MessageElement {
public:
	MessageVideoElement();
	virtual ~MessageVideoElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect) { return E_SUCCESS; }
	result MessageVideoElement::Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Web::Json::JsonObject * pObject);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_VIDEO; }
//	virtual result OnDraw(void);

private:
	Tizen::Base::String thumbUrl;
	Tizen::Web::Json::JsonObject * pVideoObject;

	LocalImageView *pPlayBtn;
	WebImageView *pImageView;
	Tizen::Ui::Controls::Label *pDurationLabel;
};

#endif /* MESSAGEVIDEOELEMENT_H_ */
