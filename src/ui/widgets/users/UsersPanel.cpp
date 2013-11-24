/*
 * UsersPanel.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: Igor Glotov
 */

#include "UsersPanel.h"
#include "Requests.h"
#include "JsonParseUtils.h"
#include "RoundedAvatar.h"
#include "VKUApi.h"
#include "ObjectCounter.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Web::Json;
using namespace Tizen::Graphics;

const wchar_t* MODEL_EMPTY = L"MODEL_EMPTY";
const wchar_t* MODEL_FRIENDS_ALPHA = L"MODEL_FRIENDS_ALPHA";
const wchar_t* MODEL_REQUESTS_SUGGESTS = L"MODEL_REQUESTS_SUGGESTS";
const wchar_t* MODEL_PHONE_CONTACTS = L"MODEL_PHONE_CONTACTS";

UsersPanel::UsersPanel() {
	CONSTRUCT(L"UsersPanel");
	_pIUserSelectedListeners = null;
	_pCurrentModel = null;
}

result UsersPanel::Construct(const Tizen::Graphics::Rectangle & rect) {
	result r = E_SUCCESS;

	_pLetterNav = new HashMap();
	_pLetterNav->Construct(70);

	RelativeLayout layout;
	r = layout.Construct();
	TryCatch(r == E_SUCCESS, , "Failed layout.Construct");

	r = Panel::Construct(layout, rect, GROUP_STYLE_NONE);
	TryCatch(r == E_SUCCESS, , "Failed Panel::Construct");

	_pIUserSelectedListeners = new ArrayList();
	r = _pIUserSelectedListeners->Construct(1);
	TryCatch(r == E_SUCCESS, , "Failed _pIUserSelectedListeners->Construct");

	_pSearchBar = new SearchBar();
	_pSearchBar->Construct(Rectangle(0, 0, rect.width, 90));
	TryCatch(r == E_SUCCESS, , "Failed _pIUserSelectedListeners->Construct");
	String searchFriendsText;
	VKUApp::GetInstance()->GetAppResource()->GetString(L"IDS_SEARCH_FRIENDS", searchFriendsText);
	_pSearchBar->SetGuideText(searchFriendsText);
	_pSearchBar->AddSearchBarEventListener(*this);
	_pSearchBar->AddTextEventListener(*this);

	_pTableView = new GroupedTableView();
	_pTableView->Construct(Rectangle(0, 0, rect.width, rect.height), true, TABLE_VIEW_SCROLL_BAR_STYLE_FAST_SCROLL);
	TryCatch(r == E_SUCCESS, , "Failed _pTableView->Construct");
//	r = _pTableView->SetFastScrollIndex(L"abcdefghijklmnopqrstuvwxyzабвгдежзиклмнопрстуфхцчшщ", false);
	TryCatch(r == E_SUCCESS, , "Failed _pTableView->SetFastScrollIndex");
	_pTableView->SetItemProvider(this);
	_pTableView->AddFastScrollListener(*this);
	_pTableView->AddGroupedTableViewItemEventListener(*this);

	r = AddControl(_pSearchBar);
	TryCatch(r == E_SUCCESS, , "Failed AddControl _pSearchBar");
	r = AddControl(_pTableView);
	TryCatch(r == E_SUCCESS, , "Failed AddControl _pTableView");

	layout.SetRelation(*_pSearchBar, this, RECT_EDGE_RELATION_TOP_TO_TOP);
	layout.SetHorizontalFitPolicy(*_pSearchBar, FIT_POLICY_PARENT);

	layout.SetRelation(*_pTableView, _pSearchBar, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
	layout.SetVerticalFitPolicy(*_pTableView, FIT_POLICY_PARENT);
	layout.SetHorizontalFitPolicy(*_pTableView, FIT_POLICY_PARENT);

	_pCurrentModel = null;

	return r;
CATCH:
	AppLogException("UsersPanel::Construct is failed. %s", GetErrorMessage(r));
	return r;
}

UsersPanel::~UsersPanel() {
	DESTRUCT(L"UsersPanel");
	if (_pIUserSelectedListeners)
		delete _pIUserSelectedListeners;

	if (_pLetterNav)
		delete _pLetterNav;
}

void UsersPanel::AddUserSelectedListener(IUserSelectedListener * pListener) {
	if (_pIUserSelectedListeners) {
		_pIUserSelectedListeners->Add(pListener);
	}

}

void UsersPanel::OnFastScrollIndexSelected(Tizen::Ui::Control& source, Tizen::Base::String& index) {
	AppLog("OnFastScrollIndexSelected %ls", index.GetPointer());
	String upperLetter;
	index.ToUpper(upperLetter);
	AppLog("Upper letter %ls", index.GetPointer());

	Integer * pos = static_cast<Integer *>(_pLetterNav->GetValue(upperLetter));

	if (pos != null) {
		int item = pos->ToInt();
		AppLog("Found at %d.", item);
		_pTableView->ScrollToItem(item, -1);
		Invalidate(true);
	} else {
		AppLog("Pointer is null...");
	}
}

// SEARCH 1
void UsersPanel::OnSearchBarModeChanged(Tizen::Ui::Controls::SearchBar& source, SearchBarMode mode) {
	if(mode == SEARCH_BAR_MODE_NORMAL) {
		_pCurrentModel->ResetFilter();

		_pTableView->UpdateTableView();
		_pTableView->RequestRedraw(true);
	}
}

// SEARCH 2
void UsersPanel::OnTextValueChanged(const Tizen::Ui::Control& source) {
	String filter(static_cast<const SearchBar*>(&source)->GetText());
	if(!filter.IsEmpty()) {
		_pCurrentModel->SetFilter(filter);
	} else {
		_pCurrentModel->ResetFilter();
	}

	_pTableView->UpdateTableView();
	_pTableView->RequestRedraw(true);
}

// SEARCH 3
void UsersPanel::OnTextValueChangeCanceled(const Tizen::Ui::Control& source) {
	_pCurrentModel->ResetFilter();

	_pTableView->UpdateTableView();
	_pTableView->RequestRedraw(true);
}


void UsersPanel::RequestModel(UserModelType model) {
	if (model == MODEL_TYPE_FRIENDS_ALPHA) {
		VKUApi::GetInstance().CreateRequest("friends.get", this)
			->Put(L"fields", L"photo_100,photo_200,online,has_mobile,contacts")
			->Put(L"order", L"name")
			->Submit(REQUEST_FRIENDS_ALPHA);
	}
}

void UsersPanel::ClearModel() {
	if(_pCurrentModel != null) {
		delete _pCurrentModel;
		_pCurrentModel = null;
		_pTableView->UpdateTableView();
		_pTableView->RequestRedraw(true);
	}
}

// IAPIRequestListener
void UsersPanel::OnResponseN(RequestId requestId, Tizen::Web::Json::JsonObject *object) {
	result r;
	if (requestId == REQUEST_FRIENDS_ALPHA) {
		GroupedUsers *users = new GroupedUsers();
		users->Construct();
		AppLog("Alpha successfully requested!");

		JsonObject * result;
		r = JsonParseUtils::GetObject(object, L"response", result);
		if (r != E_SUCCESS) {
			AppLog("NO response");
			return;
		}

		JsonArray * friends;
		r = JsonParseUtils::GetArray(result, L"items", friends);
		if (r != E_SUCCESS) {
			AppLog("NO items");
			return;
		}

		_pCurrentModel = users;

		BuildIndexForUser(friends);
		_pTableView->SetFastScrollIndex(_fastScrollIndex, false);

		_pTableView->UpdateTableView();
		_pTableView->RequestRedraw(true);

//		FIXME: parse as an alphabet list and set the model
	}

	delete object;
}

void UsersPanel::OnError(result r) {

}

// IGroupedListViewItemProvider
int UsersPanel::GetGroupCount(void) {
	if (_pCurrentModel == null)
		return 0;

	return _pCurrentModel->GetGroupCount();

}

int UsersPanel::GetItemCount(int groupIndex) {
	if (_pCurrentModel == null)
		return 0;

	return _pCurrentModel->GetUserCountInGroup(groupIndex);
}

TableViewGroupItem* UsersPanel::CreateGroupItem(int groupIndex, int itemWidth) {
	TableViewGroupItem * pItem;

	pItem = new TableViewGroupItem();
	pItem->Construct(Dimension(itemWidth, GetDefaultGroupItemHeight()));

	String name = _pCurrentModel->GetGroupName(groupIndex);
	Label * pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, GetDefaultGroupItemHeight()), name);
	pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pItem->AddControl(pLabel);

	return pItem;
}

