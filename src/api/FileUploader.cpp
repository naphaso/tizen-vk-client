/*
 * FileUploader.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: wolong
 */

#include "FileUploader.h"
#include "VKUApi.h"
#include "Requests.h"
#include "JsonParseUtils.h"



using namespace Tizen::Base;
using namespace Tizen::Io;
using namespace Tizen::Web::Json;
using namespace Tizen::Net::Http;



void PhotoUploadTrait::StartUpload(const String &filePath) {
	uploadFilePath = filePath;
	VKUApi::GetInstance().CreateRequest(L"photos.getMessagesUploadServer", this)->Submit(REQUEST_GET_UPLOAD_SERVER);
}

PhotoUploadTrait::~PhotoUploadTrait() {
	httpSession.CloseAllTransactions();
}


void PhotoUploadTrait::OnResponseN(RequestId requestId, JsonObject *object) {
	switch(requestId) {
		case REQUEST_GET_UPLOAD_SERVER:
			OnGetUploadServer(object);
			break;
		case REQUEST_SAVE_PHOTO:
			OnUploadSuccess(object);
			break;
	}
}

void PhotoUploadTrait::OnError(result r) {
	AppLogException("http request on error: %s", GetErrorMessage(r));
	OnUploadError(r);
}

// IHttpTransactionEventListener

void PhotoUploadTrait::OnTransactionReadyToRead(HttpSession& httpSession, HttpTransaction& httpTransaction, int availableBodyLen) {
	HttpResponse* httpResponse = httpTransaction.GetResponse();
	if (httpResponse->GetHttpStatusCode() == HTTP_STATUS_OK) {
		ByteBuffer *bodyBuffer = httpResponse->ReadBodyN();
		uploadResponseData.CopyFrom(*bodyBuffer);
		delete bodyBuffer;
	} else {
		AppLog("response invalid code: %d", httpResponse->GetHttpStatusCode());
		OnUploadError(E_FAILURE);
	}
}

void PhotoUploadTrait::OnTransactionAborted(HttpSession& httpSession, HttpTransaction& httpTransaction, result r) {
	AppLogException("upload http transaction aborted: %s", GetErrorMessage(r));
	OnUploadError(r);
}

void PhotoUploadTrait::OnTransactionReadyToWrite(HttpSession& httpSession, HttpTransaction& httpTransaction, int recommendedChunkSize) {

}

void PhotoUploadTrait::OnTransactionHeaderCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction, int headerLen, bool bAuthRequired) {

}

void PhotoUploadTrait::OnTransactionCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction) {
	result r = E_SUCCESS;
	IJsonValue *responseJson;
	JsonObject *responseJsonObject;
	String photoValue;

	uploadResponseData.Flip();

	responseJson = JsonParser::ParseN(uploadResponseData);
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "failed to parse upload response json");
	TryCatch(responseJson->GetType() == JSON_TYPE_OBJECT, r = E_PARSING_FAILED, "response is not json object");

	responseJsonObject = static_cast<JsonObject *>(responseJson);

	r = JsonParseUtils::GetString(*responseJsonObject, L"photo", photoValue);
	TryCatch(r == E_SUCCESS, , "failed to get photo string from upload response json");

	VKUApi::GetInstance().CreateRequest(L"photos.saveMessagesPhoto", this)->Put(L"photo", photoValue)->Submit(REQUEST_SAVE_PHOTO);

	delete &httpTransaction;
	return;
	CATCH:
	AppLogException("failed OnTransactionCompleted: %s", GetErrorMessage(r));
	OnUploadError(r);
	delete &httpTransaction;
	return;
}

void PhotoUploadTrait::OnTransactionCertVerificationRequiredN(HttpSession& httpSession, HttpTransaction& httpTransaction, Tizen::Base::String* pCert) {
	httpTransaction.Resume();
	delete pCert;
}

void PhotoUploadTrait::OnHttpUploadInProgress(HttpSession& httpSession, HttpTransaction& httpTransaction, long long currentLength, long long totalLength) {
	OnUploadProgress(currentLength, totalLength);
}

void PhotoUploadTrait::OnHttpDownloadInProgress(HttpSession& httpSession, HttpTransaction& httpTransaction, long long currentLength, long long totalLength) {

}


void PhotoUploadTrait::OnGetUploadServer(JsonObject *object) {
	result r = E_SUCCESS;
	JsonObject *response;
	HttpTransaction *httpTransaction;
	HttpRequest *request;
	HttpMultipartEntity *entity;
	String uploadUrl;

	r = JsonParseUtils::GetObject(object, L"response", response);
	TryCatch(r == E_SUCCESS, , "failed to get response from object");

	r = JsonParseUtils::GetString(*response, L"upload_url", uploadUrl);
	TryCatch(r == E_SUCCESS, , "failed to get upload_url from response");

	r = httpSession.Construct(NET_HTTP_SESSION_MODE_NORMAL, null, uploadUrl, null);
	TryCatch(r == E_SUCCESS, , "failed to construct http session");

	httpTransaction = httpSession.OpenTransactionN();
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "failed to open transaction");

	r = httpTransaction->AddHttpTransactionListener(*this);
	TryCatch(r == E_SUCCESS, , "failed to add transaction listener");

	r = httpTransaction->SetHttpProgressListener(*this);
	TryCatch(r == E_SUCCESS, , "failed to set http progress listener");

	request = httpTransaction->GetRequest();

	r = request->SetMethod(NET_HTTP_METHOD_POST);
	TryCatch(r == E_SUCCESS, , "failed to set post http method");

	r = request->SetUri(uploadUrl);
	TryCatch(r == E_SUCCESS, , "failed to set upload request uri");

	entity = new (std::nothrow) HttpMultipartEntity();
	TryCatch(entity != null, r = E_OUT_OF_MEMORY, "failed to allocate HttpMultipartEntity");

	r = entity->Construct();
	TryCatch(r == E_SUCCESS, , "failed to construct http multipart entity");

	r = entity->AddFilePart(L"photo", uploadFilePath, L"photo.jpg", L"image/jpeg", L"ISO-8859-1");
	TryCatch(r == E_SUCCESS, , "failed to add file to request");

	r = request->SetEntity(*entity);
	TryCatch(r == E_SUCCESS, , "failed to set entity in request");

	r = uploadResponseData.Construct(4096);
	TryCatch(r == E_SUCCESS, , "failed to construct buffer for upload response data");

	r = httpTransaction->Submit();
	TryCatch(r == E_SUCCESS, , "failed to submit http transaction");

	return;
	CATCH:
	AppLogException("failed OnGetUploadServer: %s", GetErrorMessage(r));
	OnUploadError(r);
	return;
}

