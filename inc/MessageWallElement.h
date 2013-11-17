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

class MessageWallElement: public MessageElement {
public:
	MessageWallElement();
	virtual ~MessageWallElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_WALL; }
	virtual result OnDraw(void);
};

#endif /* MESSAGEWALLELEMENT_H_ */
