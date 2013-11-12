/*
 * MessageSentListener.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: igorglotov
 */

#include "MessageSentListener.h"

using namespace Tizen::Base;

MessageSentListener::MessageSentListener(Tizen::Ui::Controls::TableView * apTableView,
		VKUMessagesListItemProvider * apProvider) {
	pTableView = apTableView;
	pProvider = apProvider;

}

void MessageSentListener::SetUserId(String userId) {
	userIdStr = userId;
}

MessageSentListener::~MessageSentListener() {
	// TODO Auto-generated destructor stub
}

void MessageSentListener::OnResponseN(Tizen::Web::Json::JsonObject *object) {
	TryReturnVoid(pProvider != null, "MessageSentListener: Provider cannot be null");
	TryReturnVoid(userIdStr.GetLength() != 0, "MessageSentListener: UserId is empty");

	pProvider->RequestData(userIdStr);
	delete object;
}
