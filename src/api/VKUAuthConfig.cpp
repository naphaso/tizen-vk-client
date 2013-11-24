/*
 * VKUAuthConfig.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: wolong
 */

#include "VKUAuthConfig.h"

#include <FIo.h>

#include "VKU.h"
#include "ObjectCounter.h"

using namespace Tizen::Io;
using namespace Tizen::Base;

String *VKUAuthConfig::accessTokenValue = null;
int VKUAuthConfig::expiresInValue = 0;
int VKUAuthConfig::userIdValue = 0;

VKUAuthConfig::VKUAuthConfig() {
	CONSTRUCT(L"VKUAuthConfig");
}

VKUAuthConfig::~VKUAuthConfig() {
	DESTRUCT(L"VKUAuthConfig");
}


bool VKUAuthConfig::IsExists() {
	String regPath(VKUApp::GetInstance()->GetAppDataPath() + L"auth.ini");
	return File::IsFileExist(regPath);
}

void VKUAuthConfig::Delete() {
	String regPath(VKUApp::GetInstance()->GetAppDataPath() + L"auth.ini");
	File::Remove(regPath);
}

void VKUAuthConfig::Replace(const String &accessToken, const String &expiresIn, const String userId) {
	if(IsExists()) {
		Delete();
	}

	String regPath(VKUApp::GetInstance()->GetAppDataPath() + L"auth.ini");

	String authSection(L"auth");
	Registry reg;
	reg.Construct(regPath, true);
	reg.AddSection(authSection);
	if(accessTokenValue != null) {
		delete accessTokenValue;
	}
	accessTokenValue = new String(accessToken);
	reg.AddValue(authSection, L"access_token", accessToken);
	Integer::Parse(expiresIn, expiresInValue);
	reg.AddValue(authSection, L"expires_in", expiresInValue);
	Integer::Parse(userId, userIdValue);
	reg.AddValue(authSection, L"user_id", userIdValue);
	reg.Flush();
}

void VKUAuthConfig::Read() {
	String regPath(VKUApp::GetInstance()->GetAppDataPath() + L"auth.ini");
	String authSection(L"auth");
	Registry reg;
	reg.Construct(regPath, false);
	if(accessTokenValue != null) {
		delete accessTokenValue;
	}
	accessTokenValue = new String();
	reg.GetValue(authSection, "access_token", *accessTokenValue);
	reg.GetValue(authSection, "expires_in", expiresInValue);
	reg.GetValue(authSection, "user_id", userIdValue);
}

String *VKUAuthConfig::GetAccessToken() {
	return accessTokenValue;
}

int VKUAuthConfig::GetExpiresIn() {
	return expiresInValue;
}

int VKUAuthConfig::GetUserId() {
	return userIdValue;
}

