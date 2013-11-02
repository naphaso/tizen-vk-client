/*
 * VKUJsonArray.h
 *
 *  Created on: Nov 1, 2013
 *      Author: wolong
 */

#ifndef VKUJSONARRAY_H_
#define VKUJSONARRAY_H_

#include <FBase.h>
#include <FNet.h>
#include <FApp.h>
#include <FWebJson.h>

class VKUJsonArray;

#include "VKUJsonObject.h"

class VKUJsonArray {
public:
	VKUJsonArray(Tizen::Web::Json::JsonArray *jsonArray, bool ownership = false);
	VKUJsonArray(Tizen::Web::Json::IJsonValue *jsonValue, bool ownership = false);
	virtual ~VKUJsonArray();

	int length();
	VKUJsonObject *getObject(int index);
	Tizen::Base::String *getString(int index);
	int getInt(int index);
private:
	bool ownership;
	Tizen::Web::Json::JsonArray *jsonArray;
};

#endif /* VKUJSONARRAY_H_ */
