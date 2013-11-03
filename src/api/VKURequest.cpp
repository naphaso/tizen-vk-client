/*
 * VKURequest.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: wolong
 */

#include "VKURequest.h"
#include "VKUJson.h"
#include "../VKUAuthConfig.h"
#include "../VKUConfig.h"
#include "VKURequestData.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Net::Http;
using namespace Tizen::Text;
using namespace Tizen::Web::Json;


VKURequest::VKURequest(VKUApi *api, String method, IAPIRequestListener *listener) {
	result r;

	this->api = api;
	this->pTransaction = null;
    this->pRequest = null;


	pTransaction = api->GetHttpSession()->OpenTransactionN();
	r = GetLastResult();
	TryCatch(pTransaction != null, , "Failed to open the HttpTransaction.");

	pTransaction->SetUserObject(new VKURequestData(listener));

	r = pTransaction->AddHttpTransactionListener(*this);
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

VKURequest::~VKURequest() {
	// TODO Auto-generated destructor stub
}


VKURequest *VKURequest::Put(const String &arg, const String &value) {
	pHttpUrlEncodedEntity->AddParameter(arg, value);
	return this;
}


void VKURequest::Submit() {
	result r;

	r = pRequest->SetEntity(*pHttpUrlEncodedEntity);

	r = pTransaction->Submit();
	//TryCatch(r == E_SUCCESS, , "Failed to submit the HttpTransaction.");
}


void VKURequest::OnTransactionReadyToRead(HttpSession& httpSession, HttpTransaction& httpTransaction, int availableBodyLen) {
	result r;
	AppLog("OnTransactionReadyToRead");


	HttpResponse* pHttpResponse = httpTransaction.GetResponse();
	//IAPIRequestListener *listener = static_cast<IAPIRequestListener *>(httpTransaction.GetUserObject());
	VKURequestData *requestData = static_cast<VKURequestData *>(httpTransaction.GetUserObject());


	if (pHttpResponse->GetHttpStatusCode() == HTTP_STATUS_OK)
	{
		HttpHeader* pHttpHeader = pHttpResponse->GetHeader();
		if (pHttpHeader != null)
		{
			String* tempHeaderString = pHttpHeader->GetRawHeaderN();
			ByteBuffer* pBuffer = pHttpResponse->ReadBodyN();

			String text(L"Read Body Length: ");
			text.Append(availableBodyLen);

			AppLog("len: %ls", text.GetPointer());

			requestData->data.CopyFrom(*pBuffer);

			/*
			AppLog("response: %s", pBuffer->GetPointer());

			if(listener != null) {
				IJsonValue *pJson = JsonParser::ParseN(*pBuffer);
				TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed ParseN");
				if(pJson->GetType() == JSON_TYPE_OBJECT) {
					JsonObject* pObject = static_cast< JsonObject* >(pJson);
					listener->OnResponseN(pObject);
				} else {
					delete pJson;
				}
			}
			*/


			/*
			AppLog("1");

			IJsonValue *pJson = JsonParser::ParseN(*pBuffer);
			JsonObject* pObject = static_cast< JsonObject* >(pJson);
			IJsonValue *pValue;
			String mapKey(L"response");
			String itemsKey(L"items");
			String titleKey(L"title");
			pObject->GetValue(&mapKey, pValue);
			AppLog("2");
			JsonObject* pVal = static_cast< JsonObject* >(pValue);
			IJsonValue *arrayValue;
			JsonArray *array;
			AppLog("3");
			pVal->GetValue(&itemsKey, arrayValue);
			AppLog("3.1");
			array = static_cast<JsonArray *>(arrayValue);
			AppLog("3.2");
			JsonObject *countryObj;
			IJsonValue *countryValue;
			AppLog("3.3");
			array->GetAt(0, countryValue);
			AppLog("4");
			countryObj = static_cast<JsonObject*>(countryValue);
			JsonString *titleString;
			IJsonValue *titleValue;
			countryObj->GetValue(&titleKey, titleValue);
			AppLog("5");
			titleString = static_cast<JsonString *>(titleValue);


			String valueString(L"first country = ");
			valueString.Append(*titleString);
			AppLog("output: %ls", valueString.GetPointer());


			// TODO: returning
			delete pJson;

			*/

			/*
			JSONObject jsonObject(VKUJsonObject::parseN(pBuffer));
			JSONObject response(jsonObject->getObject(L"response"));
			JSONArray items(response->getArray(L"items"));

			for(int i = 0; i < items->length(); i++) {
				JSONObject item(items->getObject(i));
				AppLog("title: %ls", item->getString(L"title")->GetPointer());
			}*/

			delete tempHeaderString;
			delete pBuffer;
		}
	}
	return;
	CATCH:
	AppLogException("OnTransactionReadyToRead constructor is failed.", GetErrorMessage(r));
	return;

}

void VKURequest::OnTransactionAborted(HttpSession& httpSession, HttpTransaction& httpTransaction, result r) {
	AppLog("OnTransactionAborted(%s)", GetErrorMessage(r));

	delete &httpTransaction;
}

void VKURequest::OnTransactionReadyToWrite(HttpSession& httpSession, HttpTransaction& httpTransaction, int recommendedChunkSize) {
	AppLog("OnTransactionReadyToWrite");
}

void VKURequest::OnTransactionHeaderCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction, int headerLen, bool authRequired) {
	AppLog("OnTransactionHeaderCompleted");
}

void VKURequest::OnTransactionCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction) {
	result r;
	AppLog("OnTransactionCompleted");

	VKURequestData *requestData = static_cast<VKURequestData *>(httpTransaction.GetUserObject());

	if(requestData != null) {
		requestData->data.Flip();
		IJsonValue *pJson = JsonParser::ParseN(requestData->data);
		TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed ParseN");
		if(pJson->GetType() == JSON_TYPE_OBJECT) {
			JsonObject* pObject = static_cast< JsonObject* >(pJson);
			requestData->listener->OnResponseN(pObject);
		} else {
			delete pJson;
		}
	}

	delete requestData;
	delete &httpTransaction;

	return;

	CATCH:
	AppLogException("OnTransactionCompleted constructor is failed.", GetErrorMessage(r));
	return;
}

void VKURequest::OnTransactionCertVerificationRequiredN(HttpSession& httpSession, HttpTransaction& httpTransaction, Tizen::Base::String* pCert) {
	AppLog("OnTransactionCertVerificationRequiredN");

	httpTransaction.Resume();

	delete pCert;
}

