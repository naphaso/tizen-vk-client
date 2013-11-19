/*
 * VKUServiceProxy.h
 *
 *  Created on: Nov 4, 2013
 *      Author: wolong
 */

#ifndef VKUSERVICEPROXY_H_
#define VKUSERVICEPROXY_H_

#include <FApp.h>
#include <FBase.h>
#include <FIo.h>

class VKUServiceProxy;

#include "IReadEventListener.h"

class VKUServiceProxy : public Tizen::Io::IMessagePortListener {
public:
	VKUServiceProxy(void);
	~VKUServiceProxy(void);

	result Construct(const Tizen::App::AppId& appId, const Tizen::Base::String& remotePortName);
	result SendMessage(const Tizen::Base::Collection::IMap* pMessage);

	virtual void OnMessageReceivedN(Tizen::Io::RemoteMessagePort* pRemoteMessagePort, Tizen::Base::Collection::IMap* pMessage);
	void SubscribeNotifications(int userId);
	void UnsubscribeNotifications(int userId);

	void SubscribeReadEvents(IReadEventListener *readEventListener);
	void UnsubscribeReadEvents();
private:
	Tizen::Io::LocalMessagePort* pLocalMessagePort;
	Tizen::Io::RemoteMessagePort* pRemoteMessagePort;
	Tizen::App::AppId appId;

	IReadEventListener *_readEventListener;
};

#endif /* VKUSERVICEPROXY_H_ */
