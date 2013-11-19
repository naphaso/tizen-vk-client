/*
 * VKUJsonObject.h
 *
 *  Created on: Nov 1, 2013
 *      Author: wolong
 */

#ifndef VKUJSONOBJECT_H_
#define VKUJSONOBJECT_H_

#include <FBase.h>
#include <FNet.h>
#include <FApp.h>
#include <FWebJson.h>

class VKUJsonObject;

#include "VKUJsonArray.h"

class VKUJsonObject {
public:
	static VKUJsonObject *parseN(Tizen::Base::ByteBuffer *byteBuffer);

	VKUJsonObject(Tizen::Web::Json::JsonObject *jsonObject, bool ownership = false);
	VKUJsonObject(Tizen::Web::Json::IJsonValue *jsonValue, bool ownership = false);

	Tizen::Base::String *getString(const Tizen::Base::String &key);
	VKUJsonObject *getObject(const Tizen::Base::String &key);
	VKUJsonArray *getArray(const Tizen::Base::String &key);
	int getInt(const Tizen::Base::String &key);

	virtual ~VKUJsonObject();
private:
	bool ownership;
	Tizen::Web::Json::JsonObject *jsonObject;
};

#endif /* VKUJSONOBJECT_H_ */
