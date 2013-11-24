/*
 * VKUApi.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: wolong
 */

#include "VKUApi.h"

#include <FText.h>
#include "ObjectCounter.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Net::Http;
using namespace Tizen::Text;
using namespace Tizen::Web::Json;


VKUApi::VKUApi() : requestsMap(SingleObjectDeleter) {
	CONSTRUCT(L"VKUApi");
	httpSession = null;
	requestsMap.Construct();
}

VKUApi::~VKUApi() {
	DESTRUCT(L"VKUApi");
}


VKUApi &VKUApi::GetInstance() {
	static VKUApi api;
	return api;
}

HttpSession* VKUApi::GetHttpSession() {
	result r;
	if(httpSession == null) {
		AppLog("creating httpsession...");
		httpSession = new (std::nothrow) HttpSession();
		r = httpSession->Construct(NET_HTTP_SESSION_MODE_MULTIPLE_HOST, null, L"https://api.vk.com", null); // NET_HTTP_COOKIE_FLAG_ALWAYS_AUTOMATIC
		if (IsFailed(r)) {
			delete httpSession;
			httpSession = null;
			AppLogException("Failed to create the HttpSession.");
			goto CATCH;
		}


		r = httpSession->SetAutoRedirectionEnabled(true);
		TryCatch(r == E_SUCCESS, , "Failed to set the redirection automatically.");
	}
	return httpSession;

	CATCH:
	return null; // TODO: error handling
}

VKURequestBuilder *VKUApi::CreateRequest(String method, IAPIRequestListener *listener) {
	return new VKURequestBuilder(this, method, listener);
}

void VKUApi::DropRequest(const UuId &requestId) {
	Object *value = requestsMap.GetValue(requestId);
	if(value != null) {
		VKURequestData *requestData = static_cast<VKURequestData*>(value);
		if(requestData->httpTransaction != null) {
			GetHttpSession()->CancelTransaction(*requestData->httpTransaction);
		}
		requestsMap.Remove(requestId);
	} else {
		AppLog("drop unknown request with id %ls", requestId.ToString().GetPointer());
	}
}

void VKUApi::SaveRequest(const UuId &requestId, VKURequestData *requestData) {
	requestsMap.Add(new UuId(requestId), requestData);
}

void VKUApi::EndRequest(const UuId &requestId) {
	requestsMap.Remove(requestId, true);
}
