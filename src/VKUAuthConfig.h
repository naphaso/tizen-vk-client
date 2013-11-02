/*
 * VKUAuthConfig.h
 *
 *  Created on: Nov 3, 2013
 *      Author: wolong
 */

#ifndef VKUAUTHCONFIG_H_
#define VKUAUTHCONFIG_H_

#include <FBase.h>

class VKUAuthConfig {
private:
	VKUAuthConfig();
public:
	static bool IsExists();
	static void Delete();
	static void Replace(const Tizen::Base::String &accessToken, const Tizen::Base::String &expiresIn, const Tizen::Base::String userId);
	static void Read();


	static Tizen::Base::String *GetAccessToken();
	static int GetExpiresIn();
	static int GetUserId();

	virtual ~VKUAuthConfig();

private:
	static Tizen::Base::String *accessTokenValue;
	static int expiresInValue;
	static int userIdValue;
};

#endif /* VKUAUTHCONFIG_H_ */
