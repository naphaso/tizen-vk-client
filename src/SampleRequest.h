/*
 * SampleRequest.h
 *
 *  Created on: Nov 3, 2013
 *      Author: wolong
 */

#ifndef SAMPLEREQUEST_H_
#define SAMPLEREQUEST_H_

#include "IAPIRequestListener.h"


class SampleRequest : public IAPIRequestListener {
public:
	virtual void OnResponseN(Tizen::Web::Json::JsonObject *json);
	SampleRequest();
	virtual ~SampleRequest();
};

#endif /* SAMPLEREQUEST_H_ */
