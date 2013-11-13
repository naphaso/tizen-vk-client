/*
 * MessageSentListener.h
 *
 *  Created on: Nov 10, 2013
 *      Author: igorglotov
 */

#ifndef MESSAGESENTLISTENER_H_
#define MESSAGESENTLISTENER_H_

#include "IAPIRequestListener.h"
#include "VKUMessagesListItemProvider.h"

#include <FUi.h>
#include <FWebJson.h>

class MessageSentListener: public IAPIRequestListener {
public:
	MessageSentListener(Tizen::Ui::Controls::TableView * apTableView,
			VKUMessagesListItemProvider * pProvider);
	virtual ~MessageSentListener();

	// IAPIRequestListener
	virtual void OnResponseN(Tizen::Web::Json::JsonObject *object);
	void SetUserJson(Tizen::Web::Json::JsonObject* userId);

private:
	Tizen::Ui::Controls::TableView * pTableView;
	VKUMessagesListItemProvider * pProvider;
	Tizen::Web::Json::JsonObject* pUserJson = null;
};

#endif /* MESSAGESENTLISTENER_H_ */
