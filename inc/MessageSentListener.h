/*
 * MessageSentListener.h
 *
 *  Created on: Nov 10, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGESENTLISTENER_H_
#define MESSAGESENTLISTENER_H_


#include <FUi.h>
#include <FWebJson.h>

class MessageSentListener;
#define MESSAGE_SEND_REQUEST 101

#include "IAPIRequestListener.h"
#include "VKUMessagesListItemProvider.h"
#include "Requests.h"

class MessageSentListener: public IAPIRequestListener {
public:
	MessageSentListener();
	virtual ~MessageSentListener();

	result Construct(
			Tizen::Ui::Controls::TableView *tableView,
			VKUMessagesListItemProvider *provider,
			Tizen::Web::Json::JsonObject *userJson);

	// IAPIRequestListener
	virtual void OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *response);


	void SetUserJson(Tizen::Web::Json::JsonObject* userId);

private:
	Tizen::Ui::Controls::TableView * _tableView;
	VKUMessagesListItemProvider * _provider;
	Tizen::Web::Json::JsonObject* _userJson;
};

#endif /* MESSAGESENTLISTENER_H_ */
