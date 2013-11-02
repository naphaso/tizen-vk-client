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

class VKURequest;

#include "VKUApi.h"
#include "IAPIRequestListener.h"

class VKURequest
	: public Tizen::Net::Http::IHttpTransactionEventListener {
public:
	VKURequest(VKUApi *api, Tizen::Base::String method, IAPIRequestListener *listener);
	virtual ~VKURequest();
	VKURequest *Put(const Tizen::Base::String &arg, const Tizen::Base::String &value);
	void Submit();

	// IHttpTransactionEventListener
	virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen);
	virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, result r);
	virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize);
	virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool authRequired);
	virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction);
	virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, Tizen::Base::String* pCert);


private:
	VKUApi *api;
	Tizen::Net::Http::HttpTransaction* pTransaction;
    Tizen::Net::Http::HttpRequest* pRequest;
    Tizen::Net::Http::HttpUrlEncodedEntity* pHttpUrlEncodedEntity;
};

#endif /* VKUREQUEST_H_ */
