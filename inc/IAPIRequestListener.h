#ifndef I_API_REQUEST_LISTENER_H
#define I_API_REQUEST_LISTENER_H

#include <FBase.h>
#include <FWebJson.h>

class IAPIRequestListener : public Tizen::Base::Object {
private:
	Tizen::Base::Collection::ArrayList pendingRequests;
public:
	IAPIRequestListener();
	void AddPendingRequest(const Tizen::Base::UuId &requestId);
	void ProcessResponseN(const Tizen::Base::UuId &requestId, Tizen::Web::Json::JsonObject *object);
	virtual void OnResponseN(Tizen::Web::Json::JsonObject *object) = 0;
	virtual ~IAPIRequestListener();
};

#endif
