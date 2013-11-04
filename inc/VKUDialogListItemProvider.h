/*
 * VKUDialogListItemProvider.h
 *
 *  Created on: Nov 3, 2013
 *      Author: Igor Glotov
 */

#ifndef VKUDIALOGLISTITEMPROVIDER_H_
#define VKUDIALOGLISTITEMPROVIDER_H_
#include <FUi.h>
#include <FWebJson.h>
#include "VKU.h"
#include "AppResourceId.h"
#include <FUiCtrlIListViewItemProvider.h>

class VKUDialogListItemProvider:
	public Tizen::Ui::Controls::IListViewItemProvider,
	public Tizen::Ui::Controls::IListViewItemEventListener
{
public:
	VKUDialogListItemProvider();
	virtual ~VKUDialogListItemProvider();

	// IFormBackEventListener
//	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	// IListViewItemEventListener
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView& listView, int index, Tizen::Ui::Controls::SweepDirection direction);
	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
	virtual void OnItemReordered(Tizen::Ui::Controls::ListView& view, int oldIndex, int newIndex);

	// IListViewItemProvider
	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
	virtual bool DeleteItem(int index, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth);

	// others
	void SetDialogsJson(Tizen::Web::Json::JsonObject *json);
private:
	Tizen::Web::Json::JsonObject *responseJson;
	Tizen::Web::Json::JsonArray *dialogsJson;

	Tizen::Graphics::Bitmap* avatarBm;
};

#endif /* VKUDIALOGLISTITEMPROVIDER_H_ */
