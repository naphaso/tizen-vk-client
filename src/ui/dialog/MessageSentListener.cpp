/*
 * MessageSentListener.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: igorglotov
 */

#include "MessageSentListener.h"

using namespace Tizen::Base;
using namespace Tizen::Web::Json;

MessageSentListener::MessageSentListener(Tizen::Ui::Controls::TableView * apTableView,
		VKUMessagesListItemProvider * apProvider) {
	pTableView = apTableView;
	pProvider = apProvider;

}

void MessageSentListener::SetUserJson(JsonObject * userJson) {
	pUserJson = userJson;
}

MessageSentListener::~MessageSentListener() {
	// TODO Auto-generated destructor stub
}

void MessageSentListener::OnResponseN(JsonObject *object) {
	TryReturnVoid(pProvider != null, "MessageSentListener: Provider cannot be null");
	TryReturnVoid(pUserJson != null, "MessageSentListener: pUserJson is empty");

	pProvider->RequestData();
	delete object;
}
