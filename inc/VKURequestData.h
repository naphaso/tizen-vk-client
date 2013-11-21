/*
 * VKURequestData.h
 *
 *  Created on: Nov 3, 2013
 *      Author: wolong
 */

#ifndef VKUREQUESTDATA_H_
#define VKUREQUESTDATA_H_

#include <FBase.h>
#include <FNet.h>
#include <FWebJson.h>

class VKURequestData;

#include "IAPIRequestListener.h"
#include "VKUApi.h"

class VKURequestData : public Tizen::Base::Object, public Tizen::Net::Http::IHttpTransactionEventListener {
public:
	VKURequestData(Tizen::Net::Http::HttpTransaction *httpTransaction, IAPIRequestListener *requestListener);
	virtual ~VKURequestData();
	Tizen::Base::ByteBuffer data;
	Tizen::Net::Http::HttpTransaction *httpTransaction;
	IAPIRequestListener *listener;
	Tizen::Base::UuId requestId;
	RequestId targetRequestId;

	void OnSend(RequestId requestId);

	// IHttpTransactionEventListener
	virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen);
	virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, result r);
	virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize);
	virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool authRequired);
	virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction);
	virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, Tizen::Base::String* pCert);

};


#endif /* VKUREQUESTDATA_H_ */
