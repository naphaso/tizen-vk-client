/*
 * ContactsRetrieveListener.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: igorglotov
 */

#include "ContactsRetrieveListener.h"

using namespace Tizen::Ui::Controls;
using namespace Tizen::Web::Json;

ContactsRetrieveListener::ContactsRetrieveListener(GroupedTableView * apTableView, ITableViewItemProvider * apProvider) {
	pGroupedTableView = apTableView;
	pProvider = apProvider;
}

ContactsRetrieveListener::~ContactsRetrieveListener() {

}

void ContactsRetrieveListener::OnResponseN(JsonObject *object) {
	pProvider->SetUsersJson(object);

	pGroupedTableView->UpdateTableView();
	pGroupedTableView->RequestRedraw(true);
}
