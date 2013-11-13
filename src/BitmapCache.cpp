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
using namespace Tizen::Io;
using namespace Tizen::Security::Crypto;

const wchar_t *hexTable[] = {L"00", L"01", L"02", L"03", L"04", L"05", L"06", L"07", L"08", L"09", L"0a", L"0b", L"0c", L"0d", L"0e", L"0f", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"1a", L"1b", L"1c", L"1d", L"1e", L"1f", L"20", L"21", L"22", L"23", L"24", L"25", L"26", L"27", L"28", L"29", L"2a", L"2b", L"2c", L"2d", L"2e", L"2f", L"30", L"31", L"32", L"33", L"34", L"35", L"36", L"37", L"38", L"39", L"3a", L"3b", L"3c", L"3d", L"3e", L"3f", L"40", L"41", L"42", L"43", L"44", L"45", L"46", L"47", L"48", L"49", L"4a", L"4b", L"4c", L"4d", L"4e", L"4f", L"50", L"51", L"52", L"53", L"54", L"55", L"56", L"57", L"58", L"59", L"5a", L"5b", L"5c", L"5d", L"5e", L"5f", L"60", L"61", L"62", L"63", L"64", L"65", L"66", L"67", L"68", L"69", L"6a", L"6b", L"6c", L"6d", L"6e", L"6f", L"70", L"71", L"72", L"73", L"74", L"75", L"76", L"77", L"78", L"79", L"7a", L"7b", L"7c", L"7d", L"7e", L"7f", L"80", L"81", L"82", L"83", L"84", L"85", L"86", L"87", L"88", L"89", L"8a", L"8b", L"8c", L"8d", L"8e", L"8f", L"90", L"91", L"92", L"93", L"94", L"95", L"96", L"97", L"98", L"99", L"9a", L"9b", L"9c", L"9d", L"9e", L"9f", L"a0", L"a1", L"a2", L"a3", L"a4", L"a5", L"a6", L"a7", L"a8", L"a9", L"aa", L"ab", L"ac", L"ad", L"ae", L"af", L"b0", L"b1", L"b2", L"b3", L"b4", L"b5", L"b6", L"b7", L"b8", L"b9", L"ba", L"bb", L"bc", L"bd", L"be", L"bf", L"c0", L"c1", L"c2", L"c3", L"c4", L"c5", L"c6", L"c7", L"c8", L"c9", L"ca", L"cb", L"cc", L"cd", L"ce", L"cf", L"d0", L"d1", L"d2", L"d3", L"d4", L"d5", L"d6", L"d7", L"d8", L"d9", L"da", L"db", L"dc", L"dd", L"de", L"df", L"e0", L"e1", L"e2", L"e3", L"e4", L"e5", L"e6", L"e7", L"e8", L"e9", L"ea", L"eb", L"ec", L"ed", L"ee", L"ef", L"f0", L"f1", L"f2", L"f3", L"f4", L"f5", L"f6", L"f7", L"f8", L"f9", L"fa", L"fb", L"fc", L"fd", L"fe", L"ff"};

String CacheFileFromUrl(const String &url) {
	Md5Hash hash;
	ByteBuffer *utf8url = StringUtil::StringToUtf8N(url);
	hash.Initialize();
	hash.Update(*utf8url);
	ByteBuffer *hashBuffer = hash.FinalizeN();

	String hashString(VKUApp::GetInstance()->GetCacheDir());
	byte currentByte;
	while(hashBuffer->GetRemaining() > 0) {
		hashBuffer->GetByte(currentByte);
		hashString.Append(hexTable[currentByte]);
	}
	hashString.Append(".jpg");

	delete utf8url;
	delete hashBuffer;

	return hashString;
}

typedef enum {
	CACHE_ENTRY_STATE_NOT_FOUND,
	CACHE_ENTRY_STATE_DOWNLOADING,
	CACHE_ENTRY_STATE_FILE,
	CACHE_ENTRY_STATE_LOADING,
	CACHE_ENTRY_STATE_MEMORY
} CacheEntryState;

