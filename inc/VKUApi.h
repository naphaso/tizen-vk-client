/*
 * VKUApi.h
 *
 *  Created on: Oct 30, 2013
 *      Author: wolong
 */

#ifndef VKUAPI_H_
#define VKUAPI_H_

#include <FApp.h>
#include <FBase.h>
#include <FNet.h>
#include <FUi.h>
#include <FWebJson.h>

class VKUApi;

#include "VKURequestBuilder.h"
#include "IAPIRequestListener.h"
#include "VKURequestData.h"

class VKUApi {
private:
	VKUApi();
public:
	virtual ~VKUApi();
	static VKUApi &GetInstance();

	VKURequestBuilder *CreateRequest(Tizen::Base::String method, IAPIRequestListener *listener);
	void DropRequest(const Tizen::Base::UuId &requestId);
	void SaveRequest(const Tizen::Base::UuId &requestId, VKURequestData *requestData);
	void EndRequest(const Tizen::Base::UuId &requestId);
	Tizen::Net::Http::HttpSession* GetHttpSession();
private:
	Tizen::Net::Http::HttpSession* httpSession;
	Tizen::Base::Collection::HashMap requestsMap;
};

#endif /* VKUAPI_H_ */
