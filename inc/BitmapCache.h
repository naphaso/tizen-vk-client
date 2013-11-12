/*
 * BitmapCache.h
 *
 *  Created on: Nov 10, 2013
 *      Author: wolong
 */

#ifndef BITMAPCACHE_H_
#define BITMAPCACHE_H_

#include <FBase.h>
#include <FMedia.h>
#include <FGraphics.h>
#include <FUi.h>

class BitmapCache;

#include "IBitmapReceiver.h"

typedef struct {
	RequestId requestId;
	Tizen::Ui::Control *control;
	Tizen::Base::String address;
} PendingRequest;

class BitmapCache : public Tizen::Media::IImageDecodeUrlEventListener {
public:
	BitmapCache();
	virtual ~BitmapCache();

	void TakeBitmap(const Tizen::Base::String &address, RequestId &requestId, Tizen::Ui::Control *control, Tizen::Graphics::BitmapPixelFormat pixelFormat, int destWidth, int destHeigth);
	//void TakeBitmap(const Tizen::Base::String address, Tizen::Media::IImageDecodeUrlEventListener *listener);
	void ReleaseBitmap(Tizen::Ui::Control *control);
	void ReduceMemoryUsage();

	virtual void OnImageDecodeUrlReceived(RequestId reqId, Tizen::Graphics::Bitmap* pBitmap, result r, const Tizen::Base::String errorCode, const Tizen::Base::String errorMessage);
private:
	Tizen::Media::Image image;
	//Tizen::Base::Collection::HashMapT<Tizen::Base::String, PendingRequest> pendingRequests;
	//Tizen::Base::Collection::LinkedList pendingRequests;
	Tizen::Base::Collection::HashMapT<RequestId, PendingRequest*> pendingRequests;

	RequestId requestIdCounter;

	RequestId GetNewRequestId();
};

#endif /* BITMAPCACHE_H_ */
