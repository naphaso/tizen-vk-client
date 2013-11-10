/*
 * DialogHistoryListener.h
 *
 *  Created on: Nov 10, 2013
 *      Author: igorglotov
 */

#ifndef DIALOGHISTORYLISTENER_H_
#define DIALOGHISTORYLISTENER_H_

#include <FUi.h>
#include <FWeb.h>
#include <FWebJson.h>

class DialogHistoryListener;

#include "VKUMessagesListItemProvider.h"
#include "IAPIRequestListener.h"

class DialogHistoryListener: public IAPIRequestListener {
public:
	DialogHistoryListener(Tizen::Ui::Controls::TableView * pTableView, VKUMessagesListItemProvider * pProvider);
	virtual ~DialogHistoryListener();

	// IAPIRequestListener
	virtual void OnResponseN(Tizen::Web::Json::JsonObject *object);

private:
	Tizen::Ui::Controls::TableView * pTableView;
	VKUMessagesListItemProvider * pProvider;
};

#endif /* DIALOGHISTORYLISTENER_H_ */
