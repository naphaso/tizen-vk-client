/*
 * UserGroup.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: Igor Glotov
 */

#include "UserGroup.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Json;

UserGroup::UserGroup() {
	_pGroupName = null;

	_pUserList = new JsonArray();
	_pUserList->Construct();
}

// FIXME: leaks
UserGroup::~UserGroup() {
//	if (_pGroupName)
//		delete _pGroupName;
//	delete _pUserList;
}

result UserGroup::Construct(const Tizen::Base::String & groupName) {
	result r = E_SUCCESS;

	_pGroupName = new String(groupName);
	return r;
}

result UserGroup::Construct(const Tizen::Base::String & groupName, const JsonArray * usersArray) {
	result r = E_SUCCESS;
	AppLog("Adding %d items to array, named %ls", usersArray->GetCount(), groupName.GetPointer());

	_pGroupName = new String(groupName);
	delete _pUserList;
	_pUserList = usersArray->CloneN();
//	_pUserList->AddItems(*usersArray);
	return r;
}


void UserGroup::AddUserArray(const JsonArray * usersArray) {
	AppLog("Adding %d items to array", usersArray->GetCount());

	_pUserList->AddItems(*usersArray);
}

void UserGroup::SetGroupName(const String & name) {
	_pGroupName = new String(name);
}

String UserGroup::GetGroupName() {
	if (_pGroupName == null) {
		return L"invalid group";
	}

	return *_pGroupName;
}

result UserGroup::GetUserAt(int index, JsonObject *& json) {
	result r = E_SUCCESS;
	if (_pUserList == null)
		return E_OUT_OF_RANGE;

	IJsonValue *value;
	_pUserList->GetAt(index, value);
	JsonObject * pUser = dynamic_cast<JsonObject *>(value);
	r = GetLastResult();

	json = pUser->CloneN();

	return r;
}

int UserGroup::GetUserCount() {
	if (_pUserList == null)
		return 0;

	return _pUserList->GetCount();
}
