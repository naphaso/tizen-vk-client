/*
 * DialogHistoryListener.cpp
 *
 *  Created on: Nov 10, 2013
 *      Author: igorglotov
 */

#include "DialogHistoryListener.h"

using namespace Tizen::Ui::Controls;
using namespace Tizen::Web::Json;

DialogHistoryListener::DialogHistoryListener(TableView * apTableView, VKUMessagesListItemProvider * apProvider) {
	pTableView = apTableView;
	pProvider = apProvider;
}

DialogHistoryListener::~DialogHistoryListener() {

}

void DialogHistoryListener::OnResponseN(JsonObject *object) {
	result r = E_SUCCESS;
	pProvider->SetMessagesJson(object);

	pTableView->UpdateTableView();
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult() , "Failed pTableView->UpdateTableView");

	pTableView->RequestRedraw(true);
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult() , "Failed pTableView->RequestRedraw");

	r = pTableView->ScrollToItem(pTableView->GetItemCount() - 1);
	TryCatch(r == E_SUCCESS, , "Failed pTableView->ScrollToItem");

	delete object;
	SetLastResult(r);
	return;

CATCH:
	AppLogException("DialogHistoryListener::OnResponseN is failed.", GetErrorMessage(r));
	delete object;
	SetLastResult(r);
	return;
}
