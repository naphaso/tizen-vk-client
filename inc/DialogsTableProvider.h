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
		public IAPIRequestListener,
		public Tizen::Ui::ITextEventListener,
		public Tizen::Ui::Controls::ISearchBarEventListener,
		public Tizen::Ui::IActionEventListener {
public:
	DialogsTableProvider();
	result Construct(Tizen::Ui::Controls::TableView* tableView);
	virtual ~DialogsTableProvider();

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
			bool activated);

	virtual void OnTableViewItemReordered(
			Tizen::Ui::Controls::TableView& tableView, int itemIndexFrom,
			int itemIndexTo) { AppLog("OnTableViewItemReordered"); };

	// IActionEventListener
	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	void SetDialogsJson(Tizen::Web::Json::JsonObject* obj);
	void ProcessJson(Tizen::Web::Json::JsonObject* obj);
	void LoadData();
	void OpenDialog(int itemId);

	// IAPIRequestListener
	virtual void OnResponseN(Tizen::Web::Json::JsonObject *object);

	// ITextEventListener
	virtual void OnTextValueChanged(const Tizen::Ui::Control& source);
	virtual void OnTextValueChangeCanceled(const Tizen::Ui::Control& source);


	//ISearchBarEventListener
	virtual void OnSearchBarModeChanged(Tizen::Ui::Controls::SearchBar& source, Tizen::Ui::Controls::SearchBarMode mode);
private:
	Tizen::Web::Json::JsonObject* responseJson;
	Tizen::Web::Json::JsonArray* dialogsJson;
	Tizen::Web::Json::JsonArray* filteredDialogsJson;
	Tizen::Ui::Controls::TableView* pDialogTableView;

	int pendingRemoveId;
};

#endif /* DIALOGSTABLEPROVIDER_H_ */
