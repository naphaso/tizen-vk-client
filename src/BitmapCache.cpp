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
	//image.Construct();
	//pendingRequests.Construct();
	bitmapCache = new HashMap(NoOpDeleter);
	bitmapCache->Construct();
}

BitmapCache::~BitmapCache() {
	delete bitmapCache;
}

//  Tizen::Graphics::BitmapPixelFormat pixelFormat, int destWidth, int destHeight, RequestId& reqId, const IImageDecodeUrlEventListener& listener, long timeout
void BitmapCache::TakeBitmap(const Tizen::Base::String &address, RequestId requestId, Control *control, BitmapPixelFormat pixelFormat, int destWidth, int destHeigth) {
	result r;
	Uri uri;
	RequestId newRequestId;
	uri.SetUri(address);

	Image *image = new Image();
	image->Construct();

	PendingRequest *pendingRequest = new PendingRequest();
	pendingRequest->requestId = requestId;
	pendingRequest->address = address;
	pendingRequest->control = control;
	pendingRequest->image = image;



	r = image->DecodeUrl(uri, pixelFormat, destWidth, destHeigth, newRequestId, *this, 30000);
	if(r == E_SUCCESS) {
		//pendingRequests.Add(newRequestId, pendingRequest);
		pendingRequests[newRequestId] = pendingRequest;
		AppLog("send request with id %ld", newRequestId);
	} else {
		AppLog("failed send request");
	}
}

void BitmapCache::ReleaseBitmap(Control *control, RequestId requestId) {

}

void BitmapCache::ReduceMemoryUsage() {

}

void BitmapCache::OnImageDecodeUrlReceived(RequestId requestId, Bitmap* pBitmap, result r, const String errorCode, const String errorMessage) {
	AppLog("received response with id %ld", requestId);
	ArrayList *list;
	Bitmap *newBitmap;
	PendingRequest *pendingRequest = pendingRequests[requestId];

	TryCatch(pendingRequest != null, , "response on unknown request");
	//r2 = pendingRequests.GetValue(requestId, pendingRequest);
	//TryCatch(r == E_SUCCESS, , "response on unknown request");
	//r2 = pendingRequests.Remove(requestId);
	//TryCatch(r == E_SUCCESS, , "error remove pending request");
	//pendingRequests.erase(requestId);

	TryCatch(r == E_SUCCESS, , "error request image");

	AppLog("received bitmap size %dx%d", pBitmap->GetWidth(), pBitmap->GetHeight());
	AppLog("received bitmap pointer %x", pBitmap);
	newBitmap = new Bitmap();
	newBitmap->Construct(*pBitmap, Rectangle(0,0,pBitmap->GetWidth(), pBitmap->GetHeight()));
	r = bitmapCache->Add(new String(pendingRequest->address), newBitmap);
	TryCatch(r == E_SUCCESS, , "save image in cache error");

	list = new ArrayList(NoOpDeleter);
	list->Construct(0);
	//list->Add(pBitmap);

	pendingRequest->control->SendUserEvent(pendingRequest->requestId, list);
	AppLog("event sended");

	return;

	CATCH:
	AppLogException("OnImageDecodeUrlReceived is failed: %s", GetErrorMessage(r));
	return;
}

Bitmap *BitmapCache::Take(const String &address) {
	Bitmap* bitmap = static_cast<Bitmap *>(bitmapCache->GetValue(address));
	AppLog("hashmap bitmap pointer %x", bitmap);
	AppLog("hashmap bitmap size %dx%d", bitmap->GetWidth(), bitmap->GetHeight());
	return bitmap;
}
