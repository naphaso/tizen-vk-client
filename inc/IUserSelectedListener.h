/*
 * IUserSelectedListener.h
 *
 *  Created on: Nov 21, 2013
 *      Author: Igor Glotov
 */

#ifndef IUSERSELECTEDLISTENER_H_
#define IUSERSELECTEDLISTENER_H_

#include <FWebJson.h>

class IUserSelectedListener:
	public Tizen::Base::Object {
public:
	IUserSelectedListener();
	virtual ~IUserSelectedListener();

	virtual void OnUserSelected(const Tizen::Web::Json::JsonObject * userJson) = 0;
};

#endif /* IUSERSELECTEDLISTENER_H_ */
