/*
 * JsonParseUtils.cpp
 *
 *  Created on: Nov 12, 2013
 *      Author: igorglotov
 */

#include "JsonParseUtils.h"

using namespace Tizen::Base;
using namespace Tizen::Web::Json;

JsonParseUtils::JsonParseUtils() {
	// TODO Auto-generated constructor stub

}

JsonParseUtils::~JsonParseUtils() {
	// TODO Auto-generated destructor stub
}

result JsonParseUtils::GetString(const JsonObject & object, const String & key,
		String & resVal) {
	result r = E_SUCCESS;

	IJsonValue * value;
	if (object.GetValue(&key, value) == E_SUCCESS) {
		if (value->GetType() == JSON_TYPE_STRING) {
			resVal = *static_cast<JsonString *>(value);
		} else {
			r = E_PARSING_FAILED;
		}
	} else {
		r = E_PARSING_FAILED;
	}

	return r;
}

result JsonParseUtils::GetInteger(const JsonObject & object, const String & key,
		int & resVal) {
	result r = E_SUCCESS;

	IJsonValue * value;
	if (object.GetValue(&key, value) == E_SUCCESS) {
		if (value->GetType() == JSON_TYPE_NUMBER) {
			JsonNumber jsonValNum = *static_cast<JsonNumber *>(value);
			resVal = jsonValNum.ToInt();
		} else {
			r = E_PARSING_FAILED;
		}
	} else {
		r = E_PARSING_FAILED;
	}

	return r;
}
