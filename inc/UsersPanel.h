/*
 * UsersPanel.h
 *
 *  Created on: Nov 21, 2013
 *      Author: Igor Glotov
 */

#ifndef USERSPANEL_H_
#define USERSPANEL_H_

#include <FUi.h>
#include <FGraphics.h>
#include <IUserSelectedListener.h>
#include "GroupedUsers.h"
#include "IAPIRequestListener.h"

extern const wchar_t* MODEL_EMPTY;
extern const wchar_t* MODEL_FRIENDS_ALPHA;
extern const wchar_t* MODEL_REQUESTS_SUGGESTS;
extern const wchar_t* MODEL_PHONE_CONTACTS;

typedef enum {
	MODEL_TYPE_EMPTY,
	MODEL_TYPE_FRIENDS_ALPHA,
	MODEL_TYPE_REQUESTS_SUGGESTS,
	MODEL_TYPE_PHONE_CONTACTS
} UserModelType;

class UsersPanel:
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::Controls::IGroupedTableViewItemProvider,
	public Tizen::Ui::Controls::IGroupedTableViewItemEventListener,
    public Tizen::Ui::Controls::ISearchBarEventListener,
    public Tizen::Ui::ITextEventListener,
    public Tizen::Ui::Controls::IFastScrollListener,
    public IAPIRequestListener {
public:
	UsersPanel();
	virtual ~UsersPanel();

	virtual result Construct(const Tizen::Graphics::Rectangle & rect);

	void AddUserSelectedListener(IUserSelectedListener * pListener);

	void RequestModel(UserModelType model);

	// IAPIRequestListener
	virtual void OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object);
	virtual void OnError(result r);

	// ITableViewItemEventListener
	virtual void OnGroupedTableViewGroupItemStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView, int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status);
	virtual void OnGroupedTableViewItemStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView, int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status);
	virtual void OnGroupedTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView, int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewContextItem* pContextItem, bool activated);

	// IGroupedListViewItemProvider
	virtual int GetGroupCount(void);
	virtual int GetItemCount(int groupIndex);
	virtual Tizen::Ui::Controls::TableViewGroupItem* CreateGroupItem(int groupIndex, int itemWidth);
	virtual bool DeleteGroupItem(int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem);
	virtual void UpdateGroupItem(int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem);
	virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int groupIndex, int itemIndex, int itemWidth);
	virtual bool DeleteItem(int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual void UpdateItem(int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual int GetDefaultGroupItemHeight(void);
	virtual int GetDefaultItemHeight(void);

	// IFastScrollListener
	virtual void OnFastScrollIndexSelected(Tizen::Ui::Control& source, Tizen::Base::String& index);

	// ISearchBarEventListener
	virtual void OnSearchBarModeChanged(Tizen::Ui::Controls::SearchBar& source, Tizen::Ui::Controls::SearchBarMode mode);

	// ITextEventListener
	virtual void OnTextValueChanged(const Tizen::Ui::Control& source);
	virtual void OnTextValueChangeCanceled(const Tizen::Ui::Control& source);


private:
	void NotifyUserSelectedListeners(const Tizen::Web::Json::JsonObject * user);
	Tizen::Base::Collection::ArrayList * _pIUserSelectedListeners;

	// UI
	Tizen::Ui::Controls::SearchBar * _pSearchBar;
	Tizen::Ui::Controls::GroupedTableView * _pTableView;

	void InitModels();
	void BuildIndexForUser(Tizen::Web::Json::JsonArray * array);

	GroupedUsers * _pCurrentModel;
	Tizen::Base::String _fastScrollIndex;
	Tizen::Base::Collection::HashMap * _pLetterNav;
};

#endif /* USERSPANEL_H_ */
