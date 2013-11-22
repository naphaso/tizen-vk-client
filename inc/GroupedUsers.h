/*
 * GroupedUsers.h
 *
 *  Created on: Nov 21, 2013
 *      Author: Igor Glotov
 */

#ifndef GROUPEDUSERS_H_
#define GROUPEDUSERS_H_

#include <FWebJson.h>
#include <FBase.h>

#include "UserGroup.h"

class GroupedUsers: public Tizen::Base::Object {
public:
	GroupedUsers();
	virtual ~GroupedUsers();

	result Construct();

	// group operations
	int GetGroupCount();
	Tizen::Base::String GetGroupName(int index);

	// user operations
	result GetUserFromGroup(int group, int index, Tizen::Web::Json::JsonObject *& obj);
	int GetUserCountInGroup(int group);
	int GetUserCount();

	result AddUserGroup(UserGroup & userGroup);
	result AddUserGroup(const Tizen::Base::String & name, Tizen::Web::Json::JsonArray * jsonArray);

	void SetFilter(const Tizen::Base::String &filter);
	void ResetFilter();
private:
	Tizen::Base::Collection::ArrayList * _pUserGroups;
	Tizen::Base::Collection::ArrayList * _filteredGroups;
};

#endif /* GROUPEDUSERS_H_ */
