/*
 * AttachElement.h
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#ifndef ATTACHELEMENT_H_
#define ATTACHELEMENT_H_

#include <FUi.h>

class AttachElement;
#include "IElementActionListener.h"

class AttachElement:
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::IActionEventListener {
public:
	AttachElement();
	virtual ~AttachElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect);
	virtual result OnDraw(void);

	void SetElementActionListener(IElementActionListener * listener) { _listener = listener; }
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

private:
	Tizen::Graphics::Bitmap * _loadedBg;
	Tizen::Graphics::Bitmap *_loadingBg;
	Tizen::Graphics::Bitmap * _closeNormalBmp;
	Tizen::Graphics::Bitmap * _closePressedBmp;
	bool _loading;

	IElementActionListener * _listener;

};

#endif /* ATTACHELEMENT_H_ */
