/*
 * AttachLocationElement.h
 *
 *  Created on: Nov 24, 2013
 *      Author: Igor Glotov
 */

#ifndef ATTACHLOCATIONELEMENT_H_
#define ATTACHLOCATIONELEMENT_H_

#include "AttachElement.h"
#include "LocalImageView.h"

class AttachLocationElement: public AttachElement {
public:
	AttachLocationElement();
	virtual ~AttachLocationElement();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect);
	virtual Tizen::Base::String ToString() {return L"";};

	virtual AttachmentType GetType() { return ATTACHMENT_TYPE_LOCATION; }

	virtual double GetLng();
	virtual double GetLat();

private:
	LocalImageView * _icon;
};

#endif /* ATTACHLOCATIONELEMENT_H_ */
