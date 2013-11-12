/*
 * JsonParseUtils.h
 *
 *  Created on: Nov 12, 2013
 *      Author: igorglotov
 */

#ifndef JSONPARSEUTILS_H_
#define JSONPARSEUTILS_H_

#include <FUi.h>
#include <FWebJson.h>
#include <FBase.h>

class JsonParseUtils {
public:
	JsonParseUtils();
	virtual ~JsonParseUtils();

	static result GetString(
			const Tizen::Web::Json::JsonObject & object,
			const Tizen::Base::String & key,
			Tizen::Base::String & value);

	static result GetInteger(
			const Tizen::Web::Json::JsonObject & object,
			const Tizen::Base::String & key,
			int & value);
};

#endif /* JSONPARSEUTILS_H_ */
