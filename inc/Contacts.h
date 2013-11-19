/*
 * Contacts.h
 *
 *  Created on: Nov 17, 2013
 *      Author: wolong
 */

#ifndef CONTACTS_H_
#define CONTACTS_H_

#include <FBase.h>
#include <FSocial.h>
#include <FIo.h>
#include <FWebJson.h>

class Contacts;

#include "IAPIRequestListener.h"
#include "Requests.h"

class Contacts : public IAPIRequestListener {
public:
	result Sync();
	Contacts();
	virtual ~Contacts();

	virtual void OnResponseN(Tizen::Web::Json::JsonObject *object);
private:
	Tizen::Social::AccountId accountId;
	Tizen::Social::AddressbookId addressbookId;

	bool IsConfigExists();
	void ReadConfig();
	void InitConfig();
	void WriteConfig();

	Tizen::Social::Contact *GetExistingContact(Tizen::Base::Collection::IList *contacts, const Tizen::Base::String &pageUrl);
};

#endif /* CONTACTS_H_ */
