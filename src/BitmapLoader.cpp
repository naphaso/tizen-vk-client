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
	// TODO Auto-generated destructor stub
}

result BitmapLoader::Construct() {
	result r = E_SUCCESS;
	r = EventDrivenThread::Construct();

	return r;
}

bool BitmapLoader::OnStart() {
	return true;
}

void BitmapLoader::OnStop() {

}

result BitmapLoader::ImageLoaderRequest(RequestId requestId, Control *control, const String &path, BitmapPixelFormat pixelFormat) {
	ArrayList *list = new ArrayList(NoOpDeleter);
	list->Construct(3);
	list->Add(control);
	list->Add(new String(path));
	list->Add(new Integer(pixelFormat));
	this->SendUserEvent(requestId, list);
	return E_SUCCESS;
}

result BitmapLoader::ImageLoaderRequest(RequestId requestId, Control *control, const String &path, BitmapPixelFormat pixelFormat, int width, int height) {
	ArrayList *list = new ArrayList(NoOpDeleter);
	list->Construct(5);
	list->Add(control);
	list->Add(new String(path));
	list->Add(new Integer(pixelFormat));
	list->Add(new Integer(width));
	list->Add(new Integer(height));
	this->SendUserEvent(requestId, list);
	return E_SUCCESS;
}

void BitmapLoader::OnUserEventReceivedN(RequestId requestId, IList *pArgs) {
	Control *control = static_cast<Control *>(pArgs->GetAt(0));
	String *path = static_cast<String*>(pArgs->GetAt(1));
	Integer *pixelFormatInt = static_cast<Integer *>(pArgs->GetAt(2));
	BitmapPixelFormat pixelFormat = static_cast<BitmapPixelFormat>(pixelFormatInt->ToInt());
	Integer *width = static_cast<Integer *>(pArgs->GetAt(3));
	Integer *height = static_cast<Integer *>(pArgs->GetAt(4));

	Image image;
	image.Construct();

	Bitmap *bitmap;
	if(width != null && height != null) {
		bitmap = image.DecodeN(*path, pixelFormat, width->ToInt(), height->ToInt());
		delete width;
		delete height;
	}

	delete pixelFormatInt;
	delete path;
	delete pArgs;

	ArrayList *result = new ArrayList(NoOpDeleter);
	result->Construct(1);
	result->Add(bitmap);
	control->SendUserEvent(requestId, result);
}
