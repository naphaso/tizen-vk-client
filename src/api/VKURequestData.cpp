/*
 * VKURequestData.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: wolong
 */

#include "VKURequestData.h"

#define MAX_RESPONSE_SIZE 131072

using namespace Tizen::Net::Http;
using namespace Tizen::Web::Json;
using namespace Tizen::Base;


VKURequestData::VKURequestData(HttpTransaction *httpTransaction, IAPIRequestListener *requestListener) {
	this->listener = requestListener;
	this->data.Construct(MAX_RESPONSE_SIZE);
	this->httpTransaction = httpTransaction;

	UuId *newId = UuId::GenerateN();
	this->requestId = *newId;
	delete newId;
}

VKURequestData::~VKURequestData() {
	AppLog("destruct VKURequestData");
	if(httpTransaction != null) {
		AppLog("delete transaction");
		delete httpTransaction;
	}
}

// interface implementation

void VKURequestData::OnTransactionReadyToRead(HttpSession& httpSession, HttpTransaction& httpTransaction, int availableBodyLen) {
	AppLog("OnTransactionReadyToRead");

	HttpResponse* pHttpResponse = httpTransaction.GetResponse();

	if (pHttpResponse->GetHttpStatusCode() == HTTP_STATUS_OK) {
		HttpHeader* pHttpHeader = pHttpResponse->GetHeader();
		if (pHttpHeader != null) {
			//String* tempHeaderString = pHttpHeader->GetRawHeaderN();
			ByteBuffer* pBuffer = pHttpResponse->ReadBodyN();

			String text(L"Read Body Length: ");
			text.Append(availableBodyLen);

			AppLog("len: %ls", text.GetPointer());

			data.CopyFrom(*pBuffer);

			//delete tempHeaderString;
			delete pBuffer;
		}
	}

	return;

}

void VKURequestData::OnTransactionAborted(HttpSession& httpSession, HttpTransaction& httpTransaction, result r) {
	AppLog("OnTransactionAborted(%s) :: TODO: check on memory leak, call on drop request", GetErrorMessage(r));

	listener->ProcessError(requestId, r);

	delete this;
}

void VKURequestData::OnTransactionReadyToWrite(HttpSession& httpSession, HttpTransaction& httpTransaction, int recommendedChunkSize) {
	AppLog("OnTransactionReadyToWrite");
}

void VKURequestData::OnTransactionHeaderCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction, int headerLen, bool authRequired) {
	AppLog("OnTransactionHeaderCompleted");
}

void VKURequestData::OnTransactionCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction) {
	result r;
	AppLog("OnTransactionCompleted");

	data.Flip();
	IJsonValue *pJson = JsonParser::ParseN(data);
	if(pJson != null) {
		if(pJson->GetType() == JSON_TYPE_OBJECT) {
			listener->ProcessResponseN(requestId, static_cast< JsonObject* >(pJson), targetRequestId);
		} else {
			delete pJson;
		}
	} else {
		AppLogException("Parse JSON is failed.", GetErrorMessage(r));
	}

	delete this;
}

void VKURequestData::OnTransactionCertVerificationRequiredN(HttpSession& httpSession, HttpTransaction& httpTransaction, Tizen::Base::String* pCert) {
	AppLog("OnTransactionCertVerificationRequiredN");

	httpTransaction.Resume();

	delete pCert;
}

void VKURequestData::OnSend(RequestId inputRequestId) {
	targetRequestId = inputRequestId;
	listener->AddPendingRequest(requestId);
}
