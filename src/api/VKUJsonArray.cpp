/*
 * VKUJsonArray.cpp
 *
 *  Created on: Nov 1, 2013
 *      Author: wolong
 */

#include "VKUJsonArray.h"
#include "ObjectCounter.h"

using namespace Tizen::Web::Json;
using namespace Tizen::Base;

VKUJsonArray::VKUJsonArray(JsonArray *jsonArray, bool ownership) {
	CONSTRUCT(L"VKUJsonArray");
	this->ownership = ownership;
	this->jsonArray = jsonArray;
}

VKUJsonArray::VKUJsonArray(IJsonValue *jsonValue, bool ownership) {
	DESTRUCT(L"VKUJsonArray");
	this->ownership = ownership;
	this->jsonArray = static_cast<JsonArray *>(jsonValue);
}

VKUJsonArray::~VKUJsonArray() {
	if(ownership) {
		delete jsonArray;
	}
}

int VKUJsonArray::length() {
	return jsonArray->GetCount();
}

VKUJsonObject *VKUJsonArray::getObject(int index) {
	result r;
	IJsonValue *value;
	r = jsonArray->GetAt(index, value);

	if(r != E_SUCCESS) {
		return null;
	}

	if(value->GetType() != JSON_TYPE_OBJECT) {
		delete value;
		return null;
	}

	return new VKUJsonObject(static_cast<JsonObject *>(value));
}

int VKUJsonArray::getInt(int index) {
	result r;
	IJsonValue *value;
	r = jsonArray->GetAt(index, value);

	if(r != E_SUCCESS) {
		return null;
	}

	if(value->GetType() != JSON_TYPE_OBJECT) {
		delete value;
		return null;
	}

	int intValue = static_cast<JsonNumber *>(value)->ToInt();

	delete value;

	return intValue;
}

String *VKUJsonArray::getString(int index) {
	result r;
	IJsonValue *value;
	r = jsonArray->GetAt(index, value);

	if(r != E_SUCCESS) {
		return null;
	}

	if(value->GetType() != JSON_TYPE_STRING) {
		delete value;
		return null;
	}

	return static_cast<JsonString *>(value);
}
