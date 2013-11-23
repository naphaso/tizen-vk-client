/*
 * IElementActionListener.h
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#ifndef IELEMENTACTIONLISTENER_H_
#define IELEMENTACTIONLISTENER_H_

#include <FBaseObject.h>

class IElementActionListener;

#include "AttachElement.h"

class IElementActionListener: public Tizen::Base::Object {
public:
	IElementActionListener();
	virtual ~IElementActionListener();

	virtual void OnElementRemoveRequest(AttachElement * source) = 0;
};

#endif /* IELEMENTACTIONLISTENER_H_ */
