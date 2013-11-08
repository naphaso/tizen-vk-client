#include "AppResourceId.h"
#include "VKUDialogPanel.h"
#include "api/VKUApi.h"
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

	TableView* pMessagesListView = static_cast<TableView*>(GetControl(
			IDC_DIALOG_MESSAGES_LISTVIEW));
	pMessagesListView->SetItemProvider(provider);

	return r;
}

void VKUDialogPanel::LoadMessages(String userId) {
	VKUApi::GetInstance().CreateRequest("messages.getHistory", this)->Put(
			L"count", L"20")->Put(L"user_id", userId)->Submit();
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

	Invalidate(true);
}

void VKUDialogPanel::OnKeypadActionPerformed(Control &source,
		KeypadAction keypadAction) {
	VKUDialog *pForm = static_cast<VKUDialog *>(GetParent());
	String userId = pForm->userId;

	if (keypadAction == KEYPAD_ACTION_SEND) {
		String text = pEditField->GetText();
		VKUApi::GetInstance().CreateRequest(L"messages.send", this)->Put(
				L"user_id", userId)->Put(L"message", text)->Submit();
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

void VKUDialogPanel::OnResponseN(JsonObject *object) {
	AppLog("Response received");
	provider->SetMessagesJson(object);

	ListView* pMessagesListView = static_cast<ListView*>(GetControl(
			IDC_DIALOG_MESSAGES_LISTVIEW));

	pMessagesListView->UpdateList();
	pMessagesListView->RequestRedraw(true);
	pMessagesListView->ScrollToItem(pMessagesListView->GetItemCount() - 1);
	delete object;
}
