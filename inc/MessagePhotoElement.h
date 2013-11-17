/*
 * MessagePhotoElement.h
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGEPHOTOELEMENT_H_
#define MESSAGEPHOTOELEMENT_H_

#include "MessageElement.h"
#include "WebImageView.h"
#include <FGraphics.h>
#include <FBase.h>

class MessagePhotoElement: public MessageElement {
public:
	MessagePhotoElement();
	virtual ~MessagePhotoElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect) { return E_SUCCESS; }
	result Construct(const Tizen::Graphics::Rectangle & rect, Tizen::Base::String & url);

	virtual MessageElementType GetElementType() { return MESSAGE_TYPE_PHOTO; }
	virtual result OnDraw(void);

	void SetUrl(Tizen::Base::String & url);

private:
	Tizen::Base::String url;
	WebImageView *pImageView;
};

#endif /* MESSAGEPHOTOELEMENT_H_ */
