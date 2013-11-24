/*
 * VKUServiceProxy.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: wolong
 */

#include "VKUServiceProxy.h"
#include "VKU.h"
#include "AppResourceId.h"
#include "VKUDialogPanel.h"
#include "ObjectCounter.h"


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Collection;
using namespace Tizen::Io;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

static const int CHECK_INTERVAL = 1000; // Checking interval in sec.

static const wchar_t* LOCAL_MESSAGE_PORT_NAME = L"UI_PORT";

VKUServiceProxy::VKUServiceProxy(void) :
		pLocalMessagePort(null),
		pRemoteMessagePort(null),
		_readEventListener(null),
		_audioProgressListener(null),
		_audioElement(null) {
	CONSTRUCT(L"VKUServiceProxy");
}

VKUServiceProxy::~VKUServiceProxy(void) {
	DESTRUCT(L"VKUServiceProxy");
}

result VKUServiceProxy::Construct(const AppId& appId, const String& remotePortName) {
	result r = E_FAILURE;

	this->appId = appId;

	AppManager* pAppManager = AppManager::GetInstance();
	TryReturn(pAppManager != null, E_FAILURE, "VKU : Fail to get AppManager instance.");

	AppLog("VKU : Checking service status for time out 5 sec...");

	for (int i = 0; i < 5; ++i) {
		if (pAppManager->IsRunning(appId)) {
			AppLog("VKU : Service is ready");
			break;
		} else {
			AppLog("VKU : Service is not ready. try to launch.");
			r = pAppManager->LaunchApplication(appId, null);
			TryReturn(!IsFailed(r), r, "VKU : [%s]", GetErrorMessage(r));
			Thread::Sleep(CHECK_INTERVAL);
		}
	}

	TryReturn(pAppManager->IsRunning(appId), E_FAILURE, "VKU : The service is not working.");

	pLocalMessagePort = MessagePortManager::RequestLocalMessagePort(LOCAL_MESSAGE_PORT_NAME);
	TryReturn(pLocalMessagePort != null, E_FAILURE, "[E_FAILURE] Failed to get LocalMessagePort instance.");

	pLocalMessagePort->AddMessagePortListener(*this);

	pRemoteMessagePort = MessagePortManager::RequestRemoteMessagePort(appId, remotePortName);
	TryReturn(pRemoteMessagePort != null, E_FAILURE, "[E_FAILURE] Failed to get LocalMessagePort instance.");

	AppLog("LocalMessagePort(\"%ls\") is ready", pLocalMessagePort->GetName().GetPointer());

	// send connect request
	HashMap *pMap =	new HashMap(SingleObjectDeleter);
	pMap->Construct();
	pMap->Add(new String(L"request"), new String(L"connect"));
	r = SendMessage(pMap);
	delete pMap;

	return E_SUCCESS;
}

result VKUServiceProxy::SendMessage(const IMap* pMessage) {
	result r = E_SUCCESS;
	AppLog("SendMessage is called.");

	if (pRemoteMessagePort != null) {
		r = pRemoteMessagePort->SendMessage(pLocalMessagePort, pMessage);
	} else {
		r = E_FAILURE;
	}

	return r;
}

void VKUServiceProxy::OnMessageReceivedN(RemoteMessagePort* pRemoteMessagePort, IMap* pMessage) {
	AppLog("VKU : A response message is Received.");

	VKUApp* pApp = static_cast<VKUApp*>(App::GetInstance());

	if (pApp != null) {
		String* event = static_cast<String*>(pMessage->GetValue(String(L"event")));
		if (event != null) {

			if(event->CompareTo(L"newmessage") == 0) {
				int messageId;
				Integer::Parse(*static_cast<String *>(pMessage->GetValue(String(L"messageid"))), messageId);

				Frame* frame = pApp->GetFrame(FRAME_NAME);
				Form* form = frame->GetCurrentForm();
				if (form->GetName() == IDF_DIALOG) {
					VKUDialogPanel* pDialogPanel = static_cast<VKUDialogPanel*>(form->GetControl(IDC_PANEL_DIALOG));
					if (pDialogPanel != null) {
						pDialogPanel->LoadNewMessage(messageId);
					}
				}
			} else if(event->CompareTo(L"typing") == 0) {
				Frame* frame = pApp->GetFrame(FRAME_NAME);
				Form* form = frame->GetCurrentForm();
				if (form->GetName() == IDF_DIALOG) {
					VKUDialogPanel* pDialogPanel = static_cast<VKUDialogPanel*>(form->GetControl(IDC_PANEL_DIALOG));
					if (pDialogPanel != null) {
						pDialogPanel->OnTyping();
					}
				}
			} else if(event->CompareTo("read") == 0) {
				int messageId;
				Integer::Parse(*static_cast<String *>(pMessage->GetValue(String(L"msg_id"))), messageId);

				if(_readEventListener != null) {
					_readEventListener->OnReadEvent(messageId);
				}
			} else if(event->CompareTo(L"status") == 0) {
				int userId;
				bool online;
				bool current;

				Integer::Parse(*static_cast<String *>(pMessage->GetValue(String(L"user_id"))), userId);
				online = static_cast<String *>(pMessage->GetValue(String(L"status")))->CompareTo(L"online") == 0;
				current = static_cast<String *>(pMessage->GetValue(String(L"current")))->CompareTo(L"true") == 0;

				// TODO: status processing
				// current = user in current dialog?
			} else if(event->CompareTo("audio-progress") == 0) {
				long duration, position;

				Long::Parse(*static_cast<String *>(pMessage->GetValue(String(L"duration"))), duration);
				Long::Parse(*static_cast<String *>(pMessage->GetValue(String(L"position"))), position);

				if(_audioProgressListener != null) {
					_audioProgressListener->OnAudioProgress(duration, position);
				}

				if(_audioElement != null) {
					_audioElement->OnProgress((int)(((double)position / (double)duration)*100));
				}
			}
		}
	}


	delete pMessage;
}

