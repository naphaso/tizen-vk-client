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
#include <FUiCtrlIListViewItemProvider.h>

class VKUDialogListItemProvider: public Tizen::Ui::Controls::IListViewItemProvider {
public:
	VKUDialogListItemProvider();
	virtual ~VKUDialogListItemProvider();

	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
	virtual bool DeleteItem(int index, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth);

	void SetDialogsJson(Tizen::Web::Json::JsonObject *json);
private:
	Tizen::Web::Json::JsonObject *responseJson;
	Tizen::Web::Json::JsonArray *dialogsJson;

	Tizen::Graphics::Bitmap* avatarBm;
};

#endif /* VKUDIALOGLISTITEMPROVIDER_H_ */
