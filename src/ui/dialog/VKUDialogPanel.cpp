#include "AppResourceId.h"
#include "VKUDialogPanel.h"
#include "../../api/VKUApi.h"
#include "VKUDialog.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Json;

VKUDialogPanel::VKUDialogPanel(void) {
	provider = new VKUMessagesListItemProvider();
}

VKUDialogPanel::~VKUDialogPanel(void) {
//	delete provider;
}

bool VKUDialogPanel::Initialize() {
	Panel::Construct(IDC_PANEL_DIALOG);

	return true;
}

result VKUDialogPanel::OnInitializing(void) {
	result r = E_SUCCESS;
	AppLog("Panel init");

	// TODO: Add your initialization code here
	FitToScreen();

	pEditField = static_cast<EditField*>(GetControl(IDC_DIALOGTEXT_EDITFIELD));
	pEditField->AddKeypadEventListener(*this);

	// table view init
	pMessagesListView = static_cast<TableView*>(GetControl(
			IDC_DIALOG_MESSAGES_LISTVIEW));
	pMessagesListView->SetItemDividerColor(Color::GetColor(COLOR_ID_BLACK));

	pDialogHistoryListener = new DialogHistoryListener(pMessagesListView, provider);
	pMessageSentListener = new MessageSentListener(pMessagesListView, provider);

	AppLog("Setting pDialogHistoryListener");
	provider->SetListener(pDialogHistoryListener);
	pMessagesListView->SetItemProvider(provider);

	return r;
}

void VKUDialogPanel::LoadMessages() {
	TryReturnVoid(userId.GetLength() != 0, "VKUDialogPanel: LoadMessages cannot be completed until userId is not set");
	AppLog("Doing VKUDialogPanel::LoadMessages");

	provider->RequestData(userId);
}

void VKUDialogPanel::SetUserId(String aUserId) {
	TryReturnVoid(pMessageSentListener != null, "VKUDialogPanel: Fatal - pMessageSentListener is null");
	pMessageSentListener->SetUserId(aUserId);

	userId = aUserId;
}

result VKUDialogPanel::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void VKUDialogPanel::FitToScreen() {
	VKUDialog *pForm = static_cast<VKUDialog *>(GetParent());

	if (pForm != null) {
		Rectangle clientRect = pForm->GetClientAreaBounds();
		Rectangle rect(0, 0, clientRect.width, clientRect.height);

		SetBounds(rect);
	}

	if (pMessagesListView != null) {
		pMessagesListView->ScrollToItem(pMessagesListView->GetItemCount() - 1);
	}

	Invalidate(true);
}

void VKUDialogPanel::OnKeypadActionPerformed(Control &source,
		KeypadAction keypadAction) {
	VKUDialog *pForm = static_cast<VKUDialog *>(GetParent());
	String userId = pForm->userId;

	if (keypadAction == KEYPAD_ACTION_SEND) {
		String text = pEditField->GetText();
		VKUApi::GetInstance().CreateRequest(L"messages.send", pMessageSentListener)->Put(
				L"user_id", userId)->Put(L"message", text)->Submit();
		pEditField->Clear();
		pEditField->RequestRedraw(true);
	}
}

void VKUDialogPanel::OnKeypadBoundsChanged(Control &source) {

}

void VKUDialogPanel::OnKeypadClosed(Control &source) {
	AppLog("Keypad closed");
	FitToScreen();
}

void VKUDialogPanel::OnKeypadOpened(Control &source) {
	AppLog("Keypad opened");
	FitToScreen();
}

void VKUDialogPanel::OnKeypadWillOpen(Control &source) {

}
