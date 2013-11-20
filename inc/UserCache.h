/*
 * UserCache.h
 *
 *  Created on: Nov 21, 2013
 *      Author: Igor Glotov
 */

#ifndef USERCACHE_H_
#define USERCACHE_H_

#include <FBase.h>
#include <FWeb.h>

class UserCache {
public:

	UserCache();
	virtual ~UserCache();

	static void Put(int userId, Tizen::Web::Json::JsonObject * userJson);
	static Tizen::Web::Json::JsonObject * Get(const int userId);

	static Tizen::Base::Collection::HashMap _usersCache;
};

#endif /* USERCACHE_H_ */
