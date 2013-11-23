/*
 * IItemsRemovedListener.h
 *
 *  Created on: Nov 23, 2013
 *      Author: Igor Glotov
 */

#ifndef IITEMSREMOVEDLISTENER_H_
#define IITEMSREMOVEDLISTENER_H_

#include <FBaseObject.h>

class IItemsRemovedListener: public Tizen::Base::Object {
public:
	IItemsRemovedListener();
	virtual ~IItemsRemovedListener();

	virtual void OnAllItemsRemoved() = 0;
};

#endif /* IITEMSREMOVEDLISTENER_H_ */
