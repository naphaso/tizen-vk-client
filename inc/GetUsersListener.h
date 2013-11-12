/*
 * GetUsersListener.h
 *
 *  Created on: Nov 11, 2013
 *      Author: igorglotov
 */

#ifndef GETUSERSLISTENER_H_
#define GETUSERSLISTENER_H_

#include "IAPIRequestListener.h"

class GetUsersListener:
	public IAPIRequestListener {
public:
	GetUsersListener();
	virtual ~GetUsersListener();

	// request
	virtual void OnResponseN(Tizen::Web::Json::JsonObject *object);
};

#endif /* GETUSERSLISTENER_H_ */
