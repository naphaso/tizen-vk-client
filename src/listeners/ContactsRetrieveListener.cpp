/*
 * ContactsRetrieveListener.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: igorglotov
 */

#include "ContactsRetrieveListener.h"

using namespace Tizen::Ui::Controls;
using namespace Tizen::Web::Json;

ContactsRetrieveListener::ContactsRetrieveListener(GroupedTableView * apTableView, ContactsTableProvider * apProvider) {
	pGroupedTableView = apTableView;
	pProvider = apProvider;
}

ContactsRetrieveListener::~ContactsRetrieveListener() {

}

void ContactsRetrieveListener::OnResponseN(JsonObject *object) {
	result r = E_SUCCESS;
	AppLog("ContactsRetrieveListener::OnResponseN");
	pGroupedTableView->UpdateTableView();
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult() , "Failed pGroupedTableView->UpdateTableView");

	pGroupedTableView->RequestRedraw(true);
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult() , "Failed pGroupedTableView->RequestRedraw");

	SetLastResult(r);
	return;
CATCH:
	AppLogException("$${Function:OnResponseN} is failed.", GetErrorMessage(r));
	SetLastResult(r);
}
