/*
 * MessageVideoElement.h
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGEVIDEOELEMENT_H_
#define MESSAGEVIDEOELEMENT_H_

#include "MessageElement.h"
#include <FGraphics.h>

class MessageVideoElement: public MessageElement {
public:
	MessageVideoElement();
	virtual ~MessageVideoElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_VIDEO; }
	virtual result OnDraw(void);
};

#endif /* MESSAGEVIDEOELEMENT_H_ */
