/*
 * VKUConfig.h
 *
 *  Created on: Nov 2, 2013
 *      Author: wolong
 */

#ifndef VKUCONFIG_H_
#define VKUCONFIG_H_

#define VKU_APP_ID L"3966496"
#define VKU_APP_PERMISSIONS L"notify,friends,photos,audio,video,docs,notes,pages,status,wall,groups,messages,notifications,stats,ads,offline,questions,offers"
#define VKU_REDIRECT_URL L"https://oauth.vk.com/blank.html"
#define VKU_DISPLAY_TYPE "touch"
#define VKU_RESPONSE_TYPE "token"

#define VKU_LOGIN_URL L"https://oauth.vk.com/authorize?" \
	L"client_id=" VKU_APP_ID            \
	L"&scope=" VKU_APP_PERMISSIONS      \
	L"&redirect_uri=" VKU_REDIRECT_URL  \
	L"&display=" VKU_DISPLAY_TYPE       \
	"&response_type=" VKU_RESPONSE_TYPE

#define VKU_API_VERSION L"5.2"


#endif /* VKUCONFIG_H_ */
