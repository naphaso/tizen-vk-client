/*
 * SampleRequest.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: wolong
 */

#include "SampleRequest.h"

using namespace Tizen::Web::Json;

SampleRequest::SampleRequest() {
	// TODO Auto-generated constructor stub

}

SampleRequest::~SampleRequest() {
	// TODO Auto-generated destructor stub
}

void SampleRequest::OnResponseN(Tizen::Web::Json::JsonObject *json) {
	char data[10000];
	JsonWriter::Compose(json, data, 10000);
	AppLog("response received!: %s", data);
}
