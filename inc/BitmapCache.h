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
#include <FIo.h>
#include <FSecCrypto.h>
#include <map>

class BitmapCache;

#include "IBitmapReceiver.h"
#include "BitmapLoader.h"
#include "FileDownloader.h"



typedef struct {
	RequestId requestId;
	Tizen::Ui::Control *control;
	Tizen::Base::String address;
	Tizen::Media::Image *image;
} PendingRequest;

class BitmapCache : public Tizen::Media::IImageDecodeUrlEventListener {
public:
	BitmapCache();
	result Construct();
	virtual ~BitmapCache();

	void TakeBitmap(const Tizen::Base::String &address, RequestId requestId, Tizen::Ui::Control *control);
	//void TakeBitmap(const Tizen::Base::String address, Tizen::Media::IImageDecodeUrlEventListener *listener);
	void ReleaseBitmap(Tizen::Ui::Control *control, RequestId requestId);
	void ReduceMemoryUsage();

	virtual void OnImageDecodeUrlReceived(RequestId reqId, Tizen::Graphics::Bitmap* pBitmap, result r, const Tizen::Base::String errorCode, const Tizen::Base::String errorMessage);
private:
	//Tizen::Media::Image image;
	//Tizen::Base::Collection::HashMapT<Tizen::Base::String, PendingRequest> pendingRequests;
	//Tizen::Base::Collection::LinkedList pendingRequests;
	//Tizen::Base::Collection::HashMapT<RequestId, PendingRequest*> pendingRequests;
	std::map<RequestId, PendingRequest *> pendingRequests;

	Tizen::Base::Collection::HashMap *bitmapCache;
	BitmapLoader *loader;
	FileDownloader *downloader;
};

#endif /* BITMAPCACHE_H_ */
