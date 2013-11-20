/*
 * IAPIRequestListener.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: wolong
 */


#include "IAPIRequestListener.h"
#include "VKUApi.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Json;

IAPIRequestListener::IAPIRequestListener() : pendingRequests(SingleObjectDeleter) {
	pendingRequests.Construct();
}

void IAPIRequestListener::AddPendingRequest(const UuId &requestId) {
	pendingRequests.Add(new UuId(requestId));
}

IAPIRequestListener::~IAPIRequestListener() {
    IEnumerator* enumerator = pendingRequests.GetEnumeratorN();
    while (enumerator->MoveNext() == E_SUCCESS) {
        VKUApi::GetInstance().DropRequest(*static_cast<UuId *>(enumerator->GetCurrent()));
    }

    delete enumerator;
}

void IAPIRequestListener::ProcessResponseN(const UuId &requestId, JsonObject *object, RequestId targetRequestId) {
	result r;
	r = pendingRequests.Remove(requestId);
	if(r == E_SUCCESS) {
		AppLog("successful remove pending request");
		OnResponseN(targetRequestId, object);
	} else {
		AppLog("failed remove pending request");
	}
}

void IAPIRequestListener::ProcessError(const UuId &requestId, result r) {
	if(pendingRequests.Remove(requestId) == E_SUCCESS) {
		AppLog("successful remove pending request");
		OnError(r);
	} else {
		AppLog("failed remove pending request");
	}
}
