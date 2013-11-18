/*
 * LocalImageView.h
 *
 *  Created on: Nov 18, 2013
 *      Author: igorglotov
 */

#ifndef LOCALIMAGEVIEW_H_
#define LOCALIMAGEVIEW_H_

#include <FUiCtrlPanel.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FBase.h>

class LocalImageView: public Tizen::Ui::Controls::Panel {
public:
	LocalImageView();
	virtual ~LocalImageView();

	result Construct(const Tizen::Graphics::Rectangle & rect, const Tizen::Base::String & resImageName);

	virtual result OnDraw(void);

private:
	Tizen::Graphics::Bitmap *pNormalBitmap;
};

#endif /* LOCALIMAGEVIEW_H_ */
