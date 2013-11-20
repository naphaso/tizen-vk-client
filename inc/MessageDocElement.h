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

class MessageDocElement: public MessageElement {
public:
	MessageDocElement();
	virtual ~MessageDocElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Web::Json::JsonObject * docObject, int out);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_DOC; }
	virtual result OnDraw(void);

private:
	Tizen::Graphics::Bitmap * _pBitmap;
	LocalImageView * _pIcon;
};

#endif /* MESSAGEDOCELEMENT_H_ */