bool UsersPanel::DeleteGroupItem(int groupIndex, TableViewGroupItem* pItem) {
	pItem->Destroy();

	return true;
}

void UsersPanel::UpdateGroupItem(int groupIndex, TableViewGroupItem* pItem) {

}

void UsersPanel::BuildIndexForUser(JsonArray * friends) {
	/*
	String letter, prevLetter = L"";
	int currentGroup = 0;

	JsonArray * array = new JsonArray();
	array->Construct();

	for (int i=0; i<friends->GetCount(); i++) {
		JsonObject *user;
		JsonParseUtils::GetObject(friends, i, user);

		String name;
		JsonParseUtils::GetString(*user, L"first_name", name);

		name.SubString(0, 1, letter);

		if (letter != prevLetter) {
			_fastScrollIndex.Append(letter);
			_pCurrentModel->AddUserGroup(prevLetter, array);

			if (prevLetter.GetLength() > 0) {
				AppLog("Adding %ls to %d item", prevLetter.GetPointer(), currentGroup);
				_pLetterNav->Add(new String(prevLetter), new Integer(currentGroup));
				currentGroup++;
			}

			prevLetter = letter;
			delete array;
			array = new JsonArray();
			array->Construct();
		} else {
			array->Add(user);
		}

	}*/

	HashMap *letterMap = new HashMap();
	letterMap->Construct();

	for(int i = 0; i < friends->GetCount(); i++) {
		JsonObject *user;
		JsonParseUtils::GetObject(friends, i, user);

		String name;
		JsonParseUtils::GetString(*user, L"first_name", name);

		String letter;
		name.SubString(0, 1, letter);

		JsonArray *letterArray;
		if(!letterMap->ContainsKey(letter)) {
			letterArray = new JsonArray();
			letterArray->Construct();
			letterMap->Add(new String(letter), letterArray);
		} else {
			letterArray = static_cast<JsonArray*>(letterMap->GetValue(letter));
		}

		letterArray->Add(user);
	}

	IList *letterList = letterMap->GetKeysN();
	StringComparer comparer;
	letterList->Sort(comparer);
	for(int i = 0; i < letterList->GetCount(); i++) {
		String *letter = static_cast<String *>(letterList->GetAt(i));
		_fastScrollIndex.Append(*letter);
		_pCurrentModel->AddUserGroup(*letter, static_cast<JsonArray *>(letterMap->GetValue(*letter)));
		_pLetterNav->Add(new String(*letter), new Integer(i));
	}

	delete letterList;
	delete letterMap;
}

