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

#define BITMAP_LOADED 31337

class BitmapCache;
class ICacheEntry;
Tizen::Base::String CacheFileFromUrl(const Tizen::Base::String &url);

#include "IBitmapReceiver.h"
#include "BitmapLoader.h"
#include "FileDownloader.h"



class ICacheEntry : public Tizen::Base::Object {
public:
	virtual ~ICacheEntry() {};
	virtual Tizen::Base::String GetUrl() = 0;
	virtual Tizen::Base::String GetFile() = 0;
	virtual void OnDownloadSuccess() = 0;
	virtual void OnDownloadError() = 0;
	virtual void OnLoadingSuccess(Tizen::Graphics::Bitmap *bitmap) = 0;
	virtual void OnLoadingError() = 0;
};

class BitmapCache {
public:
	BitmapCache();
	result Construct();
	virtual ~BitmapCache();

	void TakeBitmap(const Tizen::Base::String &address, Tizen::Ui::Control *control);
	void ReleaseBitmap(const Tizen::Base::String &address, Tizen::Ui::Control *control);
	void ReduceMemoryUsage();
private:
	Tizen::Base::Collection::HashMap *bitmapCache;
	BitmapLoader *loader;
	FileDownloader *downloader;
};

#endif /* BITMAPCACHE_H_ */
