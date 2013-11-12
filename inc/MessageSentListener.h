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
	void SetUserId(Tizen::Base::String userId);

private:
	Tizen::Ui::Controls::TableView * pTableView;
	VKUMessagesListItemProvider * pProvider;
	Tizen::Base::String userIdStr;
};

#endif /* MESSAGESENTLISTENER_H_ */
