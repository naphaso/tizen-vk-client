/*
 * VKURequest.h
 *
 *  Created on: Oct 31, 2013
 *      Author: wolong
 */

#ifndef VKUREQUEST_H_
#define VKUREQUEST_H_


#include <FBase.h>
#include <FNet.h>
#include <FApp.h>
#include <FWebJson.h>

class VKURequestBuilder;

#include "VKUApi.h"
#include "IAPIRequestListener.h"
#include "VKURequestData.h"

class VKURequestBuilder {
public:
	VKURequestBuilder(VKUApi *api, Tizen::Base::String method, IAPIRequestListener *listener);
	virtual ~VKURequestBuilder();
	VKURequestBuilder *Put(const Tizen::Base::String &arg, const Tizen::Base::String &value);
	void Submit();
private:
	VKUApi *api;
	VKURequestData *requestData;
	Tizen::Net::Http::HttpTransaction* pTransaction;
    Tizen::Net::Http::HttpRequest* pRequest;
    Tizen::Net::Http::HttpUrlEncodedEntity* pHttpUrlEncodedEntity;
};

#endif /* VKUREQUEST_H_ */