TableViewItem* UsersPanel::CreateItem(int groupIndex, int itemIndex, int itemWidth) {
	result r = E_SUCCESS;

	TableViewItem * pItem;

	RelativeLayout layout;
	layout.Construct();

	pItem = new TableViewItem();
	pItem->Construct(layout, Dimension(itemWidth, GetDefaultItemHeight()), TABLE_VIEW_ANNEX_STYLE_NORMAL);

	JsonObject *userJson;
	r = _pCurrentModel->GetUserFromGroup(groupIndex, itemIndex, userJson);

	String name, nextName, photo100;
	JsonParseUtils::GetString(*userJson, L"first_name", name);
	name += L" ";
	JsonParseUtils::GetString(*userJson, L"last_name", nextName);
	name += nextName;
	JsonParseUtils::GetString(*userJson, L"photo_100", photo100);

	Label *pNameLabel = new Label();
	pNameLabel->Construct(Rectangle(0, 0, itemWidth, 90), name);
	pNameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	RoundedAvatar *pAvatar = new RoundedAvatar(AVATAR_NORMAL);
	pAvatar->Construct(Rectangle(0, 0, 108, 108), photo100);

	pItem->AddControl(pAvatar);
	pItem->AddControl(pNameLabel);

	layout.SetRelation(*pAvatar, pItem, RECT_EDGE_RELATION_LEFT_TO_LEFT);
	layout.SetCenterAligned(*pAvatar, CENTER_ALIGN_VERTICAL);
	layout.SetMargin(*pAvatar, 30, 0, 0, 0);

	layout.SetRelation(*pNameLabel, pAvatar, RECT_EDGE_RELATION_LEFT_TO_RIGHT);
	layout.SetCenterAligned(*pNameLabel, CENTER_ALIGN_VERTICAL);
	layout.SetMargin(*pNameLabel, 10, 0, 0, 0);

	return pItem;
}

