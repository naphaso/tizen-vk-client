/*
 * AttachElement.h
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#ifndef ATTACHELEMENT_H_
#define ATTACHELEMENT_H_

#include <FUi.h>
#include <FWebJson.h>

class AttachElement;
#include "IElementActionListener.h"

typedef enum {
	ATTACHMENT_TYPE_LOCATION,
	ATTACHMENT_TYPE_WALL,
	ATTACHMENT_TYPE_PHOTO,
	ATTACHMENT_TYPE_AUDIO,
	ATTACHMENT_TYPE_VIDEO,
	ATTACHMENT_TYPE_DOC
} AttachmentType;

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

	virtual Tizen::Base::String ToString();
	bool IsUploaded() { return _isUploaded; }

	virtual AttachmentType GetType() { return ATTACHMENT_TYPE_DOC; }

protected:
	void SetUploaded(bool uploaded) { _isUploaded = uploaded; }
	IElementActionListener * _listener;

	bool _isUploaded;

	Tizen::Graphics::Bitmap * _loadedBg;
	Tizen::Graphics::Bitmap *_loadingBg;
	Tizen::Graphics::Bitmap * _closeNormalBmp;
	Tizen::Graphics::Bitmap * _closePressedBmp;
	bool _loading;
};

#endif /* ATTACHELEMENT_H_ */
