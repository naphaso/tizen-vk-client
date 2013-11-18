/*
 * MessageDocElement.h
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGEDOCELEMENT_H_
#define MESSAGEDOCELEMENT_H_

#include "MessageElement.h"
#include <FGraphics.h>

class MessageDocElement: public MessageElement {
public:
	MessageDocElement();
	virtual ~MessageDocElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_DOC; }
	virtual result OnDraw(void);
};

#endif /* MESSAGEDOCELEMENT_H_ */
