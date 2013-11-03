/*
 * VKUDialogListItemProvider.h
 *
 *  Created on: Nov 3, 2013
 *      Author: Igor Glotov
 */

#ifndef VKUDIALOGLISTITEMPROVIDER_H_
#define VKUDIALOGLISTITEMPROVIDER_H_
#include <FUi.h>
#include <FUiCtrlIListViewItemProvider.h>

class VKUDialogListItemProvider: public Tizen::Ui::Controls::IListViewItemProvider {
public:
	VKUDialogListItemProvider();
	virtual ~VKUDialogListItemProvider();

	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
	virtual bool DeleteItem(int index, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth);
};

#endif /* VKUDIALOGLISTITEMPROVIDER_H_ */