void VKUServiceProxy::PlayAudio(const String & url) {
	currentUrl = url;
	result r = E_SUCCESS;
	HashMap *pMap =	new HashMap(SingleObjectDeleter);
	pMap->Construct();
	pMap->Add(new String(L"request"), new String(L"audio-play"));
	pMap->Add(new String(L"audio-url"), new String(url));
	r = SendMessage(pMap);
	delete pMap;
}

void VKUServiceProxy::PauseAudio() {
	result r = E_SUCCESS;
	HashMap *pMap =	new HashMap(SingleObjectDeleter);
	pMap->Construct();
	pMap->Add(new String(L"request"), new String(L"audio-pause"));
	r = SendMessage(pMap);
	delete pMap;
}

void VKUServiceProxy::SeekAudio(int value) {
	result r = E_SUCCESS;
	HashMap *pMap =	new HashMap(SingleObjectDeleter);
	pMap->Construct();
	pMap->Add(new String(L"request"), new String(L"audio-seek"));
	pMap->Add(new String(L"seek"), new String(Integer::ToString(value)));
	r = SendMessage(pMap);
	delete pMap;
}

void VKUServiceProxy::SubscribeNotifications(int userId) {
	result r = E_SUCCESS;
	HashMap *pMap =	new HashMap(SingleObjectDeleter);
	pMap->Construct();
	pMap->Add(new String(L"request"), new String(L"subscribe"));
	pMap->Add(new String(L"userid"), new String(Integer::ToString(userId)));
	r = SendMessage(pMap);
	delete pMap;
}

void VKUServiceProxy::UnsubscribeNotifications(int userId) {
	result r = E_SUCCESS;
	HashMap *pMap =	new HashMap(SingleObjectDeleter);
	pMap->Construct();
	pMap->Add(new String("request"), new String("unsubscribe"));
	pMap->Add(new String(L"userid"), new String(Integer::ToString(userId)));
	r = SendMessage(pMap);
	delete pMap;
}

void VKUServiceProxy::SubscribeReadEvents(IReadEventListener *readEventListener) {
	_readEventListener = readEventListener;
}

void VKUServiceProxy::UnsubscribeReadEvents() {
	_readEventListener = null;
}

void VKUServiceProxy::SetAudioProgressListener(IAudioProgressListener *audioProgressListener) {
	_audioProgressListener = audioProgressListener;
}

void VKUServiceProxy::UnsetAudioProgressListener() {
	_audioProgressListener = null;
}

void VKUServiceProxy::SetCurrentAudioElement(MessageAudioElement *element) {
	if(_audioElement != null) {
		if(_audioElement != element) {
			_audioElement->OnReset();
		}
	}

	_audioElement = element;
}

void VKUServiceProxy::ResetCurrentAudioElement(MessageAudioElement *element) {
	if(_audioElement == element) {
		_audioElement = null;
	}
}

bool VKUServiceProxy::IsAudioCurrent(const String &url) {
	if(currentUrl.CompareTo(url) == 0) {
		return true;
	} else {
		return false;
	}
}

void VKUServiceProxy::ContactsSync() {
	result r = E_SUCCESS;
	HashMap *pMap =	new HashMap(SingleObjectDeleter);
	pMap->Construct();
	pMap->Add(new String("request"), new String("contacts-sync"));
	r = SendMessage(pMap);
	delete pMap;
}
