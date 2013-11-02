/*
 * VKUUtils.cpp
 *
 *  Created on: Nov 2, 2013
 *      Author: wolong
 */

#include "VKUUtils.h"

using namespace Tizen::Base::Collection;
using namespace Tizen::Base::Utility;
using namespace Tizen::Base;

IMap *ParseQueryStringN(const String &str) {
	HashMap *map = new HashMap(SingleObjectDeleter);

	map->Construct();

	StringTokenizer paramTokens(str, L"&");
	while (paramTokens.HasMoreTokens()) {
		String paramToken;
		paramTokens.GetNextToken(paramToken);

		StringTokenizer keyValueTokens(paramToken, L"=");

		if(keyValueTokens.GetTokenCount() == 2) { // TODO: corrent check if value contains '=' character
			String key, value;
			keyValueTokens.GetNextToken(key);
			keyValueTokens.GetNextToken(value);
			map->Add(new String(key), new String(value));
		}
	}

	return map;
}
