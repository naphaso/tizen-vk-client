/*
 * VKUApi.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: wolong
 */

#include "VKUApi.h"

#include <FText.h>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Net::Http;
using namespace Tizen::Text;
using namespace Tizen::Web::Json;

VKUApi::VKUApi() {
	httpSession = null;
	// TODO Auto-generated constructor stub

}

VKUApi::~VKUApi() {
	// TODO Auto-generated destructor stub
}

result VKUApi::request() {
	result r = E_SUCCESS;
	HttpTransaction* pHttpTransaction = null;
	HttpRequest* pHttpRequest = null;

	AppLog("start request");

	if(httpSession == null) {
		AppLog("creating httpsession...");
		httpSession = new (std::nothrow) HttpSession();
		r = httpSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, null, L"https://api.vk.com", null); // NET_HTTP_COOKIE_FLAG_ALWAYS_AUTOMATIC
		if (IsFailed(r)) {
			delete httpSession;
			httpSession = null;
			AppLogException("Failed to create the HttpSession.");
			goto CATCH;
		}

		r = httpSession->SetAutoRedirectionEnabled(true);
		TryCatch(r == E_SUCCESS, , "Failed to set the redirection automatically.");
	}

	pHttpTransaction = httpSession->OpenTransactionN();
	r = GetLastResult();
	TryCatch(pHttpTransaction != null, , "Failed to open the HttpTransaction.");

	r = pHttpTransaction->AddHttpTransactionListener(*this);
	TryCatch(r == E_SUCCESS, , "Failed to add the HttpTransactionListener.");

	pHttpRequest = const_cast< HttpRequest* >(pHttpTransaction->GetRequest());

	r = pHttpRequest->SetUri(L"https://api.vk.com/method/database.getCountries?need_all=1&count=5&v=5.2");
	TryCatch(r == E_SUCCESS, , "Failed to set the uri.");

	r = pHttpRequest->SetMethod(NET_HTTP_METHOD_GET);
	TryCatch(r == E_SUCCESS, , "Failed to set the method.");

	r = pHttpTransaction->Submit();
	TryCatch(r == E_SUCCESS, , "Failed to submit the HttpTransaction.");

	return r;

	CATCH:

	if(pHttpTransaction != null) {
		delete pHttpTransaction;
		pHttpTransaction = null;
	}

	AppLog("RequestHttpGet() failed. (%s)", GetErrorMessage(r));
	return r;
}


void VKUApi::OnTransactionReadyToRead(HttpSession& httpSession, HttpTransaction& httpTransaction, int availableBodyLen) {
	AppLog("OnTransactionReadyToRead");

	HttpResponse* pHttpResponse = httpTransaction.GetResponse();
	if (pHttpResponse->GetHttpStatusCode() == HTTP_STATUS_OK)
	{
		HttpHeader* pHttpHeader = pHttpResponse->GetHeader();
		if (pHttpHeader != null)
		{
			String* tempHeaderString = pHttpHeader->GetRawHeaderN();
			ByteBuffer* pBuffer = pHttpResponse->ReadBodyN();

			String text(L"Read Body Length: ");
			text.Append(availableBodyLen);


			IJsonValue *pJson = JsonParser::ParseN(*pBuffer);
			JsonObject* pObject = static_cast< JsonObject* >(pJson);
			IJsonValue *pValue;
			String mapKey(L"response");
			String itemsKey(L"items");
			String titleKey(L"title");
			pObject->GetValue(&mapKey, pValue);
			JsonObject* pVal = static_cast< JsonObject* >(pValue);
			IJsonValue *arrayValue;
			JsonArray *array;
			pVal->GetValue(&itemsKey, arrayValue);
			array = static_cast<JsonArray *>(arrayValue);
			JsonObject *countryObj;
			IJsonValue *countryValue;
			array->GetAt(0, countryValue);
			countryObj = static_cast<JsonObject*>(countryValue);
			JsonString *titleString;
			IJsonValue *titleValue;
			countryObj->GetValue(&titleKey, titleValue);
			titleString = static_cast<JsonString *>(titleValue);


			String valueString(L"first country = ");
			valueString.Append(*titleString);
			AppLog("output: %ls", valueString.GetPointer());


			// TODO: returning
			delete pJson;

			delete tempHeaderString;
			delete pBuffer;
		}
	}
}

void VKUApi::OnTransactionAborted(HttpSession& httpSession, HttpTransaction& httpTransaction, result r) {
	AppLog("OnTransactionAborted(%s)", GetErrorMessage(r));

	delete &httpTransaction;
}

void VKUApi::OnTransactionReadyToWrite(HttpSession& httpSession, HttpTransaction& httpTransaction, int recommendedChunkSize) {
	AppLog("OnTransactionReadyToWrite");
}

void VKUApi::OnTransactionHeaderCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction, int headerLen, bool authRequired) {
	AppLog("OnTransactionHeaderCompleted");
}

void VKUApi::OnTransactionCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction) {
	AppLog("OnTransactionCompleted");

	delete &httpTransaction;
}

void VKUApi::OnTransactionCertVerificationRequiredN(HttpSession& httpSession, HttpTransaction& httpTransaction, Tizen::Base::String* pCert) {
	AppLog("OnTransactionCertVerificationRequiredN");

	httpTransaction.Resume();

	delete pCert;
}

HttpSession* VKUApi::GetHttpSession() {
	result r;
	if(httpSession == null) {
		AppLog("creating httpsession...");
		httpSession = new (std::nothrow) HttpSession();
		r = httpSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, null, L"https://api.vk.com", null); // NET_HTTP_COOKIE_FLAG_ALWAYS_AUTOMATIC
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

VKURequest *VKUApi::CreateRequest(String method, IAPIRequestListener *listener) {
	return new VKURequest(this, method, listener);
}
