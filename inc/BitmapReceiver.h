/*
 * BitmapReceiver.h
 *
 *  Created on: Nov 12, 2013
 *      Author: wolong
 */

#ifndef BITMAPRECEIVER_H_
#define BITMAPRECEIVER_H_

#include <FBase.h>

class IBitmapReceiver : public Tizen::Base::Object {
	virtual void OnBitmap(Bitmap *bitmap);
};


#endif /* BITMAPRECEIVER_H_ */