class CacheEntry : public ICacheEntry {
private:
	FileDownloader *_downloader;
	BitmapLoader *_loader;

	CacheEntryState _state;
	String _url;
	String _file;
	Bitmap *_bitmap;
	ArrayList _subscribers;

	void StartDownloading() {
		_state = CACHE_ENTRY_STATE_DOWNLOADING;
		_downloader->DownloadImage(this);
	}

	void StartLoading() {
		_state = CACHE_ENTRY_STATE_LOADING;
		_loader->ImageLoaderRequest(this);
	}

	void SendEventsToAll() {
		for(int i = 0; i < _subscribers.GetCount(); i++) {
			SendEvent(static_cast<Control *>(_subscribers.GetAt(i)));
		}
	}

	void SendEvent(Control *control) {
		ArrayList *list = new ArrayList(NoOpDeleter);
		list->Construct(1);
		list->Add(_bitmap);
		control->SendUserEvent(BITMAP_LOADED, list); // BITMAP_LOADED_EVENT
	}
public:
	CacheEntry(const String &url, FileDownloader *downloader, BitmapLoader *loader)
			: _url(url), _file(CacheFileFromUrl(url)), _downloader(downloader), _loader(loader), _subscribers(NoOpDeleter) {
		_subscribers.Construct();
		if(File::IsFileExist(_file)) {
			_state = CACHE_ENTRY_STATE_FILE;
		} else {
			_state = CACHE_ENTRY_STATE_NOT_FOUND;
		}
	}

	CacheEntryState GetState() {
		return _state;
	}

	virtual String GetUrl() {
		return _url;
	}

	virtual String GetFile() {
		return _file;
	}

	virtual ~CacheEntry() {
		AppLog("cache entry desctructor. TODO: implement it");
	}

	void AddSubscriber(Control *control) {
		_subscribers.Add(control);
		switch(_state) {
		case CACHE_ENTRY_STATE_NOT_FOUND:
			AppLog("new subscriber on cache entry, entry not found, downloading...");
			StartDownloading();
			break;
		case CACHE_ENTRY_STATE_FILE:
			AppLog("new subscriber on cache entry, entry in file, loading...");
			StartLoading();
			break;
		case CACHE_ENTRY_STATE_MEMORY:
			AppLog("new subscriber on cache entry, entry in memory, send bitmap...");
			SendEvent(control);
			break;
		default:
			break;
		}
	}

	void RemoveSubscriber(Control *control) {
		result r;
		r = _subscribers.Remove(*control);
		if(r != E_SUCCESS) {
			AppLog("WARNING: unsubscribe unsubscribed!!!!!!!!!!!!!!");
		}
	}

	virtual void OnDownloadSuccess() {
		if(_state == CACHE_ENTRY_STATE_DOWNLOADING && File::IsFileExist(_file)) {
			AppLog("file downloaded");
			_state = CACHE_ENTRY_STATE_FILE;
			if(_subscribers.GetCount() != 0) {
				_state = CACHE_ENTRY_STATE_LOADING;
				StartLoading();
			}
		} else {
			AppLog("WARNING: illegal state: downloaded event not on DOWNLOADING state, or file don't exists");
		}
	}

	virtual void OnDownloadError() {
		if(_state == CACHE_ENTRY_STATE_DOWNLOADING) {
			AppLog("file downloading error");
			_state = CACHE_ENTRY_STATE_NOT_FOUND;
		} else {
			AppLog("WARNING: illegal state: downloading error not on DOWNLOADING state, or file don't exists");
		}
	}

	virtual void OnLoadingSuccess(Bitmap *bitmap) {
		if(_state == CACHE_ENTRY_STATE_LOADING) {
			AppLog("bitmap loaded");
			_bitmap = bitmap;
			_state = CACHE_ENTRY_STATE_MEMORY;
			if(_subscribers.GetCount() != 0) {
				SendEventsToAll();
			}
		} else {
			AppLog("WARNING: illegal state: loaded event not on LOADING state");
		}
	}

