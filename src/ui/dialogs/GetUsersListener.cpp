/*
 * GetUsersListener.cpp
 *
 *  Created on: Nov 11, 2013
 *      Author: igorglotov
 */

#include "GetUsersListener.h"
#include "ObjectCounter.h"

GetUsersListener::GetUsersListener() {
	CONSTRUCT(L"GetUsersListener");

}

GetUsersListener::~GetUsersListener() {
	DESTRUCT(L"GetUsersListener");
}

void GetUsersListener::OnResponseN(Tizen::Web::Json::JsonObject *object) {

}
