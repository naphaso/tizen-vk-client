/*
 * VKUJsonObject.cpp
 *
 *  Created on: Nov 1, 2013
 *      Author: wolong
 */

#include "VKUJsonObject.h"

using namespace Tizen::Base;
using namespace Tizen::Web::Json;

VKUJsonObject *VKUJsonObject::parseN(ByteBuffer *buffer) {
	result r;
	IJsonValue *value = JsonParser::ParseN(*buffer);
	r = GetLastResult();

	if(r != E_SUCCESS || value == null) {
		return null;
	}

	if(value->GetType() != JSON_TYPE_OBJECT) {
		delete value;
		return null;
	}

	return new VKUJsonObject(value, true);
}

VKUJsonObject::VKUJsonObject(JsonObject *jsonObject, bool ownership) {
	this->ownership = ownership;
	this->jsonObject = jsonObject;
}

VKUJsonObject::VKUJsonObject(IJsonValue *jsonValue, bool ownership) {
	this->ownership = ownership;
	this->jsonObject = static_cast<JsonObject *>(jsonValue);
}

VKUJsonObject::~VKUJsonObject() {
	if(ownership) {
		delete jsonObject;
	}
}

String *VKUJsonObject::getString(const String &key) {
	result r;
	IJsonValue *value;
	r = jsonObject->GetValue(&key, value);

	if(r != E_SUCCESS) {
		return null;
	}

	if(value->GetType() != JSON_TYPE_STRING) {
		delete value;
		return null;
	}

	return static_cast<JsonString *>(value);
}

VKUJsonObject *VKUJsonObject::getObject(const String &key) {
	result r;
	IJsonValue *value;
	r = jsonObject->GetValue(&key, value);

	if(r != E_SUCCESS) {
		return null;
	}

	if(value->GetType() != JSON_TYPE_OBJECT) {
		delete value;
		return null;
	}

	return new VKUJsonObject(static_cast<JsonObject *>(value));
}

VKUJsonArray *VKUJsonObject::getArray(const String &key) {
	result r;
	IJsonValue *value;
	r = jsonObject->GetValue(&key, value);

	if(r != E_SUCCESS) {
		return null;
	}

	if(value->GetType() != JSON_TYPE_ARRAY) {
		delete value;
		return null;
	}

	return new VKUJsonArray(static_cast<JsonArray *>(value));
}

int VKUJsonObject::getInt(const String &key) {
	result r;
	IJsonValue *value;
	r = jsonObject->GetValue(&key, value);

	if(r != E_SUCCESS) {
		return null;
	}

	if(value->GetType() != JSON_TYPE_NUMBER) {
		delete value;
		return null;
	}

	int intValue = static_cast<JsonNumber *>(value)->ToInt();

	delete value;

	return intValue;
}

