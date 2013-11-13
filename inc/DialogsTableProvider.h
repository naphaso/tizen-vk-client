/*
 * DialogsTableProvider.h
 *
 *  Created on: Nov 11, 2013
 *      Author: igorglotov
 */

#ifndef DIALOGSTABLEPROVIDER_H_
#define DIALOGSTABLEPROVIDER_H_

#include <FUi.h>
#include <FBase.h>
#include <FWebJson.h>

#include "RoundedAvatar.h"
#include "JsonParseUtils.h"
#include "TimeUtils.h"
#include "IAPIRequestListener.h"

class DialogsTableProvider: public Tizen::Ui::Controls::ITableViewItemProvider,
		public Tizen::Ui::Controls::ITableViewItemEventListener,
		public IAPIRequestListener {
public:
	DialogsTableProvider();
	virtual ~DialogsTableProvider();
	void Construct(Tizen::Ui::Controls::TableView* tableView) {
		pDialogTableView = tableView;
	}

	// ITableViewItemProvider
	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int itemIndex,
			int itemWidth);
	virtual bool DeleteItem(int itemIndex,
			Tizen::Ui::Controls::TableViewItem* pItem);
	virtual void UpdateItem(int itemIndex,
			Tizen::Ui::Controls::TableViewItem* pItem);
	virtual int GetDefaultItemHeight(void);

	// ITableViewItemEventListener
	virtual void OnTableViewItemStateChanged(
			Tizen::Ui::Controls::TableView& tableView, int itemIndex,
			Tizen::Ui::Controls::TableViewItem* pItem,
			Tizen::Ui::Controls::TableViewItemStatus status);

	virtual void OnTableViewContextItemActivationStateChanged(
			Tizen::Ui::Controls::TableView& tableView, int itemIndex,
			Tizen::Ui::Controls::TableViewContextItem* pContextItem,
			bool activated) {};

	virtual void OnTableViewItemReordered(
			Tizen::Ui::Controls::TableView& tableView, int itemIndexFrom,
			int itemIndexTo) {};

	void SetDialogsJson(Tizen::Web::Json::JsonObject* obj);
	void ProcessJson(Tizen::Web::Json::JsonObject* obj);
	void LoadData();
	void OpenDialog(int itemId);

	// IAPIRequestListener
	virtual void OnResponseN(Tizen::Web::Json::JsonObject *object);

private:
	Tizen::Web::Json::JsonObject* responseJson;
	Tizen::Web::Json::JsonArray* dialogsJson;
	Tizen::Ui::Controls::TableView* pDialogTableView;
};

#endif /* DIALOGSTABLEPROVIDER_H_ */
