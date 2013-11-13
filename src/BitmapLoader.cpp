/*
 * BitmapLoader.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: wolong
 */

#include "BitmapLoader.h"
#include <FMedia.h>

using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Media;
using namespace Tizen::Graphics;

ImageLoadingOptions::ImageLoadingOptions() {

}

BitmapLoader::BitmapLoader() {
	AppLog("constructor");

}

BitmapLoader::~BitmapLoader() {
	AppLog("destructor");
}

result BitmapLoader::Construct() {
	result r = E_SUCCESS;

	r = EventDrivenThread::Construct();
	TryCatch(r == E_SUCCESS, , "Failed to construct event driven thread");

	r = EventDrivenThread::Start();
	TryCatch(r == E_SUCCESS, , "Failed to start event driven thread");

	return E_SUCCESS;
	CATCH:
	AppLogException("Failed to construct bitmapLoader: %s", GetErrorMessage(r));
	return r;
}

bool BitmapLoader::OnStart() {
	return true;
}

void BitmapLoader::OnStop() {

}

result BitmapLoader::ImageLoaderRequest(ICacheEntry *cacheEntry) {
	ArrayList *list = new ArrayList(NoOpDeleter);
	list->Construct(3);
	list->Add(cacheEntry);
	this->SendUserEvent(1, list);
	return E_SUCCESS;
}

void BitmapLoader::OnUserEventReceivedN(RequestId requestId, IList *pArgs) {
	ICacheEntry *cacheEntry = static_cast<ICacheEntry *>(pArgs->GetAt(0));

	Image image;
	image.Construct();

	Bitmap *bitmap = image.DecodeN(cacheEntry->GetFile(), BITMAP_PIXEL_FORMAT_RGB565);
	if(GetLastResult() == E_SUCCESS) {
		cacheEntry->OnLoadingSuccess(bitmap);
	} else {
		cacheEntry->OnLoadingError();
	}

	delete pArgs;
}
