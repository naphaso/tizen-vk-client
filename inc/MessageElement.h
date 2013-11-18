/*
 * MessageElement.h
 *
 *  Created on: Nov 14, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGEELEMENT_H_
#define MESSAGEELEMENT_H_

#include <FUi.h>

typedef enum {
	MESSAGE_TYPE_TEXT,
	MESSAGE_TYPE_DOC,
	MESSAGE_TYPE_WALL,
	MESSAGE_TYPE_PHOTO,
	MESSAGE_TYPE_VIDEO,
	MESSAGE_TYPE_LOCATION,
	MESSAGE_TYPE_AUDIO,
	MESSAGE_TYPE_FORWARD
} MessageElementType;

class MessageElement: public Tizen::Ui::Controls::Panel {
public:
	MessageElement() {};
	virtual ~MessageElement() {};

	virtual result Construct(const Tizen::Graphics::Rectangle & rect) { return E_SUCCESS; };

	virtual MessageElementType GetElementType() = 0;
};

#endif /* MESSAGEELEMENT_H_ */
