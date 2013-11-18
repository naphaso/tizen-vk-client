/*
 * WebImageView.h
 *
 *  Created on: Nov 17, 2013
 *      Author: igorglotov
 */

#ifndef WEBIMAGEVIEW_H_
#define WEBIMAGEVIEW_H_

#include <FUi.h>
#include <FBase.h>
#include <FUiCtrlPanel.h>

class WebImageView: public Tizen::Ui::Controls::Panel {
public:
	WebImageView();
	virtual ~WebImageView();

	result Construct(const Tizen::Graphics::Rectangle & rect, const Tizen::Base::String &bitmapPath);

	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);

	// panel
	virtual result OnDraw(void);

private:
	Tizen::Base::String imageUrl;

	Tizen::Graphics::Bitmap* pImageBitmap;

};

#endif /* WEBIMAGEVIEW_H_ */