bool UsersPanel::DeleteItem(int groupIndex, int itemIndex, TableViewItem* pItem) {
	pItem->Destroy();

	return true;
}

void UsersPanel::UpdateItem(int groupIndex, int itemIndex, TableViewItem* pItem) {

}

int UsersPanel::GetDefaultGroupItemHeight(void) {
	return 80;
}

int UsersPanel::GetDefaultItemHeight(void) {
	return 130;
}

// ITableViewItemEventListener
void UsersPanel::OnGroupedTableViewGroupItemStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView,
		int groupIndex,
		Tizen::Ui::Controls::TableViewGroupItem* pItem,
		Tizen::Ui::Controls::TableViewItemStatus status) {

}

void UsersPanel::OnGroupedTableViewItemStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView,
		int groupIndex,
		int itemIndex,
		Tizen::Ui::Controls::TableViewItem* pItem,
		Tizen::Ui::Controls::TableViewItemStatus status) {

	JsonObject * userObject; // FIXME: provide
	_pCurrentModel->GetUserFromGroup(groupIndex, itemIndex, userObject);

	switch(status) {
	case TABLE_VIEW_ITEM_STATUS_SELECTED:
		AppLog("TABLE_VIEW_ITEM_STATUS_SELECTED");
		NotifyUserSelectedListeners(userObject);
		break;
	case TABLE_VIEW_ITEM_STATUS_HIGHLIGHTED:
		AppLog("TABLE_VIEW_ITEM_STATUS_HIGHLIGHTED");
		break;
	case TABLE_VIEW_ITEM_STATUS_CHECKED:
		AppLog("TABLE_VIEW_ITEM_STATUS_CHECKED");
		break;
	case TABLE_VIEW_ITEM_STATUS_UNCHECKED:
		AppLog("TABLE_VIEW_ITEM_STATUS_UNCHECKED");
		break;
	case TABLE_VIEW_ITEM_STATUS_MORE:
		AppLog("TABLE_VIEW_ITEM_STATUS_MORE");
		break;
	}
}

void UsersPanel::OnGroupedTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView,
		int groupIndex,
		int itemIndex,
		Tizen::Ui::Controls::TableViewContextItem* pContextItem,
		bool activated) {

}

void UsersPanel::NotifyUserSelectedListeners(const JsonObject * user) {
	AppLog("UsersPanel::NotifyUserSelectedListeners");
	for (int i=0; i < _pIUserSelectedListeners->GetCount(); i++) {
		IUserSelectedListener * item = dynamic_cast<IUserSelectedListener *>(_pIUserSelectedListeners->GetAt(i));
		item->OnUserSelected(user);
	}
}

