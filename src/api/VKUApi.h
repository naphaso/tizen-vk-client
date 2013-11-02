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

#include "VKURequest.h"
#include "IAPIRequestListener.h"

class VKUApi
	: public Tizen::Net::Http::IHttpTransactionEventListener
	  {
public:
	VKUApi();
	virtual ~VKUApi();

	result request();

	// IHttpTransactionEventListener
	virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen);
	virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, result r);
	virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize);
	virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool authRequired);
	virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction);
	virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, Tizen::Base::String* pCert);

	VKURequest *CreateRequest(Tizen::Base::String method, IAPIRequestListener *listener);

	Tizen::Net::Http::HttpSession* GetHttpSession();
private:
	Tizen::Net::Http::HttpSession* httpSession;
};

#endif /* VKUAPI_H_ */
