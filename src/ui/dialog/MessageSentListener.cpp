/*
 * MessageSentListener.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: igorglotov
 */

#include "MessageSentListener.h"
#include "ObjectCounter.h"

using namespace Tizen::Base;
using namespace Tizen::Web::Json;
using namespace Tizen::Ui::Controls;

MessageSentListener::MessageSentListener() {
	CONSTRUCT(L"MessageSentListener");
}

result MessageSentListener::Construct(TableView *tableView, VKUMessagesListItemProvider * provider, JsonObject *userJson) {
	_tableView = tableView;
	_provider = provider;
	_userJson = userJson;
	return E_SUCCESS;
}

MessageSentListener::~MessageSentListener() {
	DESTRUCT(L"MessageSentListener");
}

void MessageSentListener::OnResponseN(RequestId requestId, JsonObject *response) {
	if(requestId == REQUEST_SEND_MESSAGE) {
		TryReturnVoid(_provider != null, "MessageSentListener: Provider cannot be null");
		TryReturnVoid(_userJson != null, "MessageSentListener: pUserJson is empty");

		//_provider->RequestUpdateHistory();
	}

	delete response;
}
