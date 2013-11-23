/*
 * GroupedUsers.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: Igor Glotov
 */

#include "GroupedUsers.h"
#include "ObjectCounter.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Json;

GroupedUsers::GroupedUsers() {
	CONSTRUCT(L"GroupedUsers");
	_pUserGroups = null;
	_filteredGroups = null;
}

GroupedUsers::~GroupedUsers() {
	DESTRUCT(L"GroupedUsers");
	if (_pUserGroups)
		delete _pUserGroups;
	if(_filteredGroups)
		delete _filteredGroups;
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
	ArrayList *targetGroups = _filteredGroups != null ? _filteredGroups : _pUserGroups;

	if (targetGroups == null)
		return 0;

	return targetGroups->GetCount();
}

Tizen::Base::String GroupedUsers::GetGroupName(int index) {
	ArrayList *targetGroups = _filteredGroups != null ? _filteredGroups : _pUserGroups;

	if (targetGroups == null)
		return L"";

	UserGroup * pGroup = dynamic_cast<UserGroup *>(targetGroups->GetAt(index));
	return pGroup->GetGroupName();
}

// user operations
result GroupedUsers::GetUserFromGroup(int group, int index, JsonObject *& obj) {
	ArrayList *targetGroups = _filteredGroups != null ? _filteredGroups : _pUserGroups;

	if (targetGroups == null)
		return null;

	UserGroup * pGroup = dynamic_cast<UserGroup *>(targetGroups->GetAt(group));

	return pGroup->GetUserAt(index, obj);
}

int GroupedUsers::GetUserCountInGroup(int group) {
	ArrayList *targetGroups = _filteredGroups != null ? _filteredGroups : _pUserGroups;

	if (targetGroups == null)
		return 0;

	UserGroup * pGroup = dynamic_cast<UserGroup *>(targetGroups->GetAt(group));

	return pGroup->GetUserCount();
}

int GroupedUsers::GetUserCount() {
	ArrayList *targetGroups = _filteredGroups != null ? _filteredGroups : _pUserGroups;


	if (targetGroups == null)
		return 0;

	int sum = 0;
	for (int i=0; i < targetGroups->GetCount(); i++) {
		UserGroup * pGroup = dynamic_cast<UserGroup *>(targetGroups->GetAt(i));
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

void GroupedUsers::SetFilter(const String &filter) {
	ResetFilter();

	_filteredGroups = new ArrayList();
	_filteredGroups->Construct();

	for (int i=0; i < _pUserGroups->GetCount(); i++) {
		UserGroup *group = dynamic_cast<UserGroup *>(_pUserGroups->GetAt(i));
		UserGroup *filteredGroup = group->MatchFilter(filter);
		if(filteredGroup != null) {
			_filteredGroups->Add(filteredGroup);
		}
	}

}

void GroupedUsers::ResetFilter() {
	if(_filteredGroups != null) {
		delete _filteredGroups;
		_filteredGroups = null;
	}
}
