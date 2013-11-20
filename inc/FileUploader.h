/*
 * FileUploader.h
 *
 *  Created on: Nov 20, 2013
 *      Author: wolong
 */

#ifndef FILEUPLOADER_H_
#define FILEUPLOADER_H_

#include <FBase.h>
#include <FIo.h>
#include <FWebJson.h>
#include <FNetHttp.h>

class PhotoUploadTrait;

#include "IAPIRequestListener.h"

class PhotoUploadTrait : public IAPIRequestListener, public Tizen::Net::Http::IHttpTransactionEventListener, public Tizen::Net::Http::IHttpProgressEventListener {
private:
	Tizen::Base::String uploadFilePath;
	Tizen::Net::Http::HttpSession httpSession;
	Tizen::Base::ByteBuffer uploadResponseData;
public:
	virtual void OnUploadError(result r) = 0;
	virtual void OnUploadSuccess(Tizen::Web::Json::JsonObject *savedPhoto) = 0;
	virtual void OnUploadProgress(long long currentLength, long long totalLength) = 0;

	void StartUpload(const Tizen::Base::String &filePath);



	virtual ~PhotoUploadTrait();

	// IAPIRequestListener
	virtual void OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object);
	virtual void OnError(result r);

	// IHttpTransactionEventListener
	virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen);
	virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, result r);
	virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize);
	virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool bAuthRequired);
	virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction);
	virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, Tizen::Base::String* pCert);

	// IHttpProgressEventListener
	virtual void OnHttpUploadInProgress(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, long long currentLength, long long totalLength);
	virtual void OnHttpDownloadInProgress(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, long long currentLength, long long totalLength);
private:
	void OnGetUploadServer(Tizen::Web::Json::JsonObject *object);
};

#endif /* FILEUPLOADER_H_ */
