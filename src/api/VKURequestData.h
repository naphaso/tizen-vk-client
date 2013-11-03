/*
 * VKURequestData.h
 *
 *  Created on: Nov 3, 2013
 *      Author: wolong
 */

#ifndef VKUREQUESTDATA_H_
#define VKUREQUESTDATA_H_

#include "FBase.h"
#include "IAPIRequestListener.h"

class VKURequestData : public Tizen::Base::Object {
public:
	VKURequestData(IAPIRequestListener *requestListener) {
		data.Construct(131072);
		listener = requestListener;
	};
	Tizen::Base::ByteBuffer data;
	IAPIRequestListener *listener;
};


#endif /* VKUREQUESTDATA_H_ */
