/*
 * AttachPopup.h
 *
 *  Created on: Nov 24, 2013
 *      Author: Igor Glotov
 */

#ifndef ATTACHPOPUP_H_
#define ATTACHPOPUP_H_

#include <FUi.h>
#include <FBase.h>
#include <FApp.h>
#include "AttachControl.h"

typedef enum AttachmentTypeIndexed {
	ATI_PHOTO = 0,
	ATI_VIDEO = 1,
	ATI_AUDIO = 2,
	ATI_DOC = 3,
	ATI_LOCATION = 4
};

class AttachPopup:
	public Tizen::Ui::IPropagatedKeyEventListener,
	public Tizen::Ui::Controls::ITableViewItemProvider,
	public Tizen::Ui::Controls::ITableViewItemEventListener,
	public Tizen::App::IAppControlResponseListener {
public:
	AttachPopup(AttachControl * ctl);
	virtual ~AttachPopup();

	static void Show(AttachControl* ctl);
	void HideAndDie();
	void CreateAttachment(AttachmentTypeIndexed item);


	// IPropagatedKeyEventListener
	virtual bool OnKeyPressed(Tizen::Ui::Control& source,
							 const Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};
	virtual bool OnKeyReleased(Tizen::Ui::Control& source,
							  const Tizen::Ui::KeyEventInfo& keyEventInfo);
	virtual bool OnPreviewKeyPressed(Tizen::Ui::Control& source,
									const Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};
	virtual bool OnPreviewKeyReleased(Tizen::Ui::Control& source,
									 const Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};
	virtual bool TranslateKeyEventInfo(Tizen::Ui::Control& source,
									  Tizen::Ui::KeyEventInfo& keyEventInfo) {return false;};

	// IAppControlProviderEventListener
	void OnAppControlCompleteResponseReceived(const Tizen::App::AppId& appId,
							 const Tizen::Base::String& operationId,
							 const Tizen::App::AppCtrlResult appControlResult,
							 const Tizen::Base::Collection::IMap* pExtraData);
	// ITableViewItemProvider
	virtual int GetItemCount(void);
	virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int itemIndex, int itemWidth);
	virtual bool DeleteItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual void UpdateItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
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
private:
	void Start();

	static Tizen::Ui::Controls::Popup *_popup;
	AttachControl * _attachControl;
};

#endif /* ATTACHPOPUP_H_ */
