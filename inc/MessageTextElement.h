/*
 * MessageTextElement.h
 *
 *  Created on: Nov 14, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGETEXTELEMENT_H_
#define MESSAGETEXTELEMENT_H_

#include <FBase.h>
#include <FGraphics.h>

class MessageTextElement;

#include "MessageElement.h"

class MessageTextElement: public MessageElement {
public:
	MessageTextElement();
	virtual ~MessageTextElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect);

	result SetText(const Tizen::Base::String & text, bool emoji = true);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_TEXT; }
	virtual result OnDraw(void);

private:
	Tizen::Graphics::Font *pFont;

	Tizen::Base::String messageText;
	Tizen::Graphics::EnrichedText *pEnrichedText;

};

#endif /* MESSAGETEXTELEMENT_H_ */
