#ifndef I_API_REQUEST_LISTENER_H
#define I_API_REQUEST_LISTENER_H

#include <FBase.h>
#include <FWebJson.h>

class IAPIRequestListener : public Tizen::Base::Object {
public:
	virtual void OnResponseN(Tizen::Web::Json::JsonObject *object) = 0;
};

#endif
