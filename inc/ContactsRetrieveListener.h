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

#include "IAPIRequestListener.h"

class ContactsRetrieveListener: public IAPIRequestListener {
public:
	ContactsRetrieveListener(Tizen::Ui::Controls::GroupedTableView * apTableView,
			Tizen::Ui::Controls::IGroupedTableViewItemProvider * apProvider);
	virtual ~ContactsRetrieveListener();
	void OnResponseN(Tizen::Web::Json::JsonObject *object);

private:
	Tizen::Ui::Controls::IGroupedTableViewItemProvider * pProvider;
	Tizen::Ui::Controls::GroupedTableView * pGroupedTableView;
};

#endif /* CONTACTSRETRIEVELISTENER_H_ */
