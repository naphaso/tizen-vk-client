/*
 * VKURequest.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: wolong
 */

#include "VKURequestBuilder.h"
#include "VKUJson.h"
#include "VKUAuthConfig.h"
#include "VKUConfig.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Net::Http;
using namespace Tizen::Text;
using namespace Tizen::Web::Json;


VKURequestBuilder::VKURequestBuilder(VKUApi *api, String method, IAPIRequestListener *listener) {
	result r;

	this->api = api;
	this->pTransaction = null;
    this->pRequest = null;


	pTransaction = api->GetHttpSession()->OpenTransactionN();
	r = GetLastResult();
	TryCatch(pTransaction != null, , "Failed to open the HttpTransaction.");

	requestData = new VKURequestData(pTransaction, listener);

	r = pTransaction->AddHttpTransactionListener(*requestData);
	TryCatch(r == E_SUCCESS, , "Failed to add the HttpTransactionListener.");

	pRequest = const_cast< HttpRequest* >(pTransaction->GetRequest());

	r = pRequest->SetUri(L"https://api.vk.com/method/" + method);
	TryCatch(r == E_SUCCESS, , "Failed to set the uri.");

	r = pRequest->SetMethod(NET_HTTP_METHOD_POST);
	TryCatch(r == E_SUCCESS, , "Failed to set the method.");

    pHttpUrlEncodedEntity = new HttpUrlEncodedEntity();
    r = pHttpUrlEncodedEntity->Construct();

    AppLog("set api version: %ls", VKU_API_VERSION);
    pHttpUrlEncodedEntity->AddParameter(L"v", VKU_API_VERSION);
    AppLog("set access_token: %ls", VKUAuthConfig::GetAccessToken()->GetPointer());
    pHttpUrlEncodedEntity->AddParameter(L"access_token", *VKUAuthConfig::GetAccessToken());

	return;
	CATCH:
	AppLogException("VKUReqquest constructor is failed.", GetErrorMessage(r));
	return;
}

VKURequestBuilder::~VKURequestBuilder() {
	AppLog("destruct VKURequestBuilder and entity");
	delete pHttpUrlEncodedEntity;
}


VKURequestBuilder *VKURequestBuilder::Put(const String &arg, const String &value) {
	pHttpUrlEncodedEntity->AddParameter(arg, value);
	AppLog("key: %ls, val: %ls", arg.GetPointer(), value.GetPointer());
	return this;
}


void VKURequestBuilder::Submit(RequestId requestId) {
	result r;

	r = pRequest->SetEntity(*pHttpUrlEncodedEntity);
	//TryCatch(r == E_SUCCESS, , "Failed to set request entity");
	r = pTransaction->Submit();

	if(r == E_SUCCESS) {
		requestData->OnSend(requestId);
	}

	delete this;
}

