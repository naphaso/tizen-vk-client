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
	AppLog("Getting JSON_TYPE_NUMBER");

	if (object.GetValue(&key, value) == E_SUCCESS) {
		AppLog("GetValue E_SUCCESS");

		if (value->GetType() == JSON_TYPE_NUMBER) {
			AppLog("Static casting JSON_TYPE_NUMBER");

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

result JsonParseUtils::GetObject(const JsonObject *object, const String &key, JsonObject *&result) {
	IJsonValue *value;
	if(object->GetValue(&key, value) == E_SUCCESS) {
		if(value->GetType() == JSON_TYPE_OBJECT) {
			result = static_cast<JsonObject *>(value);
			return E_SUCCESS;
		} else {
			return E_PARSING_FAILED;
		}
	} else {
		return E_PARSING_FAILED;
	}
}

result JsonParseUtils::GetArray(const JsonObject *object, const String &key, JsonArray *&result) {
	IJsonValue *value;
	if(object->GetValue(&key, value) == E_SUCCESS) {
		if(value->GetType() == JSON_TYPE_ARRAY) {
			result = static_cast<JsonArray *>(value);
			return E_SUCCESS;
		} else {
			return E_PARSING_FAILED;
		}
	} else {
		return E_PARSING_FAILED;
	}
}

result JsonParseUtils::GetObject(const JsonArray *array, const int index, JsonObject *&result) {
	IJsonValue *value;
	if(array->GetAt(index, value) == E_SUCCESS) {
		if(value->GetType() == JSON_TYPE_OBJECT) {
			result = static_cast<JsonObject *>(value);
			return E_SUCCESS;
		} else {
			return E_PARSING_FAILED;
		}
	} else {
		return E_PARSING_FAILED;
	}
}

result JsonParseUtils::GetDialogPeerId(
		const Tizen::Web::Json::JsonObject * dialog,
		int & value) {
	int chatId;
	result r = JsonParseUtils::GetInteger(*dialog, L"chat_id", chatId);

	if (r == E_SUCCESS) {
		value = chatId + 2000000000;
		return r;
	}

	int userId;
	r = JsonParseUtils::GetInteger(*dialog, L"user_id", userId);

	if (r == E_SUCCESS) {
		value = userId;
		return r;
	}

	return E_PARSING_FAILED;
}
