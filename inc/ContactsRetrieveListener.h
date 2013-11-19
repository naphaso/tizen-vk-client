/*
 * ContactsRetrieveListener.h
 *
 *  Created on: Nov 8, 2013
 *      Author: igorglotov
 */

#ifndef CONTACTSRETRIEVELISTENER_H_
#define CONTACTSRETRIEVELISTENER_H_

#include <FUi.h>
#include <FBase.h>
#include <FWebJson.h>

class ContactsRetrieveListener;

#include "ContactsTableProvider.h"
#include "IAPIRequestListener.h"
#include "Requests.h"

class ContactsRetrieveListener: public IAPIRequestListener {
public:
	ContactsRetrieveListener(Tizen::Ui::Controls::GroupedTableView * apTableView,
			ContactsTableProvider * apProvider);
	virtual ~ContactsRetrieveListener();
	virtual void OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object);

private:
	ContactsTableProvider * pProvider;
	Tizen::Ui::Controls::GroupedTableView * pGroupedTableView;
};

#endif /* CONTACTSRETRIEVELISTENER_H_ */
