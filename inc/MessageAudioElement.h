/*
 * MessageAudioElement.h
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGEAUDIOELEMENT_H_
#define MESSAGEAUDIOELEMENT_H_

#include "MessageElement.h"
#include <FGraphics.h>

class MessageAudioElement: public MessageElement {
public:
	MessageAudioElement();
	virtual ~MessageAudioElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_AUDIO; }
	virtual result OnDraw(void);
};

#endif /* MESSAGEAUDIOELEMENT_H_ */
