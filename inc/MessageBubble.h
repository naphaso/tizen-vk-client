/*
 * MessageBubble.h
 *
 *  Created on: Nov 7, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGEBUBBLE_H_
#define MESSAGEBUBBLE_H_

#include <FUi.h>
#include <FUiCtrlPanel.h>
#include <FBase.h>
#include "RichTextPanel.h"
#include "VKU.h"
#include "BubbleConstants.h"

class MessageBubble: public Tizen::Ui::Controls::Panel {
public:
	MessageBubble();
	virtual ~MessageBubble();

	// Panel
	result Construct(const Tizen::Graphics::Dimension& dim);
	result OnDraw(void);

	void SetMessage(const Tizen::Base::String & msg, const int aOut);
private:
	// possible bubble content
	Tizen::Base::String* message;
	int out; // message in=0 or out=1

	// bubbles
	Tizen::Graphics::Bitmap* pBubbleIn;
	Tizen::Graphics::Bitmap* pBubbleOut;

	Tizen::Graphics::Rectangle bubbleBgBounds;
};

#endif /* MESSAGEBUBBLE_H_ */
