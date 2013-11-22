/*
 * UserGroup.h
 *
 *  Created on: Nov 21, 2013
 *      Author: Igor Glotov
 */

#ifndef USERGROUP_H_
#define USERGROUP_H_

#include <FBase.h>
#include <FWebJson.h>

class UserGroup: public Tizen::Base::Object {
public:
	UserGroup();
	virtual ~UserGroup();

	result Construct(const Tizen::Base::String & groupName, const Tizen::Web::Json::JsonArray * usersArray);
	result Construct(const Tizen::Base::String & groupName);

	void AddUserArray(const Tizen::Web::Json::JsonArray * usersArray);
	void SetGroupName(const Tizen::Base::String & name);

	Tizen::Base::String GetGroupName();
	result GetUserAt(int index, Tizen::Web::Json::JsonObject *& json);
	int GetUserCount();

	UserGroup *MatchFilter(const Tizen::Base::String &filter);
private:
	Tizen::Base::String * _pGroupName;
	Tizen::Web::Json::JsonArray *_pUserList;
};

#endif /* USERGROUP_H_ */