	virtual void OnLoadingError() {
		if(_state == CACHE_ENTRY_STATE_LOADING) {
			AppLog("bitmap loading error");
			_state = CACHE_ENTRY_STATE_NOT_FOUND;
			File::Remove(_file);
			if(_subscribers.GetCount() != 0) {
				StartDownloading();
			}
		} else {
			AppLog("WARNING: illegal state: loading error not on LOADING state");
		}
	}

	bool TrimMemory() {
		if(_state == CACHE_ENTRY_STATE_MEMORY && _subscribers.GetCount() == 0) {
			AppLog("trim memory, delete bitmap");
			_state = CACHE_ENTRY_STATE_FILE;
			delete _bitmap;
			return true;
		} else {
			AppLog("trim memory, not needed or not possible");
			return false;
		}
	}
};



BitmapCache::BitmapCache() {

}

result BitmapCache::Construct() {
	result r;
	String cacheDir;
	AppLog("constructor");

	bitmapCache = new (std::nothrow) HashMap(SingleObjectDeleter);
	TryCatch(bitmapCache != null, r = E_FAILURE, "failed to allocate bitmap cache hashmap");

	r = bitmapCache->Construct();
	TryCatch(r == E_SUCCESS, , "Failed to construct hashMap");

	cacheDir = VKUApp::GetInstance()->GetCacheDir();
	AppLog("cache dir: %ls", cacheDir.GetPointer());
	if(!File::IsFileExist(cacheDir)) {
		r = Directory::Create(cacheDir);
		TryCatch(r == E_SUCCESS, , "Failed to create cache dir");
	}

	loader = new (std::nothrow) BitmapLoader();
	TryCatch(loader != null, r = E_FAILURE, "fail to allocate bitmap loader");
	r = loader->Construct();
	TryCatch(r == E_SUCCESS, , "Failed to construct BitmapLoader");

	downloader = new (std::nothrow) FileDownloader();
	TryCatch(downloader != null, r = E_FAILURE, "fail to allocate file downloader");

	r = downloader->Construct();
	TryCatch(r == E_SUCCESS, , "Failed to construct FileDownloader");

	return E_SUCCESS;
	CATCH:
	AppLogException("Failed to construct bitmap cache: %s", GetErrorMessage(r));
	return r;
}

BitmapCache::~BitmapCache() {
	delete bitmapCache;
	delete downloader;
	delete loader;
}

//  Tizen::Graphics::BitmapPixelFormat pixelFormat, int destWidth, int destHeight, RequestId& reqId, const IImageDecodeUrlEventListener& listener, long timeout
void BitmapCache::TakeBitmap(const String &address, Control *control) {
	AppLog("getting cache entry %ls from bitmap cache", address.GetPointer());
	CacheEntry *cacheEntry = static_cast<CacheEntry *>(bitmapCache->GetValue(address));
	if(cacheEntry == null) {
		AppLog("cache entry not found, creating new");
		cacheEntry = new CacheEntry(address, downloader, loader);
		bitmapCache->Add(new String(address), cacheEntry);
	}

	cacheEntry->AddSubscriber(control);
}

void BitmapCache::ReleaseBitmap(const String &address, Control *control) {
	AppLog("release bitmap");
	CacheEntry *cacheEntry = static_cast<CacheEntry *>(bitmapCache->GetValue(address));
	if(cacheEntry == null) {
		AppLog("WARNING: release unknown cache entry!!!!!!!!!!!");
	} else {
		cacheEntry->RemoveSubscriber(control);
	}
}

void BitmapCache::ReduceMemoryUsage() {
	AppLog("reduce memory usage");
	// TODO: iterate on each cache entry and trim memory
}

