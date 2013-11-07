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

class MessageBubble: public Tizen::Ui::Controls::Panel {
public:
	MessageBubble();
	virtual ~MessageBubble();

	// Panel
	result Construct(const Tizen::Graphics::Dimension& dim, const Tizen::Base::String & text);
	result RichTextPanel::OnDraw(void);

	void setMessage(const Tizen::Base::String & msg, const int aOut);
private:
	// possible bubble content
	Tizen::Base::String* message;
	int out; // message in=0 or out=1
};

#endif /* MESSAGEBUBBLE_H_ */
