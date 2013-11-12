/*
 * FileDownloader.h
 *
 *  Created on: Nov 12, 2013
 *      Author: wolong
 */

#ifndef FILEDOWNLOADER_H_
#define FILEDOWNLOADER_H_

#include <FBase.h>
#include <FNetHttp.h>
#include <FUi.h>

class FileDownloader;

#include "BitmapLoader.h"

class FileDownloader : public Tizen::Net::Http::IHttpTransactionEventListener {
public:
	FileDownloader(BitmapLoader *loader);
	result Construct();
	virtual ~FileDownloader();

	result DownloadImage(const Tizen::Base::String &url, const Tizen::Base::String &file, Tizen::Ui::Control *control, RequestId requestId);

	// IHttpTransactionEventListener
	virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen);
	virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, result r);
	virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize);
	virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool authRequired);
	virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction);
	virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, Tizen::Base::String* pCert);

private:
	Tizen::Net::Http::HttpSession *httpSession;
	BitmapLoader *loader;
};

#endif /* FILEDOWNLOADER_H_ */
