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
#include "MessageElement.h"

class MessageBubble: public Tizen::Ui::Controls::Panel {
public:
	MessageBubble();
	virtual ~MessageBubble();

	result AddElement(MessageElement * pElement);
	void SetOut(int out);

	// Panel
	result Construct(const Tizen::Graphics::Dimension& dim);
	virtual result OnDraw(void);

	void SetMessage(const Tizen::Base::String & msg, const int aOut);
	Tizen::Graphics::Dimension GetPlaceholderSize();
private:
	// possible bubble content
	Tizen::Base::String* message;
	int out; // message in=0 or out=1

	Tizen::Base::Collection::ArrayList * pElements;

	// bubbles
	Tizen::Graphics::Bitmap* pBubbleIn;
	Tizen::Graphics::Bitmap* pBubbleOut;
	Tizen::Graphics::Rectangle bubbleBgBounds;

	Tizen::Ui::VerticalBoxLayout itemLayout;

	Tizen::Ui::RelativeLayout placeholderLayout;
	Tizen::Ui::Controls::Panel * pPlaceholderPanel;
};

#endif /* MESSAGEBUBBLE_H_ */
