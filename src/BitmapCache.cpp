/*
 * BitmapCache.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: wolong
 */

#include "BitmapCache.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::Media;
using namespace Tizen::Base::Utility;
using namespace Tizen::Ui;

BitmapCache::BitmapCache() {
	image.Construct();
	pendingRequests.Construct();
	requestIdCounter = 1000;
}

BitmapCache::~BitmapCache() {
	// TODO Auto-generated destructor stub
}

//  Tizen::Graphics::BitmapPixelFormat pixelFormat, int destWidth, int destHeight, RequestId& reqId, const IImageDecodeUrlEventListener& listener, long timeout
void BitmapCache::TakeBitmap(const Tizen::Base::String &address, RequestId &requestId, Control *control, BitmapPixelFormat pixelFormat, int destWidth, int destHeigth) {
	Uri uri;
	uri.SetUri(address);

	PendingRequest *pendingRequest = new PendingRequest();
	pendingRequest->requestId = requestId;
	pendingRequest->address = address;
	pendingRequest->control = control;

	RequestId newRequestId = GetNewRequestId();

	pendingRequests.Add(newRequestId, pendingRequest);

	image.DecodeUrl(uri, pixelFormat, destWidth, destHeigth, newRequestId, *this, 30);
}

void BitmapCache::ReleaseBitmap(Control *control, RequestId &requestId) {

}

void BitmapCache::ReduceMemoryUsage() {

}

void BitmapCache::OnImageDecodeUrlReceived(RequestId requestId, Bitmap* pBitmap, result r, const String errorCode, const String errorMessage) {
	result r2;
	PendingRequest *pendingRequest;
	r2 = pendingRequests.GetValue(requestId, pendingRequest);
	TryCatch(r == E_SUCCESS, , "response on unknown request");
	r2 = pendingRequests.Remove(requestId);
	TryCatch(r == E_SUCCESS, , "error remove pending request");

	if(r == E_SUCCESS) {
		ArrayList *list = new ArrayList(NoOpDeleter);
		list->Construct(1);
		list->Add(pBitmap);
		pendingRequest->control->SendUserEvent(pendingRequest->requestId, list);
	}

	CATCH:
	AppLogException("OnImageDecodeUrlReceived is failed.", GetErrorMessage(r2));
	return;
}


RequestId BitmapCache::GetNewRequestId() {
	return requestIdCounter++;
}
