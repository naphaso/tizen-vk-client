/*
 * GroupedUsers.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: Igor Glotov
 */

#include "GroupedUsers.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Json;

GroupedUsers::GroupedUsers() {
	_pUserGroups = null;
}

GroupedUsers::~GroupedUsers() {
	if (_pUserGroups)
		delete _pUserGroups;
}

result GroupedUsers::Construct() {
	// TODO: parse json
	result r = E_SUCCESS;

	_pUserGroups = new ArrayList();
	_pUserGroups->Construct();

	return r;
}

// group operations
int GroupedUsers::GetGroupCount() {
	if (_pUserGroups == null)
		return 0;

	return _pUserGroups->GetCount();
}

Tizen::Base::String GroupedUsers::GetGroupName(int index) {
	if (_pUserGroups == null)
		return L"";

	UserGroup * pGroup = dynamic_cast<UserGroup *>(_pUserGroups->GetAt(index));
	return pGroup->GetGroupName();
}

// user operations
result GroupedUsers::GetUserFromGroup(int group, int index, JsonObject *& obj) {
	if (_pUserGroups == null)
		return null;

	UserGroup * pGroup = dynamic_cast<UserGroup *>(_pUserGroups->GetAt(group));

	return pGroup->GetUserAt(index, obj);
}

int GroupedUsers::GetUserCountInGroup(int group) {
	if (_pUserGroups == null)
		return 0;

	UserGroup * pGroup = dynamic_cast<UserGroup *>(_pUserGroups->GetAt(group));

	return pGroup->GetUserCount();
}

int GroupedUsers::GetUserCount() {
	if (_pUserGroups == null)
		return 0;

	int sum = 0;
	for (int i=0; i < _pUserGroups->GetCount(); i++) {
		UserGroup * pGroup = dynamic_cast<UserGroup *>(_pUserGroups->GetAt(i));
		sum += pGroup->GetUserCount();
	}

	return sum;
}

result GroupedUsers::AddUserGroup(UserGroup & userGroup) {
	result r = E_SUCCESS;
	if (_pUserGroups == null) {
		AppLogException("GroupUsers is not constructed");
		r = E_INIT_FAILED;
		return r;
	}

	r = _pUserGroups->Add(new UserGroup(userGroup));
	return r;
}

result GroupedUsers::AddUserGroup(const Tizen::Base::String & name, Tizen::Web::Json::JsonArray * jsonArray) {
	result r = E_SUCCESS;
	if (_pUserGroups == null) {
		AppLogException("GroupUsers is not constructed");
		r = E_INIT_FAILED;
		return r;
	}

	if (name.GetLength() == 0 || jsonArray->GetCount() == 0)
		return r;

	UserGroup userGroup;
	userGroup.Construct(name, jsonArray);

	r = _pUserGroups->Add(new UserGroup(userGroup));
	return r;
}
